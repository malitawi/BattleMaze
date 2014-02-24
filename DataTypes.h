#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

enum TileType {
    GRASS = 0,
    DIRT,
    STONE,
    TREE,
    WATER
};

const std::string TileTypeNames[5] = {"GRASS", "DIRT", "STONE", "TREE", "WATER"};

enum Walkable {
    WALKABLE = 0,
    NOT_WALKABLE
};

const std::string WalkableNames[2] = {"WALKABLE", "NOT_WALKABLE"};

struct PlayerStats{
    int health;
    int damage;
    std::string name;
};
#endif
