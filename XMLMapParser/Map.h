#pragma once
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	Map(int rows, int cols);
	~Map();

	Map& operator=(Map& map);

	void setTile(int x, int y, int val);
	const std::vector<std::vector<int>> getMap();
	int getCols() const;
	int getRows() const;
	int getTile(int x, int y) const;
	void printMap() const;
private:
	const int MAX_MAP_WIDTH = 64;
	const int MAX_MAP_HEIGHT = 64;
	const int MIN_MAP_WIDTH = 8;
	const int MIN_MAP_HEIGHT = 8;

	int cols;
	int rows;
	std::vector<std::vector<int> > map;
};

