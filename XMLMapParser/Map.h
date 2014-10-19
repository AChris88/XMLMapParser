#pragma once
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	Map(int rows, int cols);
	~Map();

	const static int MAX_MAP_WIDTH = 64;
	const static int MAX_MAP_HEIGHT = 64;
	const static int MIN_MAP_WIDTH = 8;
	const static int MIN_MAP_HEIGHT = 8;

//	const std::vector<std::vector<int>> getMap();

	void setTile(int x, int y, int val);
	int getCols() const;
	int getRows() const;
	int getTile(int x, int y) const;
	void printMap() const;
private:

	int cols;
	int rows;
	std::vector<std::vector<int> > map;
};

