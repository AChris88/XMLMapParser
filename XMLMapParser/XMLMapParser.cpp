// XMLMapParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "rapidxml_print.hpp";
#include "Map.h"
#include "MapEditor.h"

using namespace std;
using namespace rapidxml;

int _tmain(int argc, _TCHAR* argv[])
{
	std::string mapDir = "C:/XMLTestFile.xml";
	std::string saveDir = "C:/savedMap.xml";

	//MapEditor* editor = new MapEditor();
	MapEditor editor(mapDir);
	editor.saveMap(saveDir);

	cin.get();
	return 0;
}