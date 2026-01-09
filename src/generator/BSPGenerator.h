#pragma once
#include "../../utils/Types.h" // <- include Dungeon definition
#include "TileMap.h"
#include <functional>

class BSPGenerator
{
public:
    std::function<void(const Dungeon &)> onStep;
    Dungeon generate(int width, int height);
};