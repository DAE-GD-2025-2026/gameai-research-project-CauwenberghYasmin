#include "raylib.h"
#include <iostream>
#include <stack>
#include <vector>
#include "Tile.h"
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

void DrawLines(int screenWidth);
void ReserveTiles(std::vector<std::vector<connect>>& allTiles);
void Grids(int screenWidth, std::vector<Tile>& screenTiles);
void LoadTileTextures(std::vector<Texture2D>& tilesTextures);
Tile* GetLowestEnthropy(std::vector<Tile>& screenTiles);
bool ClickedInside(Texture2D image, Vector2 drawPosition);
int indexCounter{0};

int main()
{
    constexpr int screenWidth = 792;
    constexpr int screenHeight = 792 + 100;
    
    std::vector<std::vector<connect>> allTiles;
    std::vector<Tile> screenTiles;

    bool isDoneGenerating {true};
    bool isDrawingBeginScreen{true};
    constexpr int gridSize = 8;

    InitWindow(screenWidth, screenHeight, "Wave collapse Function");
    SetTargetFPS(60);
    
    Texture2D TileSet =  LoadTexture("Resources/tileset.png");
    Texture2D resetButton =  LoadTexture("Resources/Reset.png");
    Texture2D cretaeButton =  LoadTexture("Resources/Create.png");
    std::vector<Texture2D> tilesTextures;
    

    while (!WindowShouldClose())
    {
        
        if (tilesTextures.empty())
        {
             LoadTileTextures(tilesTextures);
            ReserveTiles(allTiles);
            Grids(screenWidth, screenTiles);
        }
        BeginDrawing();
        constexpr Color darkBlue = { 10, 10, 10, 255 };
        ClearBackground(darkBlue);
        
        if (isDrawingBeginScreen)
        {
            DrawTextureEx(TileSet, Vector2 {0,0}, 0, 6, WHITE);  //make actual tile scale 3
            DrawLines(screenWidth);
            //std::cout<<"draw sceen at start!\n";
        }
        DrawTextureEx(resetButton, Vector2{screenWidth/6, screenHeight - 100, } , 0, 1, WHITE); 
        DrawTextureEx(cretaeButton, Vector2{ screenWidth/2, screenHeight - 100, } , 0, 1, WHITE); 
        //check drawing buttons
        
        
        //if press reset button:
        
        if (!isDoneGenerating)
        {
            allTiles.clear();
            screenTiles.clear();
            
            ReserveTiles(allTiles);
            Grids(screenWidth, screenTiles);
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ClickedInside(cretaeButton, Vector2{ screenWidth/2, screenHeight - 100, } ) )
         {
             isDrawingBeginScreen = false;
             isDoneGenerating = false;
             std::cout<<"creating\n";
            
            for (auto& tile: screenTiles)
            {
                tile.Reset();
            }
         }
        
        
         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ClickedInside(resetButton, Vector2{screenWidth/6, screenHeight - 100, }) )
        {
             isDrawingBeginScreen = true;
             isDoneGenerating = true;
             std::cout<<"clicking reset button!";
        }




        {
            //std::cout<<"generating!\n";
            std::stack<Tile*> stack;
            if (!isDoneGenerating)
            {
                indexCounter = 0; //resetting indec for ordered drawing later!

                //wavefunction collapse
                int randNumber {GetRandomValue(0, screenTiles.size()-1)}; 
                stack.push(&screenTiles[randNumber]);

                while (GetLowestEnthropy(screenTiles) != nullptr) //working with stack, maybe better by checking which of map lowest enthropy and != 0??
                {
                    Tile* currentTile = GetLowestEnthropy(screenTiles);
                    
                    int randPossibility {GetRandomValue(0, currentTile->possibilities.size()-1)};
                    int chosenTile = currentTile->possibilities[randPossibility];
                    DrawTextureEx(tilesTextures[chosenTile-1], currentTile->position, 0, 3, WHITE);
                    currentTile->tileInstanceNumber = chosenTile;
                    currentTile->possibilities.clear();
                    
                    std::vector<Tile*> neighbours = currentTile->GetAllNeighbours(gridSize, screenTiles);
                    
                    for (int i = 0; i < neighbours.size(); i++) //need raw forloop for the numbering in directions! 
                    {
                        if (neighbours[i] != nullptr && neighbours[i]->possibilities.size() != 0) //here go over all neighbours (except for the ones that have already collapsed)
                        {
                            std::vector<int> directionPossibleTiles = allTiles[chosenTile-1][i].tiles;  //check what the original options are (north of this tile without restrictions)
                            std::vector<int> limitedTiles {neighbours[i]->possibilities};//seeing what the direction can still be!
                            
                            std::vector<int> overlappingTiles;
                            std::sort(directionPossibleTiles.begin(), directionPossibleTiles.end());
                            std::sort(limitedTiles.begin(), limitedTiles.end());
                            
                            std::set_intersection(
                                directionPossibleTiles.begin(), directionPossibleTiles.end(),
                                limitedTiles.begin(), limitedTiles.end(),
                                std::back_inserter(overlappingTiles)
                            );
                            
                            neighbours[i]->possibilities = overlappingTiles; //update the new possibilities
                        }
                    }
                }
                isDrawingBeginScreen = false;
            }
                isDoneGenerating = true;
        }
        





        if (isDoneGenerating && !isDrawingBeginScreen)
        {
            //for (auto& tile: screenTiles)
            {
                if( screenTiles[indexCounter].tileInstanceNumber > 0 && screenTiles.size() > (indexCounter-1) )
                {
                    DrawTextureEx(tilesTextures[screenTiles[indexCounter].tileInstanceNumber -1], screenTiles[indexCounter].position, 0, 3, WHITE);
                    ++indexCounter;
                   // std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else
                {
                    isDoneGenerating = false; //this is a security mesure, if this triggers, it means the algorithme got stuck, forcing it to recalculate everything from scratch (vs unwinding!)
                    std::cout<<"Recreating, collapsing in the wrong order\n";
                    //this is pretty much impossible with our tiles
                    break;
                }
            }
        }






        if (isDrawingBeginScreen)
        {
            DrawTextureEx(TileSet, Vector2 {0,0}, 0, 6, WHITE);  //make actual tile scale 3
            DrawLines(screenWidth);
        }
        
        EndDrawing();
    }

    CloseWindow();
}

