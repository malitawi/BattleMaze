#include "Player.h"
#include <iostream>
#include <cassert>

using std::cout; using std::endl;
using std::string;
using std::shared_ptr; using std::weak_ptr;

Player::Player(int XPos_, int YPos_, int HP_, int DMG_, string name_)
    :health(HP_), damage(DMG_), name(name_), position(PlayerCoordinates(XPos_, YPos_)), player_state(ALIVE)
{
    position.xCoord = XPos_;
    position.yCoord = YPos_;
}

void Player::AcquireTarget(shared_ptr<Player> target_ptr)
{
    assert(player_state == ALIVE);
    assert(target_ptr);
    target = weak_ptr<Player>(target_ptr);
    cout << name << " has acquired a target for attack" << endl;
}

void Player::AttackTarget()
{
    assert(player_state == ALIVE);
    shared_ptr<Player> target_ptr = target.lock();
    if (target_ptr) {
        target_ptr->TakeDamage(damage);
        cout << name << " attacks for " << damage << "." << endl;
    }
}

void Player::TakeDamage(int dmg)
{
    assert(player_state == ALIVE);
    health -= dmg;
    cout << name << " hit for " << dmg << ". HP drops from " 
        << health + dmg << " to " << health << endl;
    if (health <= 0) {
        player_state = DEAD;
        cout << name << " dies." << endl;
    }
}

void Player::SetMapSpot(int x, int y)
{
    assert(player_state == ALIVE);
    position.xCoord = x;
    position.yCoord = y;
}

void Player::Move(int horizDist, int vertDist)
{
    assert(player_state == ALIVE);
    position.xCoord += horizDist;
    position.yCoord += vertDist;
}
