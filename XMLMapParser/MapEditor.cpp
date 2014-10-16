#include "stdafx.h"
#include "MapEditor.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace rapidxml;

MapEditor::MapEditor()
{
	createNewMap();
	validateMap();
}

MapEditor::MapEditor(std::string path){
	loadMapFile(path);
	validateMap();
	//loadMapFile(path);
}

MapEditor::~MapEditor()
{
}

void MapEditor::loadMapFile(std::string mapDir){
	int rows;
	int cols;

	//reading in xml map file into xml_document<> doc
	std::ifstream file("C:/XMLTestFile.xml");
	cout << "file.isOpen(): " << file.is_open() << endl;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	cout << "content.length(): " << content.length() << endl;
	doc.parse<0>(&content[0]);

	//instantiating pointers to the map head and to it's rows
	xml_node<> *mapHead = doc.first_node("map");
	//xml_node<> *row = mapHead->first_node("row");

	//iterating through map attributes
	for (xml_attribute<> *attr = mapHead->first_attribute();
		attr; attr = attr->next_attribute())
	{
		std::string name(attr->name());
		if (name == "cols") {
			cols = atoi(attr->value());
			continue;
		}
		if (name == "rows") {
			rows = atoi(attr->value());
			continue;
		}
	}

	//creating map
	this->map = Map(rows, cols);

	int x = 0;
	int y = 0;

	//populating map with map data from xml
	for (xml_node<> *row = mapHead->first_node("row"); row; row = row->next_sibling()){
		for (xml_node<> *tile = row->first_node("tile"); tile; tile = tile->next_sibling("tile")){
			map.setTile(x, y++, atoi(tile->first_attribute()->value()));
		}
		++x;
		if (x >= cols)
			x = 0;
		if (y >= rows)
			y = 0;
	}

	printMap();
}

void MapEditor::saveMap(std::string path){
	//val used as temp holding to convert c_str() to xml string
	char* val;
	int rows = map.getRows();
	int cols = map.getCols();

	//creating and setting xml header tag
	xml_document<> output;
	xml_node<>* header = output.allocate_node(node_declaration);
	header->append_attribute(output.allocate_attribute("version", "1.0"));
	header->append_attribute(output.allocate_attribute("encoding", "UTF-8"));
	output.append_node(header);

	//creating and setting map header tag
	xml_node<>* root = output.allocate_node(node_element, "map");

	val = doc.allocate_string(std::to_string(rows).c_str());
	xml_attribute<> *heightAttr = output.allocate_attribute("rows", val);

	val = doc.allocate_string(std::to_string(cols).c_str());
	xml_attribute<> *widthAttr = output.allocate_attribute("cols", val);

	root->append_attribute(heightAttr);
	root->append_attribute(widthAttr);

	//instantiate map components
	xml_node<> *tileNode;
	xml_attribute<> *tileValue;
	xml_node<> *row;
	output.append_node(root);

	//populating xml file with map data
	for (int i = 0; i < rows; i++) {
		row = output.allocate_node(node_element, "row");
		root->append_node(row);
		for (int j = 0; j < cols; j++) {
			tileNode = output.allocate_node(node_element, "tile");
			val = doc.allocate_string(std::to_string(map.getTile(i, j)).c_str());
			tileValue = output.allocate_attribute("access", val);
			tileNode->append_attribute(tileValue);
			row->append_node(tileNode);
		}
	}
	
	//outputting xml data to file
	std::ofstream outputFile;
	outputFile.open(path);
	outputFile << output;
	outputFile.close();
}

void MapEditor::createNewMap(){
	int cols;
	int rows;
	
	cout << "Enter number of rows: ";
	cin >> rows; 
	cout << "\nEnter number of columns: ";
	cin >> cols;

	this->map = Map(rows, cols);

	//populate map for testing
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map.setTile(i, j, 0);
		}
	}
}

void MapEditor::printMap() const{
	map.printMap();
}

void MapEditor::setTile(int row, int col, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = tower
	*  3 = start
	*  4 = end
	*/

	map.setTile(row, col, val);
}

bool MapEditor::validateMap() const{
	bool start = false;	//3
	bool end = false;	//4
	bool connected = false;
	bool valid = false;
	
	cout << "Found start: " << start << endl;
	cout << "Found end: " << end << endl;
	cout << "Connected: " << connected << endl;

	//find start and end
		//checking top and bottom rows
	for (int col = 0; col < map.getCols(); col++){
		if (map.getTile(0, col) == 3 || map.getTile(map.getRows() - 1, col) == 3)
			if (!start)
				start = true;
			else { //if multiple starts are found
				cout << "multiple starts in top/bottom" << endl;
				return false;
			}
		if (map.getTile(0, col) == 4 || map.getTile(map.getRows() - 1, col) == 4)
			if (!end)
				end = true;
			else { //if multiple ends are found
				cout << "multiple ends in top/bottom" << endl;
				return false;
			}
	}
		//checking first and last column
	for (int row = 1; row < map.getRows(); row++){
		if (map.getTile(row, 0) == 3 || map.getTile(row, map.getCols() - 1) == 3)
			if (!start)
				start = true;
			else { //if multiple starts are found
				cout << "multiple starts in left/right" << endl;
				return false;
			}
		if (map.getTile(row, 0) == 4 || map.getTile(row, map.getCols() - 1) == 4)
			if (!end)
				end = true;
			else { //if multiple ends are found
				cout << "multiple ends in left/right" << endl;
				return false;
			}
	}

	//check connection
	
	printMap();

	cout << "Found start: " << start << endl;
	cout << "Found end: " << end << endl;
	cout << "Connected: " << connected << endl;

	return (start && end);
}