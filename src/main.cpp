#include <iostream>
#include "raylib.h"
#include "generator/BSPGenerator.h"
#include "renderer/RaylibRenderer.h"
#include "JsonIO.h"

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Initialize Raylib window
    InitWindow(WIDTH, HEIGHT, "Dungeon Smith");
    SetTargetFPS(60);

    if (!IsWindowReady())
    {
        std::cerr << "Window failed to initialize!" << std::endl;
        return -1;
    }

    // Temporary delay to verify window opens
    // std::cout << "Window opened, waiting 2 seconds..." << std::endl;
    // WaitTime(2.0f); // or Sleep(2000) on Windows

    BSPGenerator generator;
    RaylibRenderer renderer;

    // Generate initial dungeon
    Dungeon dungeon = generator.generate(80, 60);

    std::cout << "Dungeon dimensions: " << dungeon.map.width << "x" << dungeon.map.height << std::endl;
    // Check dungeon for FLOOR tiles
    for (int y = 0; y < dungeon.map.height; y++)
    {
        for (int x = 0; x < dungeon.map.width; x++)
        {
            if (dungeon.map.get(x, y) == Tile::FLOOR)
            {
                std::cout << "FLOOR found at " << x << "," << y << std::endl;
            }
        }
    }

    std::cout << "Dungeon dimensions: "
              << dungeon.map.width << "x" << dungeon.map.height << std::endl;

    std::cout << "Press CTRL+C to quit..." << std::endl;

    int tileSize = std::min(WIDTH / dungeon.map.width, HEIGHT / dungeon.map.height);

    std::cout << "Dungeon dimensions: "
              << dungeon.map.width << "x" << dungeon.map.height << std::endl;

    std::cout << "Press CTRL+C to quit..." << std::endl;

    int frame = 0;
    while (!WindowShouldClose())
    {
        frame++;
        if (frame % 60 == 0)
            std::cout << "Running frame " << frame << std::endl;

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Handle input
        if (IsKeyPressed(KEY_SPACE))
        {
            dungeon = generator.generate(80, 60);
            std::cout << "Dungeon regenerated!" << std::endl;
            // std::cout.flush();

            // for (int y = 0; y < 10; y++)
            // {
            //     for (int x = 0; x < 10; x++)
            //     {
            //         std::cout << (dungeon.map.get(x, y) == Tile::FLOOR ? "." : "#");
            //     }
            //     std::cout << std::endl;
            // }

            for (int y = 0; y < dungeon.map.height; y++)
            {
                for (int x = 0; x < dungeon.map.width; x++)
                {
                    std::cout << (dungeon.map.get(x, y) == Tile::FLOOR ? "." : "#");
                }
                std::cout << std::endl;
            }
        }

        if (IsKeyPressed(KEY_S))
        {
            JsonIO::save(dungeon, "dungeon.json");
            std::cout << "Dungeon saved to dungeon.json!" << std::endl;
        }

        // Render dungeon tiles
        renderer.render(dungeon, tileSize);
        DrawRectangle(50, 50, 100, 100, RED);

        // Draw instructions on the window
        DrawText("Press SPACE to regenerate dungeon", 10, 10, 20, WHITE);
        DrawText("Press S to save dungeon.json", 10, 40, 20, WHITE);

        EndDrawing();
    }

    // Sanity check
    // InitWindow(800, 600, "Test");
    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //     ClearBackground(BLACK);
    //     DrawText("Hello World", 100, 100, 20, WHITE);
    //     EndDrawing();
    // }

    CloseWindow(); // Properly close the window
    return 0;
}
