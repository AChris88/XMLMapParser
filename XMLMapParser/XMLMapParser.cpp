#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "rapidxml_print.hpp"
#include "Map.h"
#include "MapEditor.h"

using namespace std;
using namespace rapidxml;

int _tmain(int argc, _TCHAR* argv[])
{
	//Create custom map;
	/*
	MapEditor* editor = new MapEditor();
	cin.get();
	*/

	//Reading from xml map file
	/*
	std::string mapDir = "C:/XMLTestFile.xml";
	std::string saveDir = "C:/savedMap.xml";
	MapEditor editor("C:/XMLTestFile.xml");
	editor.saveMap(saveDir);
	*/

	//Validity test
	//NOTE: This accepts a pre-determined size because the tiles are manually assigned to create a path.
	//		If you wish to test the funtionality further, you can manually build a path in 
	//		MapEditor::validityTest() using Map::setTile(int x, int y, int val)
	/*
	MapEditor editor(8, 8);
	editor.validityTest();
	*/

	cin.get();
	return 0;
}