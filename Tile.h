#ifndef TILE_H
#define TILE_H

#include "DataTypes.h"
#include <memory>

class Player;

class Tile
{
    private:
        int x, y;
        TileType Terrain;
        Walkable CanWalk;
        std::shared_ptr<Player> currPlayer;
        bool occupied;

    public:
        Tile();
        Tile(int, int, TileType, Walkable);
        ~Tile();
        void SetTileStats(int, int, TileType, Walkable);
        bool IsOccupied();
        void AssignPlayer(std::shared_ptr<Player> inPlayer);
        std::shared_ptr<Player> GetPlayer();
        void PlayerHit(int);
        Walkable IsTileWalkable();
};
#endif
