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
    j["rooms"] = json::array();

    for (const auto &r : dungeon.rooms)
    {
        j["rooms"].push_back({{"x", r.x},
                              {"y", r.y},
                              {"width", r.width},
                              {"height", r.height}});
    }

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

Dungeon JsonIO::load(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open dungeon file: " + filename);
    }

    json j;
    file >> j;

    int width = j.at("width").get<int>();
    int height = j.at("height").get<int>();

    Dungeon dungeon(width, height);

    const auto &tiles = j.at("tiles");
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int v = tiles[y][x].get<int>();
            dungeon.map.set(x, y, static_cast<Tile>(v));
        }
    }

    if (j.contains("rooms"))
    {
        for (const auto& r : j["rooms"])
        {
            Room room;
            room.x = r.at("x").get<int>();
            room.y = r.at("y").get<int>();
            room.width = r.at("height").get<int>();
            room.height = r.at("height").get<int>();
            dungeon.rooms.push_back(room);
        }
    }
    

    return dungeon;
}