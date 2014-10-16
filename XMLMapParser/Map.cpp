#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

Map::Map()
{
	this->map = std::vector<std::vector<int> >(0, std::vector<int>(0, 0));
}

Map::Map(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->map = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));
}

Map::~Map()
{
}

Map& Map::operator=(Map& map)
{
	if (this != &map)
	{
		swap(this->map, map.map);
	}
	return *this;
}

void Map::setTile(int x, int y, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = tower
	*  3 = start
	*  4 = end
	*/

	//add validation
	map[x][y] = val;
}

//printing map for testing
void Map::printMap() const {
	for (int i = 0; i < (int)map.size(); i++){
		for (int j = 0; j < (int)map[i].size(); j++)
			cout << "|" << map[i][j] << "|";
		cout << "\n";
	}
}

const std::vector<std::vector<int>> Map::getMap(){
	return map;
}

int Map::getRows() const{
	return map.size();
}

int Map::getCols() const{
	return map[0].size();
}

int Map::getTile(int row, int col) const {
	return map[row][col];
}