#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 10

// Clamp function to limit a value within a range
int Clamp(int value, int min, int max) {
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

// Simple slider implementation
int GuiSliderBar(Rectangle bounds, int value, int minValue, int maxValue) {
    // Draw slider background
    DrawRectangleRec(bounds, GRAY);
    
    // Check if mouse is hovering over the slider
    bool mouseOverSlider = CheckCollisionPointRec(GetMousePosition(), bounds);
    
    // Check for mouse input
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouseOverSlider) {
        // Calculate new slider value based on mouse position
        value = (GetMouseX() - bounds.x - 15) * (maxValue - minValue) / bounds.width + minValue;
        value = Clamp(value, minValue, maxValue);
    }
    
    // Draw slider
    DrawRectangle(bounds.x + bounds.width * ((float)(value - minValue) / (maxValue - minValue)) - 15, bounds.y, 30, bounds.height, SKYBLUE);
    
    return value; // Return the value
}

// Draw the Sierpinski Triangle
void drawSierpinskiTriangle(Rectangle rec, int depth) {
    if (depth == 0) {
        // Draw the triangle
        DrawTriangle(
            {rec.x + rec.width / 2, rec.y},
            {rec.x, rec.y + rec.height},
            {rec.x + rec.width, rec.y + rec.height},
            BLACK
        );
    } else {
        // Calculate new rectangles
        Rectangle recA = {rec.x + rec.width / 4, rec.y, rec.width / 2, rec.height / 2};
        Rectangle recB = {rec.x, rec.y + rec.height / 2, rec.width / 2, rec.height / 2};
        Rectangle recC = {rec.x + rec.width / 2, rec.y + rec.height / 2, rec.width / 2, rec.height / 2};
        
        // Recursive calls
        drawSierpinskiTriangle(recA, depth - 1);
        drawSierpinskiTriangle(recB, depth - 1);
        drawSierpinskiTriangle(recC, depth - 1);
    }
}

int main() {
    // Set up the window
    InitWindow(WIDTH, HEIGHT, "Sierpinski Triangle Slider");

    // show fps
    SetTargetFPS(60);

    // Depth slider
    int depth = 0;

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        depth = GuiSliderBar((Rectangle){10, 10, 200, 20}, depth, 0, MAX_DEPTH);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Define the initial triangle
        Rectangle initialRec = {200, 100, 400, 400};

        // Draw the Sierpinski Triangle
        drawSierpinskiTriangle(initialRec, depth);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
