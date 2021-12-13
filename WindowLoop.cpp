//
// Created by Robbe on 2/11/2021.
//
#include "iostream"
#include "WindowLoop.h"

// Functions -------

// WINDOWLOOP Class ----------------------------------------------------------------------------------------------------
// Constructor
WindowLoop::WindowLoop(std::map<int, route_struct>& ndatabase, int nscreen_width, int nscreen_height, int target_fps, int ntop_space, int nside_space)
    {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

    database = ndatabase;

    screen_height = nscreen_height;
    screen_width = nscreen_width;
    top_space = ntop_space;
    side_space = nside_space;

    GUIinstance = GUI(&mousePos, &boolean_dict);

    InitWindow(screen_width, screen_height, "Analysis");
    SetTargetFPS(target_fps);

    route_graph_dimensions = (Surface) {side_space, top_space, screen_width - 2 * side_space, screen_height - 2 * top_space};

    selected_route_id = 1;
    route_struct selected_route = database.at(selected_route_id);
    route_graph = RouteGraph(&route_graph_dimensions, database.at(selected_route_id), &GUIinstance);
    GUIinstance.insert_surface(&route_graph_dimensions, 0, "cursor_in_graph");
}

// Destructor
WindowLoop::~WindowLoop() {
    CloseWindow();
}

void WindowLoop::handle_events() {
    boolean_dict["cursor_in_graph"] = false;

    mousePos.set_pos(GetMouseX(), GetMouseY());

    GUIinstance.handle_input();

    if (IsKeyPressed(KEY_ESCAPE)||(WindowShouldClose())) {
        running = !running;
    }

}

void WindowLoop::update() {
    if (IsKeyPressed(KEY_F)) {
        if (IsWindowMaximized()) {
            RestoreWindow();
        }
        else {
            MaximizeWindow();
        }
    }
    if (IsWindowResized()) {
        // Adjust stored screen dimensions
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();

        route_graph_dimensions = (Surface) {side_space, top_space, screen_width - 2 * side_space, screen_height - 2 * top_space};

        // Rerender the graph's surface
        route_graph.resize(route_graph_dimensions.width, route_graph_dimensions.height); // Doet ook automatisch ne re-render
    }
}

void WindowLoop::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Routegraph
    DrawRectangle(side_space, top_space, screen_width - 2*side_space, screen_height - 2*top_space, RED);

    // if (route_graph_dimensions.check_cursor())
    DrawTexture(route_graph.render_surface().texture, route_graph_dimensions.x_pos, route_graph_dimensions.y_pos, RAYWHITE);

    // FPS
    std::string s = std::to_string(GetFPS());  // Convert int to string
    char const *fps = s.c_str();  //convert string to char const *
    DrawText(fps, 0, 0, 20, RED);

    EndDrawing();
}