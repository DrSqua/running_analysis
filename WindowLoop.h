//
// Created by Robbe on 2/11/2021.
//

#ifndef CSV_PARSER_WINDOWLOOP_H
#define CSV_PARSER_WINDOWLOOP_H

#include "raylib.h"
#include "data_processing/csv_parser.h"
#include "data_processing/data_processer.h"
#include "GUI/GUI.h"
#include "RouteGraph/RouteGraph.h"

// WINDOWLOOP Class ----------------------------------------------------------------------------------------------------
class WindowLoop {
public:
    // Constructor
    WindowLoop(std::map<int, route_struct>& database, int screen_width, int screen_height, int target_fps, int top_space, int side_space);
    // Destructor
    ~WindowLoop();

    // Event loop
    [[nodiscard]] bool is_loop_good() const {
        return running;
    }

    void handle_events();
    void update();
    void draw();

private:
    // main screen
    bool running = true;
    bool max_window = false;

    int screen_width{};
    int screen_height{};

    int top_space{};
    int side_space{};

    // Loop
    std::map<std::string, bool> boolean_dict;

    // GUI
    MousePos mousePos{};
    GUI GUIinstance;

    // Graph related
    std::map<int, route_struct> database;

    Surface route_graph_dimensions;
    RouteGraph route_graph;

    int selected_route_id{};
};

#endif //CSV_PARSER_WINDOWLOOP_H