bool ClickedInside(Texture2D image, Vector2 drawPosition)
{
    Vector2 mousePosition = GetMousePosition();
    
    
    if (
        mousePosition.x >= drawPosition.x && mousePosition.x <= drawPosition.x + image.width &&
        mousePosition.y >= drawPosition.y && mousePosition.y <= drawPosition.y + image.height)
    {
        return true;
    }
    
    
    return false;
}


void DrawLines(int screenWidth)
{
    int SquareSize {screenWidth/4};
    DrawLine(SquareSize, 0, SquareSize, SquareSize* 4, WHITE);
    DrawLine(SquareSize*2, 0, SquareSize*2, SquareSize* 4, WHITE);
    DrawLine(SquareSize*3, 0, SquareSize*3, SquareSize* 4, WHITE); 
    
    DrawLine(0, SquareSize*3, SquareSize*4, SquareSize*3, WHITE);
    DrawLine(0, SquareSize*2, SquareSize*4, SquareSize*2, WHITE);
    DrawLine(0, SquareSize*1, SquareSize*4, SquareSize*1, WHITE);
}

void ReserveTiles(std::vector<std::vector<connect>>& allTiles) //use these vectors instead of the full class, save in size!
{
    allTiles.reserve(16);


    allTiles.emplace_back(std::vector<connect>{
       connect{Directions::North, {3, 4}},
       connect{Directions::East, {1,2,3,4,5,8,9,12,16}},
       connect{Directions::South, {5, 6, 7}},
       connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 16}}
    });

    allTiles.emplace_back((std::vector<connect>{ //tile 2
        connect{Directions::North, {3, 4}},
        connect{Directions::East, {1, 2,3,4,5,8,9,12,16}},
        connect{Directions::South, {5, 6, 7}},
        connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 16}}
        }));

    allTiles.emplace_back((std::vector<connect>{//tile 3
    connect{Directions::North, {3, 4}},
    connect{Directions::East, {1, 2,3,4,5,8,9,12,16}},
    connect{Directions::South, {1, 2, 3, 4, 5, 6, 7, 8}},
        connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 12, 16}}
    }));

    allTiles.emplace_back((std::vector<connect>{ //4
        connect{Directions::North, {3}},
        connect{Directions::East, {1,2,3,4,5,8,9,12,16}},
        connect{Directions::South, {1, 2, 3, 5, 6, 7, 8}},
        connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 12, 16}}
    }));

    allTiles.emplace_back((std::vector<connect>{ //5
        connect{Directions::North, {1,2,3,4,16}},
        connect{Directions::East, {6, 7, 13}},
        connect{Directions::South, {9, 13}},
        connect{Directions::West, {7, 1, 2, 3, 4, 8, 12, 16}}
    }));


    allTiles.emplace_back((std::vector<connect>{ //6
        connect{Directions::North, {1,2,3,4,16}},
        connect{Directions::East, {6, 7, 13}},
        connect{Directions::South, {10, 14}},
        connect{Directions::West, {5,6,15}}
    }));



    allTiles.emplace_back((std::vector<connect>{ //7
        connect{Directions::North, {1,2,3,4,16}},
        connect{Directions::East, {5, 1, 2, 3, 4, 8, 12, 16, 9}},
        connect{Directions::South, {11,15}},
        connect{Directions::West, {5, 6, 15}}
    }));

    allTiles.emplace_back((std::vector<connect>{ //8
      connect{Directions::North, {3,4}},
      connect{Directions::East, {5,1,2,3,4,16,12,8, 9}},
      connect{Directions::South, {12, 16}},
      connect{Directions::West, {7,11,1,2,3,4,8,12, 16}}
  }));


    allTiles.emplace_back((std::vector<connect>{ //9
          connect{Directions::North, {9, 5}},
          connect{Directions::East, {10,14,11,15}},
          connect{Directions::South, {9,13}},
          connect{Directions::West, {11, 7, 1, 2, 3, 4, 16, 12, 8}}
      }));

    allTiles.emplace_back((std::vector<connect>{ //10
         connect{Directions::North, {10, 14, 6, 13, 15}},
         connect{Directions::East, {10,14,11,15}},
         connect{Directions::South, {10,14}},
         connect{Directions::West, {9, 10, 14, 13}}
     }));


        allTiles.emplace_back((std::vector<connect>{ //11
         connect{Directions::North, {9, 10, 14, 13}},
         connect{Directions::East, {16, 12, 8, 4, 1, 2, 3, 9}},
         connect{Directions::South, {11, 15}},
         connect{Directions::West, {9, 10, 14, 13}}
        }));

    allTiles.emplace_back((std::vector<connect>{ //12
         connect{Directions::North, {12,8}},
         connect{Directions::East, {1,2,3,4, 5, 9, 12, 16, 8}},
         connect{Directions::South, {12, 16}},
         connect{Directions::West, {1,2,3,4, 7, 11, 8, 12, 16}}
     }));

    allTiles.emplace_back((std::vector<connect>{ //13
        connect{Directions::North, {9,5}},
        connect{Directions::East, {10,14,11,15}},
        connect{Directions::South, {10, 14}},
        connect{Directions::West, {5,6, 15}}
    }));


    allTiles.emplace_back((std::vector<connect>{ //14
        connect{Directions::North, {10,6, 13, 15}},
        connect{Directions::East, {10,14,11,15}},
        connect{Directions::South, {10, 14}},
        connect{Directions::West, {13, 9, 10, 14}}
    }));

    allTiles.emplace_back((std::vector<connect>{ //15
        connect{Directions::North, {11, 7}},
        connect{Directions::East, {6,7,13}},
        connect{Directions::South, {10, 14}},
        connect{Directions::West, {13, 9, 10, 14}}
    }));

    allTiles.emplace_back((std::vector<connect>{ //16
            connect{Directions::North, {12,8}},
            connect{Directions::East, {16, 12, 8, 4, 1, 2, 3, 9, 5}},
            connect{Directions::South, {5, 6, 7}},
            connect{Directions::West, {16, 12, 8, 4, 1, 2, 3, 11, 7}}
        }));

}

