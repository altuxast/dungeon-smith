#pragma once
#include "../utils/Types.h"

class RaylibRenderer {
    public:
    void render(const Dungeon& dungeon, int tileSize = 10);
};
