#pragma once
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	Map(int height, int width);
	~Map();

	Map& operator=(Map& map);

	void setTile(int x, int y, int val);
	const std::vector<std::vector<int>> getMap();
	int getWidth() const;
	int getHeight() const;
	int getTile(int x, int y) const;
	void printMap() const;
private:
	const int MAX_MAP_WIDTH = 64;
	const int MAX_MAP_HEIGHT = 64;
	const int MIN_MAP_WIDTH = 8;
	const int MIN_MAP_HEIGHT = 8;

	int width;
	int height;
	std::vector<std::vector<int> > map;
};

