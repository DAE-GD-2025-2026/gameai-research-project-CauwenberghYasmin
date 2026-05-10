

enum Directions
{
    North,
    East,
    South,
    West
};

class Tile{
    public:

    int tileNumber;
    std::vector<connect> connections;
    std::vector<int> enthropy; //number 1-16!
    //in constructor
    //already reserve 4 for vector!
}

  

//----------------1------------------------
std::vector<std::unique_pointer<Tile>> allTiles;
allTiles.reserve(16); //have 16 tiles 

//do they really need to be smartpointers? or can I just create an instance?
std::make_unique<Tile> tile1  {}
tile1.connections.emplace_back( connect{Directions::North, 3, 4} );
tile1.connections.emplace_back( connect{Directions::East, 1, 2,3,4,5,8,9,12,13,16});
tile1.connections.emplace_back( connect{Directions::South, 5,, 6, 7});
tile1.connections.emplace_back( connect{Directions::West, 1,2, 3, 4, 7, 8, 11, 12, 15, 16});
allTiles.emplace_back(tile1);


std::make_unique<Tile> tile2{}
tile2.connections.emplace_back( connect{Directions::North, 3, 4} );
tile2.connections.emplace_back( connect{Directions::East, 1, 2,3,4,5,8,9,12,13,16});
tile2.connections.emplace_back( connect{Directions::South, 5,, 6, 7});
tile2.connections.emplace_back( connect{Directions::West, 1,2, 3, 4, 7, 8, 11, 12, 15, 16});
allTiles.emplace_back(tile2);

std::make_unique<Tile> tile3{}
tile2.connections.emplace_back( connect{Directions::North, 3, 4} );
tile2.connections.emplace_back( connect{Directions::East, 1, 2, 3, 4, 5, 8, 9, 12, 13, 16});
tile2.connections.emplace_back( connect{Directions::South, 1, 2, 3, 4, 5, 6, 7, 8});
tile2.connections.emplace_back( connect{Directions::West, 1, 2, 3, 4, 7, 8, 11, 15, 12, 16});
allTiles.emplace_back(tile3);

std::make_unique<Tile> tile4{}
tile2.connections.emplace_back( connect{Directions::North, 3, 4} );
tile2.connections.emplace_back( connect{Directions::East, 1, 2, 3, 4, 5, 8, 9, 12, 13, 16});
tile2.connections.emplace_back( connect{Directions::South, 1, 2, 3, 4, 5, 6, 7, 8});
tile2.connections.emplace_back( connect{Directions::West, 1, 2, 3, 4, 7, 8, 11, 15, 12, 16});
allTiles.emplace_back(tile4);


std::make_unique<Tile> tile5{}
tile2.connections.emplace_back( connect{Directions::North, 1,2,3,4,16} );
tile2.connections.emplace_back( connect{Directions::East, 6, 7});
tile2.connections.emplace_back( connect{Directions::South, 9});
tile2.connections.emplace_back( connect{Directions::West, 7, 1, 2, 3, 4, 8, 12, 16});
allTiles.emplace_back(tile5);

std::make_unique<Tile> tile6{}
tile2.connections.emplace_back( connect{Directions::North, 1,2,3,4,16} );
tile2.connections.emplace_back( connect{Directions::East, 6, 7});
tile2.connections.emplace_back( connect{Directions::South, 10, 14});
tile2.connections.emplace_back( connect{Directions::West, 5, 6});
allTiles.emplace_back(tile6);


std::make_unique<Tile> tile7{}
tile2.connections.emplace_back( connect{Directions::North, 1,2,3,4,16} );
tile2.connections.emplace_back( connect{Directions::East, 6, 7});
tile2.connections.emplace_back( connect{Directions::South, 10, 14});
tile2.connections.emplace_back( connect{Directions::West, 5, 6});
allTiles.emplace_back(tile7);

std::make_unique<Tile> tile8{}
tile2.connections.emplace_back( connect{Directions::North, 3, 4} );
tile2.connections.emplace_back( connect{Directions::East, 5,6,1,2,3,4,16,12,8});
tile2.connections.emplace_back( connect{Directions::South, 12, 16});
tile2.connections.emplace_back( connect{Directions::West, 7,11,1,2,3,4,8,12});
allTiles.emplace_back(tile8);

std::make_unique<Tile> tile9{}
tile2.connections.emplace_back( connect{Directions::North, 9, 5} );
tile2.connections.emplace_back( connect{Directions::East, 10,14,11,15});
tile2.connections.emplace_back( connect{Directions::South, 9,13});
tile2.connections.emplace_back( connect{Directions::West, 11, 7, 1, 2, 3, 4, 16, 12, 8});
allTiles.emplace_back(tile9);

std::make_unique<Tile> tile10{}
tile2.connections.emplace_back( connect{Directions::North, 10, 14, 6} );
tile2.connections.emplace_back( connect{Directions::East, 10,14,11,15});
tile2.connections.emplace_back( connect{Directions::South, 10, 14});
tile2.connections.emplace_back( connect{Directions::West, 9, 10, 14, 13});
allTiles.emplace_back(tile10);

std::make_unique<Tile> tile11{}
tile2.connections.emplace_back( connect{Directions::North, 7, 11} );
tile2.connections.emplace_back( connect{Directions::East, 16, 12, 8, 4, 1, 2, 3, 9});
tile2.connections.emplace_back( connect{Directions::South, 11, 15});
tile2.connections.emplace_back( connect{Directions::West, 9, 10, 14, 13});
allTiles.emplace_back(tile11);

std::make_unique<Tile> tile12{}
tile2.connections.emplace_back( connect{Directions::North, 12, 8} );
tile2.connections.emplace_back( connect{Directions::East, 1,2,3,4, 5, 9});
tile2.connections.emplace_back( connect{Directions::South, 12, 16});
tile2.connections.emplace_back( connect{Directions::West, 1,2,3,4, 7, 11});
allTiles.emplace_back(tile12);

std::make_unique<Tile> tile13{}
tile2.connections.emplace_back( connect{Directions::North, 9,5} );
tile2.connections.emplace_back( connect{Directions::East, 10,14,11,15});
tile2.connections.emplace_back( connect{Directions::South, 10, 14});
tile2.connections.emplace_back( connect{Directions::West, 5,6});
allTiles.emplace_back(tile13);


std::make_unique<Tile> tile14{}
tile2.connections.emplace_back( connect{Directions::North,10,6} );
tile2.connections.emplace_back( connect{Directions::East, 14,10,15,11});
tile2.connections.emplace_back( connect{Directions::South, 14, 10});
tile2.connections.emplace_back( connect{Directions::West, 13, 9, 10, 14});
allTiles.emplace_back(tile14);

std::make_unique<Tile> tile15{}
tile2.connections.emplace_back( connect{Directions::North,11, 7} );
tile2.connections.emplace_back( connect{Directions::East, 6,7});
tile2.connections.emplace_back( connect{Directions::South, 14, 10});
tile2.connections.emplace_back( connect{Directions::West, 13, 9, 10, 14});
allTiles.emplace_back(tile15);

std::make_unique<Tile> tile16{}
tile2.connections.emplace_back( connect{Directions::North, 12, 8} );
tile2.connections.emplace_back( connect{Directions::East, 16, 12, 8, 4, 1, 2, 3});
tile2.connections.emplace_back( connect{Directions::South, 5, 6, 7});
tile2.connections.emplace_back( connect{Directions::West, 16, 12, 8, 4, 1, 2, 3});
allTiles.emplace_back(tile16);