#include "JsonIO.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void JsonIO::save(const Dungeon &dungeon, const std::string &filename)
{
    json j;

    j["width"] = dungeon.map[0].size();
    j["height"] = dungeon.map.size();

    j["tiles"] = dungeon.map;

    for (const auto &r : dungeon.rooms)
    {
        j["rooms"].push_back({{"x", r.x}, {"y", r.y}, {"width", r.width}, {"height", r.height}});
    }

    std::ofstream file(filename);
    file << j.dump(2);
}