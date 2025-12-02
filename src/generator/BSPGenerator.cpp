#include "BSPGenerator.h"
#include <random>

Dungeon BSPGenerator::generate(int width, int height)
{
    Dungeon dungeon;
    dungeon.map = std::vector(height, std::vector<Tile>(width, Tile::WALL));

    Room room = {width / 4, height / 4, width / 2, height / 2};
    dungeon.rooms.push_back(room);

    for (int y = room.y; y < room.y + room.height; y++)
    {
        for (int x = room.x; x < room.x + room.width; x++)
        {
            dungeon.map[y][x] = Tile::FLOOR;       
        }
        
    }
    
    return dungeon;
}