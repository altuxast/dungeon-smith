#include "RaylibRenderer.h"
#include "raylib.h"

void RaylibRenderer::render(const Dungeon& dungeon, int tileSize){
    for (int y = 0; y < dungeon.map.size(); y++)
    {
        for (int x = 0; x < dungeon.map[0].size(); x++)
        {
            Color c = dungeon.map[y][x] == Tile::WALL ? DARKGRAY : RAYWHITE;

            DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, c);
        }
        
    }
    
}