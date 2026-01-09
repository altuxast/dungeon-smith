#include "RaylibRenderer.h"
#include "raylib.h"

void RaylibRenderer::render(const Dungeon &dungeon, int tileSize, bool showRooms)
{
    for (int y = 0; y < dungeon.map.height; y++)
    {
        for (int x = 0; x < dungeon.map.width; x++)
        {
            // Color c = dungeon.map[y][x] == Tile::WALL ? DARKGRAY : RAYWHITE;

            Tile t = dungeon.map.get(x, y);
            Color c = (t == Tile::WALL) ? DARKGRAY : SKYBLUE;

            DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, c);
            DrawRectangleLines(x * tileSize, y * tileSize, tileSize, tileSize, DARKGRAY);
        }
    }

    // Draw room outlines overlay
    if (showRooms)
    {
        for (const auto& r : dungeon.rooms)
        {
            DrawRectangleLines(
                r.x * tileSize,
                r.y * tileSize,
                r.width * tileSize,
                r.height * tileSize,
                RED
            );
        }   
    }
    
}