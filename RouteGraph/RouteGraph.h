//
// Created by Robbe on 12/12/2021.
//

#ifndef CSV_PARSER_ROUTEGRAPH_H
#define CSV_PARSER_ROUTEGRAPH_H

#include "raylib.h"
#include "../GUI/GUI.h"
#include "../data_processing/csv_parser.h"
#include "../data_processing/data_processer.h"
#include "vector"

//! Structs---- ---------------------------------------------------------------------------------------------------------
struct GraphFormatStruct {
    float line_thickness;
    int map_width;
    int map_height;
    float align_x;
    float align_y;
};

struct GraphPoint {
    Vector2 pos{};
};

// Buttons ------------------------------------------------------------------------------------------------------------


// RouteGraph ---------------------------------------------------------------------------------------------------------
class RouteGraph {
public:
    // Constructor
    RouteGraph();
    RouteGraph(Surface* route_graph_size, route_struct& route_instance);

    // Destructor
    ~RouteGraph();

    // Looping
    void update(Vector2 Mouse_pos);

    void draw();

    //Getters and Setters
    route_struct get_route_struct() { return this->route_instance;} // Get Route
    void set_route(const route_struct& new_route_instance); // Set route

    route_statistic_struct get_statistics_struct() { return this->route_statistics;} // struct of statistics_struct 's


    // Calc functions
    [[nodiscard]] GraphFormatStruct calculate_graph_format_struct() const;
    void normalise_points();
    void align_points();

    // Render functions
    void render_static_surface();
    [[nodiscard]] RenderTexture2D render_surface();
    void resize(int new_width, int new_height);

private:
    // Pointers

    // Surface
    int surface_width{};
    int surface_height{};
    RenderTexture2D static_surface{};
    RenderTexture2D surface{};

    // Data
    route_struct route_instance; // Raw data
    route_statistic_struct route_statistics{}; // struct of statistics_struct 's (min, max, mean, median all per datatype)

    // Graph options
    GraphFormatStruct graph_format{};

    std::array<Color, 6> dark_colors = {DARKBLUE, DARKGREEN, ORANGE, MAROON, DARKPURPLE, DARKBROWN};
    std::array<Color, 6> medium_colors = {SKYBLUE, GREEN, YELLOW, PINK, PURPLE, BEIGE};
    std::array<Color, 6> light_colors = {BLUE, LIME, GOLD, RED, VIOLET, BROWN};

    std::vector<int> x_axis_labels = {1}; // Which data to place on x-axis (standard attempt)
    std::vector<int> y_axis_labels = {7}; // Which data to place on y-axis (standard speed)

    std::vector<std::vector<GraphPoint>> normalised_points; // Punten op schaal 0.0f tot 10.0f
    std::vector<std::vector<GraphPoint>> alligned_points;  // Calculated point, omgezet naar de breedte van de graph map

    std::vector<int> x_points;
};


#endif //CSV_PARSER_ROUTEGRAPH_H
