//
// Created by Robbe on 2/11/2021.
//
#include "iostream"
#include "WindowLoop.h"

// Functions -------

// RouteGraph ---------------------------------------------------------------------------------------------------------
// Constructors
RouteGraph::RouteGraph() = default;

RouteGraph::RouteGraph(int graph_width, int graph_height, route_struct& route_instance) {
    this->surface_width = graph_width,
    this->surface_height = graph_height;

    this->set_route(route_instance); // Set_Route calculates ook alle data
    this->surface = this->render_surface();
    std::cout << "RouteGraph created";
}
// Destructor
RouteGraph::~RouteGraph() {
    std::cout << "RouteGraph destroyed";
}

void RouteGraph::set_route(const route_struct& route_instance) {
    this->route_instance = route_instance;
    this->calculate_data();
}

void RouteGraph::calculate_data() {
    // Declarations
    this->route_statistics = calculate_statistics_data(this->route_instance);
    this->calculate_graph_sizes();
}

void RouteGraph::calculate_graph_sizes() {
    // x-Axis
    unsigned long long int x_attributes = this->x_axis_labels.size();

    // Max and min
    for (int i = 0; i < x_attributes; i++) {
        switch (this->x_axis_labels[i]) {
            case 1: // Attempt
                // min, max, points
                std::cout << "";
                break;
            default:
                break;
        }
    }

    // Y-axis
    unsigned long long int y_attributes = this->y_axis_labels.size();
    // Max and min
    for (int i = 0; i < y_attributes; i++) {
        switch (this->y_axis_labels[i]) {
            case 1: // Attempt
                // min, max, points
                std::cout << "";
                break;
            default:
                break;
        }
    }
}
// Rendering related
Texture2D RouteGraph::render_surface() {
    Image raw_image = GenImageColor(this->surface_width, this->surface_height, LIGHTGRAY);

    return LoadTextureFromImage(raw_image);
}

void RouteGraph::resize(int new_width, int new_height) {
    this->surface_width = new_width;
    this->surface_height = new_height;
    this->surface = render_surface();
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

    InitWindow(screen_width, screen_height, "Analysis");

    this->route_graph = RouteGraph(screen_width - 2*side_space,
                                   screen_height - 2*top_space,
                                   this->database[this->selected_route]);

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
    if (IsKeyPressed(KEY_B)) {
        if (IsWindowMaximized()) {
            RestoreWindow();
        }
        else {
            MaximizeWindow();
        }
    }
    if (IsWindowResized()) {
        // Adjust stored screen dimensions
        this->screen_width = GetScreenWidth();
        this->screen_height = GetScreenHeight();

        // Rerender the graph's surface
        this->route_graph.resize(screen_width - 2*side_space, screen_height - 2*top_space); // Doet ook automatisch ne re-render
    }
}

void WindowLoop::draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    std::string s = std::to_string(GetFPS());  // Convert int to string
    char const *fps = s.c_str();  //convert string to char const *

    DrawRectangle(side_space, top_space, screen_width - 2*side_space, screen_height - 2*top_space, RED);

    DrawTexture(this->route_graph.get_surface(), side_space, top_space, RAYWHITE);

    DrawText(fps, top_space, side_space, 20, RED);

    EndDrawing();
}