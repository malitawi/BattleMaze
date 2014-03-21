#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "DataTypes.h"
#include <vector>
#include <memory>

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
        void AttackPlayer(std::shared_ptr<Player>, std::shared_ptr<Player>);
        void AddPlayer(std::shared_ptr<Player>);
        std::shared_ptr<Player> GetPlayer(int, int);
};
#endif
