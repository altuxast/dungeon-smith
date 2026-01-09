#pragma once
#include "Types.h"

class RaylibRenderer {
    public:
    void render(const Dungeon& dungeon, int tileSize = 10, bool showRooms = false);
};
