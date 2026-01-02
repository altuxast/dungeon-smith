#include "TileMap.h"
#include <algorithm>
#include <cassert>

// Constructor
TileMap::TileMap(int width, int height)
    : width(width), height(height),
      tiles(height, std::vector<Tile>(width, Tile::WALL))
{}

// Fill the map with a tile
void TileMap::fill(Tile t) {
    for (auto &row : tiles) {
        std::fill(row.begin(), row.end(), t);
    }
}

// Get tile at position
Tile TileMap::get(int x, int y) const {
    assert(x >= 0 && x < width);
    assert(y >= 0 && y < height);
    return tiles[y][x];
}

// Set tile at position
void TileMap::set(int x, int y, Tile t) {
    assert(x >= 0 && x < width);
    assert(y >= 0 && y < height);
    tiles[y][x] = t;
}