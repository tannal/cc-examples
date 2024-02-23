#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define MAX_DEPTH 5

// Clamp function to limit a value within a range
int Clamp(int value, int min, int max) {
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

// Function to draw Sierpinski's Carpet
void drawCarpet(int x, int y, int size, int depth) {
    if (depth == 0) return;

    // Calculate width and height of each smaller square
    int newSize = size / 3;

    // Draw 8 smaller squares (except the center one)
    for (int i = 0; i < 9; i++) {
        if (i == 4) continue; // Skip the center square

        // Calculate coordinates for each smaller square
        int newX = x + (i % 3) * newSize;
        int newY = y + (i / 3) * newSize;

        // Draw the smaller square
        DrawRectangle(newX, newY, newSize, newSize, BLACK);

        // Recursive call for each smaller square
        drawCarpet(newX, newY, newSize, depth - 1);
    }
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

int main() {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sierpinski's Carpet");

    // Depth slider
    int depth = MAX_DEPTH;

    // Main loop
    while (!WindowShouldClose()) {
        // Update
        depth = GuiSliderBar((Rectangle){10, 10, 200, 20}, depth, 0, MAX_DEPTH);

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // Start drawing the carpet at the center of the screen
        drawCarpet(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 3, depth);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
