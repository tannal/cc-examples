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

// Custom BeginMode2D function for zooming
void BeginMode2D(Vector2 target, float rotation, float zoom) {
    // No implementation needed for Raylib
}

// Custom Translate function
void Translatef(float x, float y, float z) {
    // No implementation needed for Raylib
}

// Custom Scale function
void Scalef(float x, float y, float z) {
    // No implementation needed for Raylib
}

// Draw the Sierpinski Triangle
void drawSierpinskiTriangle(Rectangle rec, int depth, float windowScale) {
    if (depth == 0) {
        // Draw the triangle
        DrawTriangle(
            {rec.x * windowScale + WIDTH / 2, rec.y * windowScale + HEIGHT / 2},
            {rec.x * windowScale + WIDTH / 2, (rec.y + rec.height) * windowScale + HEIGHT / 2},
            {(rec.x + rec.width) * windowScale + WIDTH / 2, (rec.y + rec.height) * windowScale + HEIGHT / 2},
            BLACK
        );
    } else {
        // Calculate new rectangles
        Rectangle recA = {rec.x + rec.width / 4, rec.y, rec.width / 2, rec.height / 2};
        Rectangle recB = {rec.x, rec.y + rec.height / 2, rec.width / 2, rec.height / 2};
        Rectangle recC = {rec.x + rec.width / 2, rec.y + rec.height / 2, rec.width / 2, rec.height / 2};
        
        // Recursive calls
        drawSierpinskiTriangle(recA, depth - 1, windowScale);
        drawSierpinskiTriangle(recB, depth - 1, windowScale);
        drawSierpinskiTriangle(recC, depth - 1, windowScale);
    }
}

int main() {
    // Set up the window
    InitWindow(WIDTH, HEIGHT, "Sierpinski Triangle Slider");

    // Depth slider and window scale
    int depth = 0;
    float windowScale = 1.0f;

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        int sliderValue = GuiSliderBar((Rectangle){10, 10, 200, 20}, depth, 0, MAX_DEPTH);
        
        // Zoom in when slider moves right, zoom out when slider moves left
        windowScale = 1.0f + (sliderValue - depth) * 0.1f;
        depth = sliderValue;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Define the initial triangle
        Rectangle initialRec = {-200, -200, 400, 400};

        // Draw the Sierpinski Triangle
        drawSierpinskiTriangle(initialRec, depth, windowScale);
        
        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
