#include "TileMap.h"

TileMap::TileMap(int width, int height)
    : width(width), height(height),
      tiles(height, std::vector<Tile>(width, Tile::WALL)) {}

void TileMap::fill(Tile t){
    for(auto& row : tiles){
        std::fill(row.begin(), row.end(), t);
    }
}

Tile TileMap::get(int x, int y) const {
    return tiles[y][x];
}

void TileMap::set(int x, int y, Tile t){
    tiles[y][x] = t;
}
