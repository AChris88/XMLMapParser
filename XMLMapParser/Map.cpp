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

void Map::setTile(int x, int y, int val){
	/* acceptable vals
	*  0 = scenery
	*  1 = path
	*  2 = tower
	*  3 = start
	*  4 = end
	*/

	//checking that x and y are within map range and that value is valid
	if (x >= 0 && x <= (getRows() - 1) && 
		y >= 0 && y <= (getCols() - 1) && 
		(val >= 0 && val <=4))
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

/*
const std::vector<std::vector<int>> Map::getMap(){
	return map;
}
*/

//return the number of rows in the map
int Map::getRows() const{
	return map.size();
}

//returns the number of columns in the map
int Map::getCols() const{
	return map[0].size();
}

//retrieves that value at a specified x, y index
int Map::getTile(int x, int y) const {
	if (x >= 0 && x <= (getRows() - 1) &&
		y >= 0 && y <= (getCols() - 1))
		return map[x][y];
}