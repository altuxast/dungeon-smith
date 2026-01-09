#include <iostream>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "generator/BSPGenerator.h"
#include "renderer/RaylibRenderer.h"
#include "JsonIO.h"

#undef RAYGUI_IMPLEMENTATION

#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

GuiWindowFileDialogState fileDialog;
bool showLoadDialog = false;

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

    fileDialog = InitGuiWindowFileDialog(NULL);

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
    bool showRooms = false;
    float animSpeed = 0.01f;
    bool animate = true;
    bool skipAnimation = false;

    while (!WindowShouldClose())
    {   
        frame++;
        if (frame % 60 == 0)
            std::cout << "Running frame " << frame << std::endl;

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Toggle rooms overlay
        if (IsKeyPressed(KEY_R))
            showRooms = !showRooms;

        // Animate dungeon generation
        if (IsKeyPressed(KEY_A))
            animate = !animate;

        // Animation speed control
        if (IsKeyPressed(KEY_UP))
            animSpeed = std::max(0.0f, animSpeed - 0.005f);

        if (IsKeyPressed(KEY_DOWN))
            animSpeed = std::min(0.25f, animSpeed + 0.005f);

        // Handle input
        if (IsKeyPressed(KEY_SPACE))
        {
            if (animate)
            {
                // Animation callback
                generator.onStep = [&](const Dungeon &d)
                {
                    // Skip animation
                    if (IsKeyPressed(KEY_K))
                    {
                        skipAnimation = true;
                        generator.onStep = nullptr;
                        return;
                    }

                    dungeon = d;

                    BeginDrawing();
                    ClearBackground(BLACK);
                    renderer.render(dungeon, tileSize, showRooms);
                    EndDrawing();

                    WaitTime(animSpeed);
                };
            }
            else
            {
                generator.onStep = nullptr;
            }

            dungeon = generator.generate(80, 60);

            skipAnimation = false;

            // Disable callback after generation
            generator.onStep = nullptr;

            std::cout << "Dungeon regenerated!" << std::endl;

            for (int y = 0; y < dungeon.map.height; y++)
            {
                for (int x = 0; x < dungeon.map.width; x++)
                {
                    std::cout << (dungeon.map.get(x, y) == Tile::FLOOR ? "." : "#");
                }
                std::cout << std::endl;
            }
        }

        // Save dungeon
        if (IsKeyPressed(KEY_S))
        {
            JsonIO::save(dungeon, "dungeon.json");
            std::cout << "Dungeon saved to dungeon.json!" << std::endl;
        }

        // Load dungeon
        // if (IsKeyPressed(KEY_L))
        // {
        //     const char *filePath = GuiWindowFileDialog("Load Dungeon", "*.json", "Select a JSON dungeon file");

        //     if (filePath != nullptr && filePath[0] != '\0')
        //     {
        //         try
        //         {
        //             dungeon = JsonIO::load(filePath);
        //             tileSize = std::min(WIDTH / dungeon.map.width, HEIGHT / dungeon.map.height);
        //             std::cout << "Dungeon loaded from: " << filePath << std::endl;
        //         }
        //         catch (const std::exception &e)
        //         {
        //             std::cerr << "Load failed: " << e.what() << std::endl;
        //         }
        //     }
        // }

        if (IsKeyPressed(KEY_L))
        {
            fileDialog.windowActive = true;
            showLoadDialog = true;
        }

        // Render dungeon tiles
        renderer.render(dungeon, tileSize, showRooms);

        if (showLoadDialog)
        {
            GuiWindowFileDialog(&fileDialog);

            // When the dialog file closes
            if (!fileDialog.windowActive)
            {
                showLoadDialog = false;

                if(fileDialog.SelectFilePressed){
                    std::string fullPath = std::string(fileDialog.dirPathText) + "/" + std::string(fileDialog.fileNameText);

                    try
                    {
                        dungeon = JsonIO::load(fullPath.c_str());
                        tileSize = std::min(WIDTH / dungeon.map.width, HEIGHT / dungeon.map.height);
                    
                        std::cout << "Dungeon loaded from: " << fullPath << std::endl;
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << "Load failed: " << e.what() << std::endl;
                    }
                    
                }
            }
            
        }

        DrawRectangle(50, 50, 100, 100, RED);

        // Draw instructions on the window
        DrawText("Press SPACE to regenerate dungeon", 10, 10, 20, WHITE);
        DrawText("Press S to save dungeon.json", 10, 40, 20, WHITE);
        DrawText(TextFormat("Speed: %.3f", animSpeed), 10, 130, 20, WHITE);
        DrawText("Press A to animate dungeon generation", 10, 160, 20, WHITE);
        DrawText("Press K to skip animation", 10, 190, 20, WHITE);

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
