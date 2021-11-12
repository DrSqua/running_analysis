//
// Created by Robbe on 2/11/2021.
//

#ifndef CSV_PARSER_WINDOWLOOP_H
#define CSV_PARSER_WINDOWLOOP_H

#include "raylib.h"
#include "csv_parser.h"
#include "data_processer.h"

// Structs---- ---------------------------------------------------------------------------------------------------------
struct graph_format_struct {
    float line_thickness;
    int map_width;
    int map_height;
    float align_x;
    float align_y;
};

// Buttons ------------------------------------------------------------------------------------------------------------


// RouteGraph ---------------------------------------------------------------------------------------------------------
class RouteGraph {
public:
    // Constructor
    RouteGraph();
    RouteGraph(int graph_width, int graph_height, route_struct& route_instance);

    // Destructor
    ~RouteGraph();

    //Getters and Setters
    Texture2D get_surface() {return this->surface;}
    route_struct get_route_struct() { return this->route_instance;} // Get Route
    void set_route(const route_struct& new_route_instance); // Set route

    route_statistic_struct get_statistics_struct() { return this->route_statistics;} // struct of statistics_struct 's


    // Calc functions
    [[nodiscard]] graph_format_struct calculate_graph_format_struct() const;
    void normalise_points();
    void align_points();

    // Render functions
    [[nodiscard]] Texture2D render_surface();
    void resize(int new_width, int new_height);

private:
    // Surface
    int surface_width;
    int surface_height;
    Texture2D surface;

    // Data
    route_struct route_instance; // Raw data
    route_statistic_struct route_statistics; // struct of statistics_struct 's (min, max, mean, median all per datatype)

    // Graph options
    graph_format_struct graph_format;

    std::array<Color, 6> dark_colors = {DARKBLUE, DARKGREEN, ORANGE, MAROON, DARKPURPLE, DARKBROWN};
    std::array<Color, 6> medium_colors = {SKYBLUE, GREEN, YELLOW, PINK, PURPLE, BEIGE};
    std::array<Color, 6> light_colors = {BLUE, LIME, GOLD, RED, VIOLET, BROWN};

    std::vector<int> x_axis_labels = {1}; // Which data to place on x-axis (standard attempt)
    std::vector<int> y_axis_labels = {7}; // Which data to place on y-axis (standard speed)

    std::vector<std::vector<Vector2>> normalised_points; // Punten op schaal 0.0f tot 10.0f
    std::vector<std::vector<Vector2>> alligned_points;  // Calculated point, omgezet naar de breedte van de graph map

    std::vector<int> x_points;
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
    [[nodiscard]] bool ismaxwindow() const {
        return max_window;
    }

    void handle_event();

    void update();

    void draw();

    //

private:
    std::map<int,std::map<int, route_struct>> dataframe;

    // main screen and loop related
    bool running = true;
    bool max_window = false;

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
