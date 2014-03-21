#include "GameMap.h"
#include "Tile.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

using std::shared_ptr;

GameMap::GameMap()
{
}

GameMap::GameMap(int inWidth, int inHeight): width(inWidth), height(inHeight)
{
    Map = new Tile*[height];
    for (int i = 0; i < height; i++){
        Map[i] = new Tile[width];
    }
}

GameMap::~GameMap()
{
    players.clear();
    for (int i = 0; i < height; i++){
        delete [] Map[i];
        Map[i] = NULL;
    }
    delete [] Map;
    Map = NULL;
}

void GameMap::SetTile(int x, int y, TileType tile, Walkable canWalk)
{
    Map[y][x].SetTileStats(x, y, tile, canWalk);
}

bool GameMap::IsTileOccupied(int x, int y)
{
    return Map[y][x].IsOccupied();
}

void GameMap::SetTileOccupant(int x, int y, shared_ptr<Player> setPlayer)
{
    Map[y][x].AssignPlayer(setPlayer);
}

bool GameMap::IsValidSpot(int x, int y)
{
    return (x >= 0 && x < width && y >= 0 && y < height && Map[y][x].IsTileWalkable() == WALKABLE);
}

void GameMap::AttackPlayer(shared_ptr<Player> attacker, shared_ptr<Player> victim)
{
    PlayerCoordinates Attacker(attacker->GetXSpot(), attacker->GetYSpot());
    PlayerCoordinates Victim(victim->GetXSpot(), victim->GetYSpot());

    Map[Victim.yCoord][Victim.xCoord].PlayerHit(Map[Attacker.yCoord][Attacker.xCoord].PlayerAttacks());
}

void GameMap::AddPlayer(shared_ptr<Player> inPlayer)
{
    players.push_back(inPlayer);
}

shared_ptr<Player> GameMap::GetPlayer(int xPosition, int yPosition)
{
    if (xPosition < 0 || xPosition > (width - 1)) {
        return nullptr;
    }
    else if (yPosition < 0 || yPosition > (height - 1)) {
        return nullptr;
    }
    if (Map[yPosition][xPosition].IsOccupied()) {
        return Map[yPosition][xPosition].GetPlayer();
    }
    return nullptr;
}
