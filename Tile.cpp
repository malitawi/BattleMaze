#include "Tile.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

using std::shared_ptr;
using std::cout; using std::endl;

Tile::Tile(): currPlayer(NULL), occupied(false)
{
}

Tile::Tile(int inX, int inY, TileType inType, Walkable inWalk): x(inX), y(inY), 
    Terrain(inType), CanWalk(inWalk), currPlayer(NULL), occupied(false)
{
}

Tile::~Tile()
{
    currPlayer = NULL;
}

void Tile::SetTileStats(int inX, int inY, TileType inType, Walkable inWalk)
{
    x = inX;
    y = inY;
    Terrain = inType;
    CanWalk = inWalk;
}

bool Tile::IsOccupied()
{
    return occupied;
}

void Tile::AssignPlayer(shared_ptr<Player> inPlayer)
{
    currPlayer = inPlayer;
    //cout << "(" << x << ", " << y << ") set to ";
    if (currPlayer == NULL){
        occupied = false;
        //cout << "no player." << endl;
    }
    else{
        occupied = true;
        //cout << "containg a player." << endl;
    }
}

shared_ptr<Player> Tile::GetPlayer()
{
    if (IsOccupied()) {
        return currPlayer;
    }
    return nullptr;
}

void Tile::PlayerHit(int dmg)
{
    currPlayer->TakeDamage(dmg);
}

int Tile::PlayerAttacks()
{
    // return currPlayer->Attack();
    return 1;
}

Walkable Tile::IsTileWalkable()
{
    return CanWalk;
}
