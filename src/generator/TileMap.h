#pragma once

#include <vector>
#include "../utils/Types.h"

class TileMap
{
public:
    TileMap(int width, int height);

    void fill(Tile t);
    Tile get(int x, int y) const;
    void set(int x, int y, Tile t);

    int width, height;
    std::vector<std::vector<Tile>> tiles;
};