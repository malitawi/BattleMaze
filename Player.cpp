#include "Player.h"
#include <iostream>

using std::cout; using std::endl;

Player::Player()
{
}

Player::Player(int inX, int inY): xTile(inX), yTile(inY)
{
}

void Player::SetStats(int inHP, int inDmg, std::string inName)
{
    stats.health = inHP;
    stats.damage = inDmg;
    stats.name = inName;
}

int Player::Attack()
{
    cout << stats.name << " attacks for " << stats.damage << "." << endl;
    return stats.damage;
}

void Player::TakeDamage(int dmg)
{
    stats.health -= dmg;
    cout << stats.name << " hit for " << dmg << ". HP drops from " << stats.health + dmg << " to " << stats.health << endl;
}

void Player::SetMapSpot(int x, int y)
{
    xTile = x;
    yTile = y;
}

void Player::Move(int horrizDist, int vertDist)
{
    xTile += horrizDist;
    yTile += vertDist;
}

int Player::GetXSpot()
{
    return xTile;
}

int Player::GetYSpot()
{
    return yTile;
}
