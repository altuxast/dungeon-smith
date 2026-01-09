#include "BSPGenerator.h"
#include <random>
#include <vector>
#include <algorithm>

struct Node
{
    int x, y, width, height;
    Node *left = nullptr;
    Node *right = nullptr;
    Room room;

    Node(int x_, int y_, int w_, int h_) : x(x_), y(y_), width(w_), height(h_) {}
};

class BSP
{
public:
    BSP(int minSize = 6, int maxSize = 20) : minRoomSize(minSize), maxRoomSize(maxSize)
    {
        rng.seed(std::random_device{}());
    }

    std::function<void(const Dungeon &)> onStep;

    Dungeon generate(int width, int height)
    {
        Dungeon dungeon(width, height);
        dungeon.map.fill(Tile::WALL);

        Node root(0, 0, width, height);
        splitNode(&root, dungeon);

        return dungeon;
    }

private:
    int maxRoomSize;
    int minRoomSize;
    std::mt19937 rng;

    void splitNode(Node *node, Dungeon &dungeon)
    {
        bool splitH = (node->width < node->height) ? true : false;
        if (node->width > 2 * minRoomSize && node->height > 2 * minRoomSize)
            splitH = std::uniform_int_distribution<>(0, 1)(rng) == 0;

        int maxSplit = (splitH ? node->height : node->width) - minRoomSize;
        if (maxSplit <= minRoomSize)
        {
            createRoom(node, dungeon);
            return;
        }

        std::uniform_int_distribution<> dist(minRoomSize, maxSplit);
        int split = dist(rng);

        if (splitH)
        {
            node->left = new Node(node->x, node->y, node->width, split);
            node->right = new Node(node->x, node->y + split, node->width, node->height - split);
        }
        else
        {
            node->left = new Node(node->x, node->y, split, node->height);
            node->right = new Node(node->x + split, node->y, node->width - split, node->height);
        }

        splitNode(node->left, dungeon);
        splitNode(node->right, dungeon);

        connectNodes(node->left, node->right, dungeon);
    }

    void createRoom(Node *node, Dungeon &dungeon)
    {
        std::uniform_int_distribution<> rw(minRoomSize, std::min(node->width, maxRoomSize));
        std::uniform_int_distribution<> rh(minRoomSize, std::min(node->height, maxRoomSize));

        int roomW = rw(rng);
        int roomH = rh(rng);

        std::uniform_int_distribution<> rx(0, node->width - roomW);
        std::uniform_int_distribution<> ry(0, node->height - roomH);

        int roomX = node->x + rx(rng);
        int roomY = node->y + ry(rng);

        roomX = std::max(0, std::min(roomX, dungeon.map.width - roomW));
        roomY = std::max(0, std::min(roomY, dungeon.map.height - roomH));

        for (int y = roomY; y < roomY + roomH; y++)
        {
            for (int x = roomX; x < roomX + roomW; x++)
            {
                dungeon.map.set(x, y, Tile::FLOOR);
            }
        }
        
        node->room = {roomX, roomY, roomW, roomH};
        dungeon.rooms.push_back(node->room);

        if (onStep)
            onStep(dungeon);
    }

    void connectNodes(Node *a, Node *b, Dungeon &dungeon)
    {
        if (!a || !b)
            return;

        int ax = a->room.x + a->room.width / 2;
        int ay = a->room.y + a->room.height / 2;
        int bx = b->room.x + b->room.width / 2;
        int by = b->room.y + b->room.height / 2;

        if (std::uniform_int_distribution<>(0, 1)(rng) == 0)
        {
            carveHorizontal(ax, bx, ay, dungeon);
            carveVertical(ay, by, bx, dungeon);
        }
        else
        {
            carveHorizontal(ay, by, ax, dungeon);
            carveVertical(ax, bx, by, dungeon);
        }

        if (onStep)
            onStep(dungeon);
    }

    void carveHorizontal(int x1, int x2, int y, Dungeon &dungeon)
    {
        y = std::clamp(y, 0, dungeon.map.height - 1);
        int start = std::clamp(std::min(x1, x2), 0, dungeon.map.width - 1);
        int end = std::clamp(std::max(x1, x2), 0, dungeon.map.width - 1);
        for (int x = start; x <= end; x++)
        {
            dungeon.map.set(x, y, Tile::FLOOR);
            if (onStep)
                onStep(dungeon);
        }
    }

    void carveVertical(int y1, int y2, int x, Dungeon &dungeon)
    {
        x = std::clamp(x, 0, dungeon.map.width - 1);
        int start = std::clamp(std::min(y1, y2), 0, dungeon.map.height - 1);
        int end = std::clamp(std::max(y1, y2), 0, dungeon.map.height - 1);
        for (int y = start; y <= end; y++)
        {
            dungeon.map.set(x, y, Tile::FLOOR);
            if (onStep)
                onStep(dungeon);
        }
    }
};

Dungeon BSPGenerator::generate(int width, int height)
{
    BSP bsp;
    bsp.onStep = onStep;
    return bsp.generate(width, height);
}

// Temporary safe generator for testing
// Dungeon BSPGenerator::generate(int width, int height)
// {
//     Dungeon dungeon(width, height);

//     // Fill all tiles with WALL initially
//     dungeon.map.fill(Tile::WALL);

//     // Example: carve a simple FLOOR rectangle in the middle
//     int startX = width / 4;
//     int startY = height / 4;
//     int endX   = 3 * width / 4;
//     int endY   = 3 * height / 4;

//     for (int y = startY; y < endY; y++)
//         for (int x = startX; x < endX; x++)
//             dungeon.map.set(x, y, Tile::FLOOR);

//     return dungeon;
// }
