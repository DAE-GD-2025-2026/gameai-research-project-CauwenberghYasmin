#include "raylib.h"
#include <iostream>
#include <vector>
#include "Tile.h"
#include <string>

void DrawLines(int screenWidth);
void ReserveTiles(std::vector<Tile>& allTiles);
void Grids(int screenWidth, std::vector<Tile>& screenTiles);
void LoadTileTextures(std::vector<Texture2D>& tilesTextures);

int main()
{
    constexpr Color darkBlue = { 10, 10, 43, 255 };
    constexpr int screenWidth = 792 ;
    constexpr int screenHeight = 792 + 100;
    std::vector<Tile> allTiles;
    std::vector<Tile> screenTiles;


    InitWindow(screenWidth, screenHeight, "Wave collapse Function");
    SetTargetFPS(60);
    
    Texture2D TileSet =  LoadTexture("Resources/tileset.png");
    std::vector<Texture2D> tilesTextures;


    while (!WindowShouldClose())
    {
        if (tilesTextures.empty())
        {
             LoadTileTextures(tilesTextures);
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        
        DrawTextureEx(TileSet, Vector2 {0,0}, 0, 6, WHITE);  //make actual tile scale 3!
        DrawLines(screenWidth);
        ReserveTiles(allTiles);
        Grids(screenWidth, screenTiles);
        
        //register clicks
        //click button (reset and solve!)
        //don't draw lines anymore!
        
        //try drawing
        for (const auto& tile : screenTiles) //cant scale rectangles of specific drawings, so have to save rect images seperatly
        {
            //DrawTextureEx(TileSet, tile.position, 0, 0.8, WHITE);
            DrawTextureEx(tilesTextures[0], tile.position, 0, 3, WHITE); 
        }
        
      
    
        EndDrawing();
    }

    CloseWindow();
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
    tile1.connections.emplace_back( connect{Directions::East, {1,2,3,4,5,8,9,12,13,16}});
    tile1.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile1.connections.emplace_back( connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 15, 16}});
    allTiles.emplace_back(tile1);


    Tile tile2 = Tile(2);
    tile2.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile2.connections.emplace_back( connect{Directions::East, {1, 2,3,4,5,8,9,12,13,16}});
    tile2.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile2.connections.emplace_back( connect{Directions::West, {1,2, 3, 4, 7, 8, 11, 12, 15, 16}});
    allTiles.emplace_back(tile2);

    Tile tile3 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile2.connections.emplace_back( connect{Directions::East, {1, 2, 3, 4, 5, 8, 9, 12, 13, 16}});
    tile2.connections.emplace_back( connect{Directions::South, {1, 2, 3, 4, 5, 6, 7, 8}});
    tile2.connections.emplace_back( connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 15, 12, 16}});
    allTiles.emplace_back(tile3);

    Tile tile4 = Tile(4);
    tile2.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile2.connections.emplace_back( connect{Directions::East, {1, 2, 3, 4, 5, 8, 9, 12, 13, 16}});
    tile2.connections.emplace_back( connect{Directions::South, {1, 2, 3, 4, 5, 6, 7, 8}});
    tile2.connections.emplace_back( connect{Directions::West, {1, 2, 3, 4, 7, 8, 11, 15, 12, 16}});
    allTiles.emplace_back(tile4);


    Tile tile5 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile2.connections.emplace_back( connect{Directions::East, {6, 7}});
    tile2.connections.emplace_back( connect{Directions::South, {9}});
    tile2.connections.emplace_back( connect{Directions::West, {7, 1, 2, 3, 4, 8, 12, 16}});
    allTiles.emplace_back(tile5);

        Tile tile6 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile2.connections.emplace_back( connect{Directions::East, {6, 7}});
    tile2.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile2.connections.emplace_back( connect{Directions::West, {5, 6}});
    allTiles.emplace_back(tile6);


        Tile tile7 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {1,2,3,4,16}} );
    tile2.connections.emplace_back( connect{Directions::East, {6, 7}});
    tile2.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile2.connections.emplace_back( connect{Directions::West, {5, 6}});
    allTiles.emplace_back(tile7);

        Tile tile8 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {3, 4}} );
    tile2.connections.emplace_back( connect{Directions::East, {5,6,1,2,3,4,16,12,8}});
    tile2.connections.emplace_back( connect{Directions::South, {12, 16}});
    tile2.connections.emplace_back( connect{Directions::West, {7,11,1,2,3,4,8,12}});
    allTiles.emplace_back(tile8);

        Tile tile9 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {9, 5}} );
    tile2.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile2.connections.emplace_back( connect{Directions::South, {9,13}});
    tile2.connections.emplace_back( connect{Directions::West, {11, 7, 1, 2, 3, 4, 16, 12, 8}});
    allTiles.emplace_back(tile9);

        Tile tile10 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {10, 14, 6}} );
    tile2.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile2.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile2.connections.emplace_back( connect{Directions::West, {9, 10, 14, 13}});
    allTiles.emplace_back(tile10);

        Tile tile11 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {7, 11}} );
    tile2.connections.emplace_back( connect{Directions::East, {16, 12, 8, 4, 1, 2, 3, 9}});
    tile2.connections.emplace_back( connect{Directions::South, {11, 15}});
    tile2.connections.emplace_back( connect{Directions::West, {9, 10, 14, 13}});
    allTiles.emplace_back(tile11);

        Tile tile12 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {12, 8}} );
    tile2.connections.emplace_back( connect{Directions::East, {1,2,3,4, 5, 9}});
    tile2.connections.emplace_back( connect{Directions::South, {12, 16}});
    tile2.connections.emplace_back( connect{Directions::West, {1,2,3,4, 7, 11}});
    allTiles.emplace_back(tile12);

        Tile tile13 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {9,5}} );
    tile2.connections.emplace_back( connect{Directions::East, {10,14,11,15}});
    tile2.connections.emplace_back( connect{Directions::South, {10, 14}});
    tile2.connections.emplace_back( connect{Directions::West, {5,6}});
    allTiles.emplace_back(tile13);


        Tile tile14 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North,{10,6}} );
    tile2.connections.emplace_back( connect{Directions::East, {14,10,15,11}});
    tile2.connections.emplace_back( connect{Directions::South, {14, 10}});
    tile2.connections.emplace_back( connect{Directions::West, {13, 9, 10, 14}});
    allTiles.emplace_back(tile14);

        Tile tile15 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North,{11, 7} });
    tile2.connections.emplace_back( connect{Directions::East, {6,7}});
    tile2.connections.emplace_back( connect{Directions::South, {14, 10}});
    tile2.connections.emplace_back( connect{Directions::West, {13, 9, 10, 14}});
    allTiles.emplace_back(tile15);

        Tile tile16 = Tile(3);
    tile2.connections.emplace_back( connect{Directions::North, {12, 8}} );
    tile2.connections.emplace_back( connect{Directions::East, {16, 12, 8, 4, 1, 2, 3}});
    tile2.connections.emplace_back( connect{Directions::South, {5, 6, 7}});
    tile2.connections.emplace_back( connect{Directions::West, {16, 12, 8, 4, 1, 2, 3}});
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

void LoadTileTextures(std::vector<Texture2D>& tilesTextures)
{
    for (int i =1; i <= 16; i++)
    {
        std::string filepath{"Resources/layer"};
        std::string number {std::to_string(i)};
        std::string fileName {filepath + number+ ".png"};
        std::cout<<fileName<<std::endl;
        tilesTextures.emplace_back(LoadTexture("fileName"));
    }
}