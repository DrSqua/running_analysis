//
// Created by Robbe on 2/11/2021.
//

#ifndef CSV_PARSER_WINDOWLOOP_H
#define CSV_PARSER_WINDOWLOOP_H
#include "csv_parser.h"
#include "data_processer.h"

// Structs---- ---------------------------------------------------------------------------------------------------------


// Buttons ------------------------------------------------------------------------------------------------------------


// RouteGraph ---------------------------------------------------------------------------------------------------------
class RouteGraph {
public:
    // Constructor
    RouteGraph(int graph_width, int graph_height, route_struct& route_instance);

    // Destructor
    ~RouteGraph();

    //Getters and Setters
    route_struct get_route_struct() { return this->route_instance;} // Get Route
    void set_route(const route_struct& route_instance); // Set route

    route_statistic_struct get_statistics_struct() { return this->route_statistics;} // Get Route statistics


    // Calc functions
    void calculate_data();  // Calc statistics data en graph size

    void calculate_graph_sizes();

    // Render functions
    void render_surface();

    // Drawing
    void draw();

private:
    // Surface
    Image surface{};

    // Structs
    route_struct route_instance; // Raw data
    route_statistic_struct route_statistics{}; // Statistical values struct

    // Graph options
    std::vector<int> x_axis_labels = {1}; // Which data to place on x-axis (standard attempt)
    std::vector<int> y_axis_labels = {7}; // Which data to place on y-axis (standard speed)
};

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

    void handle_event();

    void update();

    void draw();

    //

private:
    std::map<int,std::map<int, route_struct>> dataframe;

    // main screen and loop related
    bool running = true;

    int screen_width;
    int screen_height;

    int top_space;
    int side_space;

    // Graph related
    std::map<int, route_struct> database;

    RouteGraph route_graph;

    int selected_route = 1;
};

#endif //CSV_PARSER_WINDOWLOOP_H
