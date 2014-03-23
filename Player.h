#ifndef PLAYER_H
#define PLAYER_H

#include "DataTypes.h"
#include <memory>

struct Coordinates {
    int xCoord;
    int yCoord;
    Coordinates(int xCoord_, int yCoord_):xCoord(xCoord_), yCoord(yCoord_) {}
};

class Player
{
    private:
        int health;
        int damage;
        std::string name;
        Coordinates position;
        std::weak_ptr<Player> target;
        
        enum Player_State_e { ALIVE, DEAD };
        Player_State_e player_state;

    public:
        Player(int, int, int, int, std::string);

        // disallow copy/move, construction, or assignment
        Player(const Player&) = delete;
        Player(Player&&) = delete;
        Player& operator =(const Player&) = delete;
        Player& operator =(Player&&) = delete;

        void AcquireTarget(std::shared_ptr<Player>);
        void AttackTarget();
        void TakeDamage(int dmg);
        void SetMapSpot(int x, int y);
        void Move(int horrizDist, int vertDist);

        int GetXSpot() { return position.xCoord; }
        int GetYSpot() { return position.yCoord; }
        bool IsAlive() { return player_state == ALIVE; }
        bool HasTarget() { return !target.expired(); }
};
#endif
