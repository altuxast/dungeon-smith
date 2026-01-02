#pragma once
#include "generator/TileMap.h"
#include "Tile.h"
#include <vector>

struct Room
{
    int x, y;
    int width, height;
};

struct Dungeon
{
    TileMap map;
    // std::vector<std::vector<Tile>> map;
    std::vector<Room> rooms;

    Dungeon(int width, int height) : map(width, height) {}
};