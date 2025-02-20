#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1080 / 2
#define SCREEN_HEIGHT 1920 / 2
#define CIRC_RADIUS_MIN 4  // Minimum circle radius
#define CIRC_RADIUS_MAX 12 // Maximum circle radius
#define CIRC_NUM 2000
#define SUB_STEPS 30

int draw_limit;
int frames_counter;

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My collision sim");
    SetTargetFPS(60);

    Vector2 gravity = {0.f, 1000.f};
    Vector2 circPos[CIRC_NUM];
    Vector2 circVel[CIRC_NUM];
    Vector2 circAcc[CIRC_NUM] = {{gravity.x, gravity.y}};
    Color circColor[CIRC_NUM];
    float circRadius[CIRC_NUM]; // Array for storing variable radii

    for (int i = 0; i < CIRC_NUM; i++) {
        circPos[i] = (Vector2){GetRandomValue(4 * CIRC_RADIUS_MAX, 10 * CIRC_RADIUS_MAX),
                               CIRC_RADIUS_MAX * 10};
        circVel[i] = (Vector2){GetRandomValue(200, 300), GetRandomValue(1, 100)};
        circColor[i] = ColorFromHSV(GetRandomValue(0, 360), 0.5f, 0.7f);
        circRadius[i] = GetRandomValue(CIRC_RADIUS_MIN, CIRC_RADIUS_MAX); // Assign random radius
    }

    while (!WindowShouldClose()) {

        if (draw_limit < CIRC_NUM && frames_counter % 4)
            draw_limit++;

        float dt = GetFrameTime() / SUB_STEPS;

        for (int step = 0; step < SUB_STEPS; step++) {
            for (int i = 0; i < draw_limit; i++) {
                // Update Positions
                circPos[i].x += circVel[i].x * dt + circAcc[i].x * dt * dt * 0.5f;
                circPos[i].y += circVel[i].y * dt + circAcc[i].y * dt * dt * 0.5f;

                // Update Velocities
                circVel[i].x += gravity.x * dt;
                circVel[i].y += gravity.y * dt;

                // Check walls collision for bouncing
                if (circPos[i].x >= GetScreenWidth() - circRadius[i]) {
                    circPos[i].x = GetScreenWidth() - circRadius[i];
                    circVel[i].x *= -0.6f;
                } else if (circPos[i].x < circRadius[i]) {
                    circPos[i].x = circRadius[i];
                    circVel[i].x *= -0.6f;
                }

                if (circPos[i].y >= GetScreenHeight() - circRadius[i]) {
                    circPos[i].y = GetScreenHeight() - circRadius[i];
                    circVel[i].y *= -0.6f;
                } else if (circPos[i].y < circRadius[i]) {
                    circPos[i].y = circRadius[i];
                    circVel[i].y *= -0.6f;
                }

                // Check and solve collision
                for (int j = i + 1; j < draw_limit; j++) {
                    if (i != j && CheckCollisionCircles(circPos[i], circRadius[i],
                                                        circPos[j], circRadius[j])) {
                        Vector2 tmp = circVel[i];
                        circVel[i] = circVel[j];
                        circVel[j] = tmp;

                        // Separate the two intersecting circles
                        Vector2 normal =
                            Vector2Normalize(Vector2Subtract(circPos[j], circPos[i]));
                        float overlap =
                            (circRadius[i] + circRadius[j]) - Vector2Distance(circPos[j], circPos[i]);
                        normal = Vector2Scale(normal, overlap / 2.f);

                        circPos[i] = Vector2Subtract(circPos[i], normal);
                        circPos[j] = Vector2Add(circPos[j], normal);
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < draw_limit; i++) {
            DrawCircleV(circPos[i], circRadius[i], circColor[i]);
        }

        DrawFPS(10, 10);
        EndDrawing();
        frames_counter++;
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
