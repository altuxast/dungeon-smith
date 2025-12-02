#pragma once
#include "../utils/Types.h"
#include <string>

class JsonIO {
    public:
    static void save(const Dungeon& dungeon, const std::string& filename);
};