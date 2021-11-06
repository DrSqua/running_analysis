//
// Created by Robbe on 2/11/2021.
//
#include "iostream"
#include "raylib.h"
#include "WindowLoop.h"

// Functions ---------------------------------------------------------------------------------------------------------
// Median of vector
int index_median(const std::vector<int>& input_vector) {
    int n = input_vector.size();
    std::cout << n;
}

double index_median(const std::vector<bool>& input_vector) {

}

// RouteGraph ---------------------------------------------------------------------------------------------------------
// Constructor
RouteGraph::RouteGraph() {

}

// Destructor
RouteGraph::~RouteGraph() = default;

void RouteGraph::set_route(route_struct& route_dataframe) {
    this->calculate_data();
}

void RouteGraph::calculate_data() {
    // Declarations

}


// WINDOWLOOP Class ----------------------------------------------------------------------------------------------------
// Constructor
WindowLoop::WindowLoop(std::map<int, route_struct>& database, int screen_width, int screen_height, int target_fps, int top_space, int side_space)
    {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

    this->database = database;

    this->screen_height = screen_height;
    this->screen_width = screen_width;
    this->top_space = top_space;
    this->side_space = side_space;

    this->route_graph.set_route(database[1]);

    InitWindow(screen_width, screen_height, "Analysis");

    SetTargetFPS(target_fps);
}

// Destructor
WindowLoop::~WindowLoop() {
    CloseWindow();
}

void WindowLoop::handle_event() {
    if (IsKeyPressed(KEY_ESCAPE)||(WindowShouldClose())) {
        running = !running;
    }
}

void WindowLoop::update() {
    if (IsWindowResized()) {
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
    }
}

void WindowLoop::draw() {
    ClearBackground(RAYWHITE);

    std::string s = std::to_string(GetFPS());  // Convert int to string
    char const *fps = s.c_str();  //convert string to char const *

    DrawRectangle(side_space, top_space, screen_width - 2*side_space, screen_height - 2*top_space, LIGHTGRAY);

    DrawText(fps, top_space, side_space, 20, RED);
    EndDrawing();
}