#include "GameMap.h"
#include "Tile.h"
#include "Player.h"
#include "GameController.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <memory>

using std::string;
using std::ifstream; using std::getline;
using std::shared_ptr; using std::make_shared;
using std::cerr; using endl;

shared_ptr<GameMap> LoadGameBoard(string);

int main(int argc, char* argv[])
{
    try {
        shared_ptr<GameMap> World = LoadGameBoard("gameboard1.txt");
        GameController game;
        game.run(World);
    } catch (Error er) {
        cerr << er.msg << endl;
    }
    return 0;
}

/********************************************************************************
    Reads in the text file that represents the actual game board
    - Throws an error if the file could not be opened
    - Returns a shared_ptr of the GameMap
*********************************************************************************/
shared_ptr<GameMap> LoadGameBoard(string filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()){
        throw Error("Error, could not open file\n");
        return nullptr;
    }
    int width, height;
    string clr, tile_label;
    TileType tile_type;
    Walkable walk;
    infile >> width >> height;
    getline(infile, clr);
    shared_ptr<GameMap> World(new GameMap(width, height));

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            infile >> tile_label;
            walk = WALKABLE;
            if (tile_label == "G"){
                tile_type = GRASS;
            }
            else if (tile_label == "D"){
                tile_type = DIRT;
            }
            else if (tile_label == "S"){
                tile_type = STONE;
            }
            else if (tile_label == "T"){
                tile_type = TREE;
                walk = NOT_WALKABLE;
            }
            World->SetTile(j, i, tile_type, walk);
        }
        getline(infile, clr);
    }
    infile.close();
    return World;
}
