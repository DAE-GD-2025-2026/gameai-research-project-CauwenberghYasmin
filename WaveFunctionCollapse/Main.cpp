#include "raylib.h"
#include <iostream>
#include <stack>
#include <vector>
#include "Tile.h"
#include <string>
#include <algorithm>

void DrawLines(int screenWidth);
void ReserveTiles(std::vector<Tile>& allTiles);
void Grids(int screenWidth, std::vector<Tile>& screenTiles);
void LoadTileTextures(std::vector<Texture2D>& tilesTextures);
Tile* GetLowestEnthropy(std::vector<Tile>& screenTiles);
bool ClickedInside(Texture2D image, Vector2 drawPosition);

int main()
{
    constexpr int screenWidth = 792;
    constexpr int screenHeight = 792 + 100;
    
    std::vector<Tile> allTiles;
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
        constexpr Color darkBlue = { 10, 10, 43, 255 };
        ClearBackground(darkBlue);
        
        if (isDrawingBeginScreen)
        {
            DrawTextureEx(TileSet, Vector2 {0,0}, 0, 6, WHITE);  //make actual tile scale 3
            DrawLines(screenWidth);
            std::cout<<"draw sceen at start!\n";
        }
        DrawTextureEx(resetButton, Vector2{screenWidth/6, screenHeight - 100, } , 0, 1, WHITE); 
        DrawTextureEx(cretaeButton, Vector2{ screenWidth/2, screenHeight - 100, } , 0, 1, WHITE); 
        //check drawing buttons
        
        
        //if press reset button:
        
        if (!isDoneGenerating)
        {
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
                //-------------------------------------
                // ReserveTiles(allTiles);
                // Grids(screenWidth, screenTiles);
                //-------------------------------------
                
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
                    
                    for (int i = 0; i < neighbours.size(); i++) //need raw forloop for the numbering!
                    {
                        if (neighbours[i] != nullptr && neighbours[i]->possibilities.size() != 0) //here go over all neighbours
                        {
                            std::vector<int> directionPossibleTiles = allTiles[chosenTile-1].connections[i].tiles;  //check what the original options are (north of this tile without restrictions)
                            int enthropy {static_cast<int>(neighbours[i]->possibilities.size())}; //seeing what the direction can still be!
                            std::vector<int> limitedTiles {neighbours[i]->possibilities};
                            
                            std::vector<int> overlappingTiles;
                            
                            std::sort(directionPossibleTiles.begin(), directionPossibleTiles.end());
                            std::sort(limitedTiles.begin(), limitedTiles.end());
                            
                            std::set_intersection(
                                directionPossibleTiles.begin(), directionPossibleTiles.end(),
                                limitedTiles.begin(), limitedTiles.end(),
                                std::back_inserter(overlappingTiles)
                            );
                            
                            neighbours[i]->possibilities = overlappingTiles;
                            int enthropyAfter {static_cast<int>(neighbours[i]->possibilities.size())};
                        }
                    }
                }
                isDrawingBeginScreen = false;
            }
                isDoneGenerating = true;
        }
        
        
        if (isDoneGenerating && !isDrawingBeginScreen)
        {
            for (auto& tile: screenTiles)
            {
                if( tile.tileInstanceNumber > 0)
                {
                    DrawTextureEx(tilesTextures[tile.tileInstanceNumber -1], tile.position, 0, 3, WHITE);
                }
            }
        }
        
        if (isDrawingBeginScreen)
        {
            DrawTextureEx(TileSet, Vector2 {0,0}, 0, 6, WHITE);  //make actual tile scale 3
            DrawLines(screenWidth);
            std::cout<<"DrawingBeginScreenCalled!";
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

void ReserveTiles(std::vector<Tile>& allTiles)
{
    allTiles.reserve(16);
    
    Tile tile1 = Tile(1);
    tile1.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile1.connections.emplace_back( connect{Directions::East, {1,2,3,4,5,8,9,12,16}});
    tile1.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile1.connections.emplace_back( connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 16}});
    allTiles.emplace_back(tile1);


    Tile tile2 = Tile(2);
    tile2.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile2.connections.emplace_back( connect{Directions::East, {1, 2,3,4,5,8,9,12,16}});
    tile2.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile2.connections.emplace_back( connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 16}});
    allTiles.emplace_back(tile2);

    Tile tile3 = Tile(3);
    tile3.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile3.connections.emplace_back( connect{Directions::East, {1, 2, 3, 4, 5, 8, 9, 12, 16}});
    tile3.connections.emplace_back( connect{Directions::South, {1, 2, 3, 4, 5, 6, 7, 8}});
    tile3.connections.emplace_back( connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 12, 16}});
    allTiles.emplace_back(tile3);

    Tile tile4 = Tile(4);
    tile4.connections.emplace_back( connect{Directions::North, {3}} ); //no fire above fire (personal preference)
    tile4.connections.emplace_back( connect{Directions::East, {1, 2, 3, 4, 5, 8, 9, 12, 16}});
    tile4.connections.emplace_back( connect{Directions::South, {1, 2, 3, 5, 6, 7, 8}});
    tile4.connections.emplace_back( connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 12, 16}});
    allTiles.emplace_back(tile4);


    Tile tile5 = Tile(5);
    tile5.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile5.connections.emplace_back( connect{Directions::East, {6, 7, 13}});
    tile5.connections.emplace_back( connect{Directions::South, {9, 13}});
    tile5.connections.emplace_back( connect{Directions::West, {7, 1, 2, 3, 4, 8, 12, 16}});
    allTiles.emplace_back(tile5);

        Tile tile6 = Tile(6);
    tile6.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile6.connections.emplace_back( connect{Directions::East, {6, 7, 13}});
    tile6.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile6.connections.emplace_back( connect{Directions::West, {5, 6, 15}});
    allTiles.emplace_back(tile6);


        Tile tile7 = Tile(7);
    tile7.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile7.connections.emplace_back( connect{Directions::East, {5, 1, 2, 3, 4, 8, 12, 16, 9}});
    tile7.connections.emplace_back( connect{Directions::South, {11,15}});
    tile7.connections.emplace_back( connect{Directions::West, {5, 6, 15}});
    allTiles.emplace_back(tile7);

        Tile tile8 = Tile(8);
    tile8.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile8.connections.emplace_back( connect{Directions::East, {5,1,2,3,4,16,12,8, 9}});
    tile8.connections.emplace_back( connect{Directions::South, {12, 16}});
    tile8.connections.emplace_back( connect{Directions::West, {7,11,1,2,3,4,8,12, 16}});
    allTiles.emplace_back(tile8);

        Tile tile9 = Tile(9);
    tile9.connections.emplace_back( connect{Directions::North, {9, 5}} );
    tile9.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile9.connections.emplace_back( connect{Directions::South, {9,13}});
    tile9.connections.emplace_back( connect{Directions::West, {11, 7, 1, 2, 3, 4, 16, 12, 8}});
    allTiles.emplace_back(tile9);

        Tile tile10 = Tile(10);
    tile10.connections.emplace_back( connect{Directions::North, {10, 14, 6, 13, 15}} );
    tile10.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile10.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile10.connections.emplace_back( connect{Directions::West, {9, 10, 14, 13}});
    allTiles.emplace_back(tile10);

        Tile tile11 = Tile(11);
    tile11.connections.emplace_back( connect{Directions::North, {7, 11}} );
    tile11.connections.emplace_back( connect{Directions::East, {16, 12, 8, 4, 1, 2, 3, 9}});
    tile11.connections.emplace_back( connect{Directions::South, {11, 15}});
    tile11.connections.emplace_back( connect{Directions::West, {9, 10, 14, 13}});
    allTiles.emplace_back(tile11);

        Tile tile12 = Tile(12);
    tile12.connections.emplace_back( connect{Directions::North, {12, 8}} );
    tile12.connections.emplace_back( connect{Directions::East, {1,2,3,4, 5, 9, 12, 16, 8}});
    tile12.connections.emplace_back( connect{Directions::South, {12, 16}});
    tile12.connections.emplace_back( connect{Directions::West, {1,2,3,4, 7, 11, 8, 12, 16}});
    allTiles.emplace_back(tile12);

        Tile tile13 = Tile(13);
    tile13.connections.emplace_back( connect{Directions::North, {9,5}} );
    tile13.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile13.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile13.connections.emplace_back( connect{Directions::West, {5,6, 15}});
    allTiles.emplace_back(tile13);


        Tile tile14 = Tile(14);
    tile14.connections.emplace_back( connect{Directions::North,{10,6, 13, 15}} );
    tile14.connections.emplace_back( connect{Directions::East, {14,10,15,11}});
    tile14.connections.emplace_back( connect{Directions::South, {14, 10}});
    tile14.connections.emplace_back( connect{Directions::West, {13, 9, 10, 14}});
    allTiles.emplace_back(tile14);

        Tile tile15 = Tile(15);
    tile15.connections.emplace_back( connect{Directions::North,{11, 7} });
    tile15.connections.emplace_back( connect{Directions::East, {6,7, 13}});
    tile15.connections.emplace_back( connect{Directions::South, {14, 10}});
    tile15.connections.emplace_back( connect{Directions::West, {13, 9, 10, 14}});
    allTiles.emplace_back(tile15);

        Tile tile16 = Tile(16);
    tile16.connections.emplace_back( connect{Directions::North, {12, 8}} );
    tile16.connections.emplace_back( connect{Directions::East, {16, 12, 8, 4, 1, 2, 3, 9, 5}});
    tile16.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile16.connections.emplace_back( connect{Directions::West, {16, 12, 8, 4, 1, 2, 3, 11, 7}});
    allTiles.emplace_back(tile16);
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