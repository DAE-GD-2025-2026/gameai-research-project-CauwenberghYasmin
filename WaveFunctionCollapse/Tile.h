#pragma once
#include"raylib.h"
#include <vector>



enum Directions
{
	North,
	East,
	South,
	West
};

struct connect
{
	Directions direction;
	std::vector<int> tiles;
};

struct GridPos
{
	int x;
	int y;
	
	GridPos(int x=0, int y=0) 
	   : x(x), y(y)
	{
	}
	
	bool operator==(const GridPos& a) const
	{
		return (x == a.x && y == a.y);
	}
};


class Tile
{
public:
	Tile(int tileN) noexcept;
	int tileInstanceNumber;
	std::vector<connect> connections;
	std::vector<int> possibilities; //number 1-16!
	
	Vector2 position{};
	GridPos gridPOsition{};
	
	std::vector<Tile*> GetAllNeighbours(int gridSize,  std::vector<Tile>& screenTiles);
	Tile* GetEastNeighbor(int gridSize,  std::vector<Tile>& screenTiles);
	Tile* GetSouthNeighbor(int gridSize,  std::vector<Tile>& screenTiles);
	Tile* GetWestNeighbor(int gridSize,  std::vector<Tile>& screenTiles);
	int GiveRandTileOption(); //give rand enthropy tile to use + set own enthorpy to 0 
	void Reset();
	
private:
	
	static Tile* FindTileWithGridPos(std::vector<Tile>& screenTiles, GridPos pos);
};


