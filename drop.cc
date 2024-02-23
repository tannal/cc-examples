#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class DroppedFiles {
public:
    DroppedFiles() {
        // Initially, no files are dropped, so no need to allocate memory here
    }

    ~DroppedFiles() {
        Clear();
    }

    // Disallow copy and assign to avoid double freeing
    DroppedFiles(const DroppedFiles&) = delete;
    DroppedFiles& operator=(const DroppedFiles&) = delete;

    void Update() {
        // if (IsFileDropped()) {
        //     int count = GetDroppedFilesCount();
        //     char** droppedFilePaths = GetDroppedFiles(&count);
        //     for (int i = 0; i < count; ++i) {
        //         files.emplace_back(droppedFilePaths[i]);
        //     }
        //     ClearDroppedFiles();  // Clear internal buffer of dropped files
        // }
    }

    void Clear() {
        files.clear();
    }

    const std::vector<std::string>& GetFiles() const {
        return files;
    }

private:
    std::vector<std::string> files;
};

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - drop files");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    DroppedFiles droppedFiles;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        droppedFiles.Update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Drop your files to this window!", 100, 40, 20, DARKGRAY);

        const auto& files = droppedFiles.GetFiles();
        for (size_t i = 0; i < files.size(); ++i) {
            DrawText(files[i].c_str(), 100, 80 + 20 * static_cast<int>(i), 10, DARKGRAY);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
