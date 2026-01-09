#pragma once

#include "../utils/Types.h"
#include <string>

// Add this:
#include "json.hpp"
using json = nlohmann::json;

class JsonIO {
public:
    static void save(const Dungeon& dungeon, const std::string& filename);
    static Dungeon load(const std::string& filename);

private:
    static Dungeon loadVersion0(const json& j);
    static Dungeon loadVersion1(const json& j);
};