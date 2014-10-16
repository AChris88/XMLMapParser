#pragma once
#include "rapidxml.hpp"
#include "Map.h"
#include <string>

using namespace std;
using namespace rapidxml;

class MapEditor
{
public:
	MapEditor();
	MapEditor(std::string mapDir);
	void saveMap(std::string saveDir);

	~MapEditor();

	void MapEditor::setTile(int row, int col, int val);
private:
	Map map;
	xml_document<> doc;

	bool validateMap() const;
	void createNewMap();
	void loadMapFile(std::string mapDir);
	void importMap() const;
	void printMap() const;
};