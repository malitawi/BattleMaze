#ifndef PLAYER_H
#define PLAYER_H

#include "DataTypes.h"

class Player
{
    private:
        PlayerStats stats;
        int xTile;
        int yTile;

    public:
        Player();
        Player(int, int);
        void SetStats(int inHP, int inDMG, std::string inName);
        int Attack();
        void TakeDamage(int dmg);
        void SetMapSpot(int x, int y);
        void Move(int horrizDist, int vertDist);
        int GetXSpot();
        int GetYSpot();
};
#endif
