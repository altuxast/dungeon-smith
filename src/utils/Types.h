#pragma once

#include <vector>

enum class Tile
{
    WALL,
    FLOOR
};

struct Room {
    int x, y;
    int width, height;
};

struct Dungeon {
    std::vector<std::vector<Tile>> map;
    std::vector<Room> rooms;
};