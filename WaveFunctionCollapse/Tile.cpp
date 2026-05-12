#include "raylib.h"
#include "Tile.h"
#include <iostream>


Tile::Tile(int tileN) noexcept:
    tileInstanceNumber ( tileN)
{
    connections.reserve(4);
    possibilities.reserve(16);
    
    for (int i = 1; i <= 16; i++)
    {
        possibilities.push_back(i);
    }
}


std::vector<Tile*> Tile::GetAllNeighbours(int gridSize,  std::vector<Tile>& screenTiles)
{
    std::vector<Tile*> neighbours;
    
    if (gridPOsition.y -1 < 0)
    {
        neighbours.push_back(nullptr);
    } 
    else
    {
        GridPos northPos {gridPOsition.x, gridPOsition.y -1};
        neighbours.push_back( FindTileWithGridPos(screenTiles, northPos));
    }
    
    
    if (gridPOsition.x + 1 > 7)
    {
        neighbours.push_back(nullptr);
    } 
    else
    {
        GridPos eastPos {gridPOsition.x + 1, gridPOsition.y};
        neighbours.push_back (FindTileWithGridPos(screenTiles, eastPos));
    }
    
    
    if (gridPOsition.y + 1 > 7)
    {
        neighbours.push_back(nullptr);
    } 
    else
    {
        GridPos southPos {gridPOsition.x, gridPOsition.y + 1};
        neighbours.push_back  (FindTileWithGridPos(screenTiles, southPos));
    }
    
    
    if (gridPOsition.x - 1 < 0)
    {
        neighbours.push_back(nullptr);
    }
    else
    {
        
        GridPos  westPos {gridPOsition.x + 1, gridPOsition.y};
        neighbours.push_back (FindTileWithGridPos(screenTiles,  westPos));
    }
    
    return neighbours;
}   

Tile* Tile::GetSouthNeighbor(int gridSize,  std::vector<Tile>& screenTiles)
{
    if (gridPOsition.y + 1 > 7)
    {
        return nullptr;
    } 
    
    GridPos southPos {gridPOsition.x, gridPOsition.y + 1};
    return FindTileWithGridPos(screenTiles, southPos);
} 

Tile* Tile::GetEastNeighbor(int gridSize,  std::vector<Tile>& screenTiles)
{
    if (gridPOsition.x + 1 > 7)
    {
        return nullptr;
    } 
    
    GridPos eastPos {gridPOsition.x + 1, gridPOsition.y};
    return FindTileWithGridPos(screenTiles, eastPos);
} 

Tile* Tile::GetWestNeighbor(int gridSize,  std::vector<Tile>& screenTiles)
{
    if (gridPOsition.x - 1 < 0)
    {
        return nullptr;
    } 
    
    GridPos  westPos {gridPOsition.x + 1, gridPOsition.y};
    return FindTileWithGridPos(screenTiles,  westPos);
}

Tile* Tile::FindTileWithGridPos(std::vector<Tile>& screenTiles, GridPos pos)
{
    for (auto& tile: screenTiles)
    {
        if (tile.gridPOsition == pos)
        {
            return &tile;
        }
    }
    
    return nullptr;
}


int Tile::GiveRandTileOption()
{
    int sizeArray { static_cast<int>(possibilities.size())}; //make sure when taking poss away to remove them fully from the vector
    int randNumber {GetRandomValue(0, sizeArray-1)};
    
    return possibilities[randNumber];
}

void Tile::Reset()
{
    connections.clear();
    possibilities.clear();
    tileInstanceNumber = 0;
    
    connections.reserve(4);
    possibilities.reserve(16);
    
    for (int i = 1; i <= 16; i++)
    {
        possibilities.push_back(i);
    }
}