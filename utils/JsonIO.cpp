#include "JsonIO.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void JsonIO::save(const Dungeon &dungeon, const std::string &filename)
{
    json j;

    // j["width"] = dungeon.map[0].size();
    // j["height"] = dungeon.map.size();

    j["width"] = dungeon.map.width;
    j["height"] = dungeon.map.height;

    // j["tiles"] = dungeon.map;

    j["tiles"] = json::array();

    // for (const auto &r : dungeon.rooms)
    // {
    //     j["rooms"].push_back({{"x", r.x}, {"y", r.y}, {"width", r.width}, {"height", r.height}});
    // }

    for (int y = 0; y < dungeon.map.height; y++)
    {
        json row = json::array();
        for (int x = 0; x < dungeon.map.width; x++)
        {
            row.push_back(static_cast<int>(dungeon.map.get(x, y)));
        }
        j["tiles"].push_back(row);
    }

    std::ofstream file(filename);
    file << j.dump(2);
}