#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <memory>
#include "DataTypes.h"
class Tile;
class Player;

class GameMap
{
    private:
        int width;
        int height;
        Tile** Map;
        std::vector<std::shared_ptr<Player> > players;

    public:
        GameMap();
        GameMap(int inWidth, int inHeight);
        ~GameMap();
        void SetTile(int, int, TileType, Walkable);
        bool IsTileOccupied(int, int);
        void SetTileOccupant(int, int, std::shared_ptr<Player>);
        bool IsValidSpot(int, int);
        void AttackPlayer(int, int, int, int);
        void AddPlayer(std::shared_ptr<Player> inPlayer);
};
#endif
