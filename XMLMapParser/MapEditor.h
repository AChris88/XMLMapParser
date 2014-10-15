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
private:
	Map map;
	xml_document<> doc;

	bool validateMap(Map* map);
	void loadMapFile(std::string mapDir);
	void importMap() const;
	void printMap() const;
};