//
// Created by Robbe on 2/11/2021.
//
#include "iostream"
#include "WindowLoop.h"

// Functions -------

// RouteGraph ---------------------------------------------------------------------------------------------------------
// Constructors %%%%%%
RouteGraph::RouteGraph() = default;

RouteGraph::RouteGraph(Surface* route_graph_size, route_struct& route_instance) {
    surface_width = route_graph_size->width,
    surface_height = route_graph_size->height;

    if (!route_instance.empty()) {
        set_route(route_instance); // Set_Route calculates ook alle data
    } else {
        throw std::invalid_argument("RouteGraph::set_route krijgt een lege route_struct&");
        }
    render_static_surface();
    std::cout << "RouteGraph created" << std::endl;
}
// Destructor%%%%%
RouteGraph::~RouteGraph() {
    std::cout << "" << std::endl;
}

// WindowLoop Functions
void update(Vector2 Mouse_pos) {

}

void RouteGraph::draw() {
    // surface = render_surface();
}

// Calculations %%%%
void RouteGraph::set_route(const route_struct& new_route_instance) {
    if (!new_route_instance.empty()) {
        route_instance = new_route_instance;  // Nieuwe variabele toewijzen
        route_statistics = calculate_statistics_data(this->route_instance);  // Statistics data (max, min, .......
        normalise_points();  // Normaliseert naar [0, 10]
        align_points(); // Alignt naar de graph map size
    } else {
        throw std::invalid_argument("RouteGraph::set_route krijgt een lege route_struct&");
    }
}

void RouteGraph::resize(int new_width, int new_height) {  // Wanneer de window wordt veranderd van grootte
    surface_width = new_width;
    surface_height = new_height;

    graph_format = calculate_graph_format_struct();

    alligned_points.clear();
    align_points();

    render_static_surface();
    surface = LoadRenderTexture(surface_width, surface_height);
}

GraphFormatStruct RouteGraph::calculate_graph_format_struct() const {
    float line_thickness = float(surface_height*surface_width) / 45000.0f;
    int map_width = surface_width-int(line_thickness) - 10;
    int map_height = surface_height-int(line_thickness) - 10;
    return (GraphFormatStruct){line_thickness,
                               map_width, map_height,
                                 float(map_width)/10.0f, float(map_height)/10};
}

void RouteGraph::normalise_points() {  // Werkt atm alleen nog maar met 1 label op de x as
    graph_format = calculate_graph_format_struct();

    std::vector<float> x_floats;
    std::vector<std::vector<float>> y_floats;

    // x-Axis --
    unsigned long long int x_attributes = this->x_axis_labels.size();
    // Max and min
    for (int i = 0; i < x_attributes; i++) { // Loopt door elk ding da op de x-as moet staan
        switch (this->x_axis_labels[i]) {  // Switch voor welke soort data het is
            case 1: { // Attemps (int)
                // min, max, points
                float normalisation_multiplier = 10.0f / float(route_statistics.attempt.max);
                for (auto x_raw : route_instance.attempt)
                x_floats.push_back(float(x_raw) * normalisation_multiplier);
                break;
            }
            default:
                break;
        }
    }

    // Y-axis
    unsigned long long int y_attributes = this->y_axis_labels.size();
    // Max and min
    for (int i = 0; i < y_attributes; i++) {
        switch (this->y_axis_labels[i]) {
            case 7: { // Speed
                // min, max, points
                std::vector<float> y_vector;
                float normalisation_multiplier = 10.0f / float(route_statistics.average_speed.max);
                for (auto y_raw : route_instance.average_speed)
                    y_vector.push_back(float(y_raw) * normalisation_multiplier);
                y_floats.push_back(y_vector);
                break;
            }
            default:
                break;
        }
    }

    // Combining into point
    for (auto y_vector : y_floats) {
        std::vector<GraphPoint> normalised_vector;
        normalised_vector.reserve(y_vector.size());
        for (int i = 0; i<y_vector.size(); i++) {
            Vector2 pos = (Vector2){x_floats[i], y_vector[i]};
            normalised_vector.push_back((GraphPoint) {pos});
        }
        normalised_points.push_back(normalised_vector);
    }
}
// Rendering related %%%%%%%%%%%%%
void RouteGraph::align_points() {  // Neemt de normalised_point en converteerd ze punten die op de map graph kunnen
    if (!normalised_points.empty()) {
        alligned_points.reserve(normalised_points.size());
        for (const auto &norm_point_vector: this->normalised_points) {

            std::vector<GraphPoint> align_point_vector;
            align_point_vector.reserve(norm_point_vector.size()); // Dees was een aanwijzing, nog is goe op te zoeken wa dees doet

            for (auto point: norm_point_vector)
                Vector2 pos = (Vector2) {point.pos.x * graph_format.align_x, point.pos.y * graph_format.align_y};
                align_point_vector.push_back((GraphPoint) {});

            alligned_points.push_back(align_point_vector);
        }
    }
    else
        normalise_points();
}

void RouteGraph::render_static_surface() {
    surface = LoadRenderTexture(surface_width, surface_height); // Als de static_surface opnieuw gerendered moet worden wss de surface ook
    static_surface = LoadRenderTexture(surface_width, surface_height);
    BeginTextureMode(static_surface);
    ClearBackground(LIGHTGRAY);

    std::cout << std::endl << std::endl << surface_width << "   " << surface_height << std::endl;
    // Axis
    float width_offset = graph_format.line_thickness/ 2;
    DrawLineEx((Vector2){0.0f, width_offset}, (Vector2){float(surface_width), width_offset}, graph_format.line_thickness, DARKGRAY); // x-as
    DrawLineEx((Vector2){width_offset, 0.0f}, (Vector2){width_offset, float(surface_height)}, graph_format.line_thickness, DARKGRAY); // y-as

    // Points
    if (!alligned_points.empty()) {
        for (int i = 0; i < int(alligned_points.size()); i++) {
            std::vector<GraphPoint> point_vector = alligned_points[i];
            Color dark_color = dark_colors[i];
            Color med_color = medium_colors[i];

            for (GraphPoint point: point_vector) {
                DrawCircleV(point.pos, graph_format.line_thickness/4, dark_color);
                DrawRectangleV((Vector2) {point.pos.x, graph_format.line_thickness}, (Vector2) {graph_format.line_thickness/2, graph_format.line_thickness}, med_color);
                DrawRectangleV((Vector2) {graph_format.line_thickness, point.pos.y}, (Vector2) {graph_format.line_thickness, graph_format.line_thickness/2}, med_color);
            }
        }
    }
    EndTextureMode();
}

RenderTexture2D RouteGraph::render_surface() {
    BeginTextureMode(surface);
    ClearBackground(LIGHTGRAY);

    DrawTexture(static_surface.texture, 0, 0, RAYWHITE);

    EndTextureMode();
    return surface;
}

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

    InitWindow(screen_width, screen_height, "Analysis");
    SetTargetFPS(target_fps);

    route_graph_dimensions = (Surface) {side_space, top_space, screen_width - 2 * side_space, screen_height - 2 * top_space};

    selected_route_id = 1;
    route_struct selected_route = database.at(selected_route_id);
    route_graph = RouteGraph(&route_graph_dimensions, database.at(selected_route_id));
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