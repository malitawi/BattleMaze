#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>

enum TileType {
    GRASS,
    DIRT,
    STONE,
    TREE,
    WATER
};

const std::string TileTypeNames[5] = {"GRASS", "DIRT", "STONE", "TREE", "WATER"};

enum Walkable {
    WALKABLE,
    NOT_WALKABLE
};

const std::string WalkableNames[2] = {"WALKABLE", "NOT_WALKABLE"};

#endif
