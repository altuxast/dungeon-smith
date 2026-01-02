#pragma once
#include "../../utils/Types.h"  // <- include Dungeon definition
#include "TileMap.h"

class BSPGenerator
{
public:
    Dungeon generate(int width, int height);
};