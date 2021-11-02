//
// Created by Robbe on 2/11/2021.
//
#include "raylib.h"
#include "WindowLoop.h"

WindowLoop::WindowLoop(int screen_width, int screen_height, int target_fps) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

    InitWindow(screen_width, screen_height, "raylib [core] example - basic window");

    SetTargetFPS(target_fps);

}

void WindowLoop::handle_event() {

}

void WindowLoop::update() {
    if (!WindowShouldClose()) {
        // running = !running;
    }
}

void WindowLoop::draw() {
    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}