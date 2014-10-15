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
}

MapEditor::MapEditor(std::string path){
	loadMapFile(path);
}

MapEditor::~MapEditor()
{
}

void MapEditor::loadMapFile(std::string mapDir){
	int height = 0;
	int width = 0;

	std::ifstream file("C:/XMLTestFile.xml");
	cout << "file.isOpen(): " << file.is_open() << endl;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	cout << "content.length(): " << content.length() << endl;
	doc.parse<0>(&content[0]);

	xml_node<> *mapHead = doc.first_node("map");
	xml_node<> *rows = mapHead->first_node("row");

	//iterating through map attributes
	for (xml_attribute<> *attr = mapHead->first_attribute();
		attr; attr = attr->next_attribute())
	{
		std::string name(attr->name());
		if (name == "width") {
			width = atoi(attr->value());
			continue;
		}
		if (name == "height") {
			height = atoi(attr->value());
			continue;
		}
	}

	//creating map
	this->map = Map(height, width);

	//populating map with map data from xml
	int x = 0;
	int y = 0;

	for (xml_node<> *row = mapHead->first_node("row"); row; row = row->next_sibling()){
		for (xml_node<> *tile = row->first_node("tile"); tile; tile = tile->next_sibling("tile")){
			map.setTile(x, y++, atoi(tile->first_attribute()->value()));
		}
		++x;
		if (x >= width)
			x = 0;
		if (y >= height)
			y = 0;
	}
}

void MapEditor::saveMap(std::string path){
	char* val;
	int height = map.getHeight();
	int width = map.getWidth();

	//creating xml header tag
	xml_document<> output;
	xml_node<>* header = output.allocate_node(node_declaration);
	header->append_attribute(output.allocate_attribute("version", "1.0"));
	header->append_attribute(output.allocate_attribute("encoding", "UTF-8"));
	output.append_node(header);

	//creating map header tag
	xml_node<>* root = output.allocate_node(node_element, "map");
	val = doc.allocate_string(std::to_string(height).c_str());
	xml_attribute<> *heightAttr = output.allocate_attribute("height", val);
	val = doc.allocate_string(std::to_string(width).c_str());
	xml_attribute<> *widthAttr = output.allocate_attribute("width", val);
	root->append_attribute(heightAttr);
	root->append_attribute(widthAttr);

	xml_node<> *tileNode;
	xml_attribute<> *tileValue;
	xml_node<> *row;
	output.append_node(root);

	//populating xml file with map data
	for (int i = 0; i < width; i++) {
		row = output.allocate_node(node_element, "row");
		root->append_node(row);
		for (int j = 0; j < height; j++) {
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

void MapEditor::printMap() const{
	map.printMap();
}