void Grids(int screenWidth, std::vector<Tile>& screenTiles)
{
    const int gridLength {8}; //8x8 grid!
    const int gridSize { screenWidth/8 };
    
    for (int i =0; i < gridLength; i++)
    {
        for (int j =0; j < gridLength; j++)
        {
            Tile tile = Tile(0);
            
            //grid.pos.x = i*gridSize;
            //grid.pos.y = j*gridSize;
            tile.position.x = static_cast<int>(i * gridSize);
            tile.position.y = static_cast<int>(j*gridSize);
            
            //tile.gridPos = (i,j)
            tile.gridPOsition = GridPos(i, j);
            
            //enthropy/possibilities is already set.
            
            //push tile to screenTiles
            screenTiles.emplace_back(tile);
        }
    }
}

Tile* GetLowestEnthropy(std::vector<Tile>& screenTiles)
{
    Tile* lowestEnthropyTile { nullptr};
    int lowestEnthropy {17}; //only 16 diff tiles!
    
    for (Tile& tile : screenTiles)
    {
        if (tile.possibilities.size() < lowestEnthropy &&  !tile.possibilities.empty())
        {
            lowestEnthropyTile = &tile;
            lowestEnthropy = tile.possibilities.size();
        }
    }
    
    return lowestEnthropyTile; //normaly return a random one, here we just return the last (should not impact the algorithm)
}

void LoadTileTextures(std::vector<Texture2D>& tilesTextures)
{
    for (int i =1; i <= 16; i++)
    {
        std::string filepath{"Resources/layer"};
        std::string number {std::to_string(i)};
        std::string fileName {filepath + number+ ".png"};
       //std::cout<<fileName<<std::endl;
        tilesTextures.emplace_back(LoadTexture(fileName.c_str()));
    }
}