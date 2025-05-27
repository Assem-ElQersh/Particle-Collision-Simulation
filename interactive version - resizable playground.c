#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1080 / 2
#define SCREEN_HEIGHT 1920 / 2
#define CIRC_RADIUS 8
#define CIRC_NUM 2000
#define SUB_STEPS 30
#define EDGE_THRESHOLD 20  // Distance from edge to detect dragging

typedef struct {
    float left;
    float right;
    float top;
    float bottom;
} Playground;

int draw_limit;
int frames_counter;
Playground playground;
bool isDragging = false;
int dragEdge = 0;  // 0: none, 1: left, 2: right, 3: top, 4: bottom

void UpdatePlayground() {
    // Check if mouse is near edges and handle dragging
    Vector2 mousePos = GetMousePosition();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Check which edge is being dragged
        if (mousePos.x < playground.left + EDGE_THRESHOLD) {
            isDragging = true;
            dragEdge = 1;
        }
        else if (mousePos.x > playground.right - EDGE_THRESHOLD) {
            isDragging = true;
            dragEdge = 2;
        }
        else if (mousePos.y < playground.top + EDGE_THRESHOLD) {
            isDragging = true;
            dragEdge = 3;
        }
        else if (mousePos.y > playground.bottom - EDGE_THRESHOLD) {
            isDragging = true;
            dragEdge = 4;
        }
    }
    
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        isDragging = false;
        dragEdge = 0;
    }
    
    if (isDragging) {
        switch (dragEdge) {
            case 1: // Left edge
                playground.left = Clamp(mousePos.x, 0, playground.right - 100);
                break;
            case 2: // Right edge
                playground.right = Clamp(mousePos.x, playground.left + 100, GetScreenWidth());
                break;
            case 3: // Top edge
                playground.top = Clamp(mousePos.y, 0, playground.bottom - 100);
                break;
            case 4: // Bottom edge
                playground.bottom = Clamp(mousePos.y, playground.top + 100, GetScreenHeight());
                break;
        }
    }
}

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Interactive Collision Sim");
    SetTargetFPS(60);

    // Initialize playground boundaries
    playground.left = 50;
    playground.right = GetScreenWidth() - 50;
    playground.top = 50;
    playground.bottom = GetScreenHeight() - 50;

    Vector2 gravity = {0.f, 1000.f};
    Vector2 circPos[CIRC_NUM];
    Vector2 circVel[CIRC_NUM];
    Vector2 circAcc[CIRC_NUM] = {{gravity.x, gravity.y}};
    Color circColor[CIRC_NUM];

    for (int i = 0; i < CIRC_NUM; i++) {
        circPos[i] = (Vector2){
            GetRandomValue(playground.left + 4 * CIRC_RADIUS, playground.right - 4 * CIRC_RADIUS),
            playground.top + CIRC_RADIUS * 10
        };
        circVel[i] = (Vector2){GetRandomValue(200, 300), GetRandomValue(1, 100)};
        circColor[i] = ColorFromHSV(GetRandomValue(0, 360), 0.5f, 0.7f);
    }

    while (!WindowShouldClose()) {
        if (draw_limit < CIRC_NUM && frames_counter % 4)
            draw_limit++;

        UpdatePlayground();

        float dt = GetFrameTime() / SUB_STEPS;

        for (int step = 0; step < SUB_STEPS; step++) {
            for (int i = 0; i < draw_limit; i++) {
                // Update Positions
                circPos[i].x += circVel[i].x * dt + circAcc[i].x * dt * dt * 0.5f;
                circPos[i].y += circVel[i].y * dt + circAcc[i].y * dt * dt * 0.5f;

                // Update Velocities
                circVel[i].x += gravity.x * dt;
                circVel[i].y += gravity.y * dt;

                // Check playground boundaries for bouncing
                if (circPos[i].x >= playground.right - CIRC_RADIUS) {
                    circPos[i].x = playground.right - CIRC_RADIUS;
                    circVel[i].x = circVel[i].x * 0.6f;
                } else if (circPos[i].x < playground.left + CIRC_RADIUS) {
                    circPos[i].x = playground.left + CIRC_RADIUS;
                    circVel[i].x = 0.f;
                }

                if (circPos[i].y >= playground.bottom - CIRC_RADIUS) {
                    circPos[i].y = playground.bottom - CIRC_RADIUS;
                    circVel[i].y = -0.6f * circVel[i].y;
                } else if (circPos[i].y < playground.top + CIRC_RADIUS) {
                    circPos[i].y = playground.top + CIRC_RADIUS;
                    circVel[i].y = 0.f;
                }

                // Check and solve collision
                for (int j = i; j < draw_limit; j++) {
                    if (i != j && CheckCollisionCircles(circPos[i], CIRC_RADIUS,
                                                      circPos[j], CIRC_RADIUS)) {
                        Vector2 tmp = circVel[i];
                        circVel[i] = circVel[j];
                        circVel[j] = tmp;

                        // Separate the two intersecting circles
                        Vector2 normal =
                            Vector2Normalize(Vector2Subtract(circPos[j], circPos[i]));
                        float overlap =
                            2.f * CIRC_RADIUS - Vector2Distance(circPos[j], circPos[i]);
                        normal = Vector2Scale(normal, overlap / 2.f);

                        circPos[i] = Vector2Subtract(circPos[i], normal);
                        circPos[j] = Vector2Add(circPos[j], normal);
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw playground boundaries
        DrawRectangleLinesEx(
            (Rectangle){playground.left, playground.top, 
                       playground.right - playground.left, 
                       playground.bottom - playground.top},
            2, YELLOW
        );

        // Draw particles
        for (int i = 0; i < draw_limit; i++) {
            DrawCircleV(circPos[i], CIRC_RADIUS, circColor[i]);
        }

        // Draw instructions
        DrawText("Drag edges to resize playground", 10, 10, 20, WHITE);
        DrawFPS(10, 40);
        EndDrawing();
        frames_counter++;
    }

    CloseWindow();
    return EXIT_SUCCESS;
} 