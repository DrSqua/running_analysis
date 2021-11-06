//
// Created by Robbe on 2/11/2021.
//

#ifndef CSV_PARSER_WINDOWLOOP_H
#define CSV_PARSER_WINDOWLOOP_H
#include "csv_parser.h"

// Structs---- ---------------------------------------------------------------------------------------------------------

// Route statistics struct ( keeps min, max
struct route_statistic_data {
    // First element is min, second element is average, third is mean, fourth is max
    std::array<double*, 4> distance;
    std::array<int*, 4> moving_time;
    std::array<int*, 4> elapsed_time;
    std::array<double*, 4> average_speed;
    std::array<double*, 4> max_speed;
    std::array<double*, 4> average_tempo;
};

struct route_graph_data {
    // First element is startx, second is furthestx, third is startx, fourth is furthesty
    std::array<double*, 4> distance;
    std::array<int*, 4> moving_time;
    std::array<int*, 4> elapsed_time;
    std::array<double*, 4> average_speed;
    std::array<double*, 4> max_speed;
    std::array<double*, 4> average_tempo;
};

// RouteGraph ---------------------------------------------------------------------------------------------------------
class RouteGraph {
public:
    // Constructor
    RouteGraph();

    // Destructor
    ~RouteGraph();

    //Getters and Setters
    route_struct get_route_struct() { return this->route_instance;} // Get Route
    void set_route(route_struct& route_instance); // Set route


    // Calc functions
    void calculate_data();

    void calculate_graph_sizes();

    // Render functions
    void render_surface();

private:
    route_struct route_instance;

    route_statistic_data route_statistics;
};

// WINDOWLOOP Class ----------------------------------------------------------------------------------------------------
class WindowLoop {
public:
    // Constructor
    WindowLoop(std::map<int, route_struct>& database, int screen_width, int screen_height, int target_fps, int top_space, int side_space);
    // Destructor
    ~WindowLoop();

    // Event loop
    bool is_loop_good() const {
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
    std::vector<int> selected_data;
};

#endif //CSV_PARSER_WINDOWLOOP_H
