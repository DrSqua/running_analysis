#include <iostream>
#include <sstream>

#include "raylib.h"
#include "UI/Routegraph.h"

#include "parsing/csv_parser.h"
#include "data_processing/data_processer.h"

int main() {
    std::string filepath = R"(C:\Users\Robbe\CLionProjects\running_analysis\emUUN_a8.csv)";

    std::map<int, RouteDataframe> route_database = parse_running_csv(filepath);

    auto route = route_database.at(1);
    route.reverse();
    std::cout << route << std::endl;


    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Window Name");
    SetTargetFPS(60);

    Routegraph routegraph;
    std::cout << routegraph.addRoute(route);

    while (!WindowShouldClose()) {
        // Handle Input

        // Update

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        routegraph.drawDynamic();

        DrawFPS(4, 4);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}