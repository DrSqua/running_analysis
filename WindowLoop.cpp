//
// Created by Robbe on 2/11/2021.
//
#include "iostream"
#include "WindowLoop.h"

// Functions -------

// RouteGraph ---------------------------------------------------------------------------------------------------------
// Constructors %%%%%%
RouteGraph::RouteGraph() = default;

RouteGraph::RouteGraph(int graph_width, int graph_height, route_struct& route_instance) {
    this->surface_width = graph_width,
    this->surface_height = graph_height;

    this->set_route(route_instance); // Set_Route calculates ook alle data
    this->surface = this->render_surface();
    std::cout << "RouteGraph created";
}
// Destructor%%%%%
RouteGraph::~RouteGraph() {
    std::cout << "RouteGraph destroyed";
}

// Calculations %%%%
void RouteGraph::set_route(const route_struct& new_route_instance) {
    this->route_instance = new_route_instance;  // Nieuwe variabele toewijzen
    this->route_statistics = calculate_statistics_data(this->route_instance);  // Statistics data (max, min, .......
    this->normalise_points();  // Normaliseert naar [0, 10]
    this->align_points(); // Alignt naar de graph map size
}

void RouteGraph::resize(int new_width, int new_height) {  // Wanneer de window wordt veranderd van grootte
    this->surface_width = new_width;
    this->surface_height = new_height;

    this->graph_format = calculate_graph_format_struct();

    alligned_points.clear();
    align_points();
    this->surface = render_surface();
}

graph_format_struct RouteGraph::calculate_graph_format_struct() const {
    float line_thickness = float(surface_height*surface_width) / 45000.0f;
    int map_width = surface_width-int(line_thickness) - 10;
    int map_height = surface_height-int(line_thickness) - 10;
    return (graph_format_struct){line_thickness,
                                 map_width, map_height,
                                 float(map_width)/10.0f, float(map_height)/10};
}

void RouteGraph::normalise_points() {  // Werkt atm alleen nog maar met 1 label op de x as
    this->graph_format = calculate_graph_format_struct();

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
        std::vector<Vector2> normalised_vector;
        normalised_vector.reserve(y_vector.size());
        for (int i = 0; i<y_vector.size(); i++) {
            normalised_vector.push_back((Vector2){x_floats[i], y_vector[i]});
        }
        normalised_points.push_back(normalised_vector);
    }
}
// Rendering related %%%%%%%%%%%%%
void RouteGraph::align_points() {  // Neemt de normalised_point en converteerd ze punten die op de map graph kunnen
    if (!normalised_points.empty()) {
        alligned_points.reserve(normalised_points.size());
        for (const auto &norm_point_vector: this->normalised_points) {

            std::vector<Vector2> align_point_vector;
            align_point_vector.reserve(norm_point_vector.size()); // Dees was een aanwijzing, nog is goe op te zoeken wa dees doet

            for (auto point: norm_point_vector)
                align_point_vector.push_back((Vector2) {point.x * graph_format.align_x, point.y * graph_format.align_y});

            alligned_points.push_back(align_point_vector);
        }
    }
    else
        normalise_points();
}

Texture2D RouteGraph::render_surface() {
    RenderTexture2D canvas = LoadRenderTexture(surface_width, surface_height);
    BeginTextureMode(canvas);
    ClearBackground(LIGHTGRAY);
    std::cout << std::endl << std::endl << surface_width << "   " << surface_height << std::endl;
    // Axis
    float width_offset = graph_format.line_thickness/ 2;
    DrawLineEx((Vector2){0.0f, width_offset}, (Vector2){float(surface_width), width_offset}, graph_format.line_thickness, DARKGRAY);
    DrawLineEx((Vector2){width_offset, 0.0f}, (Vector2){width_offset, float(surface_height)}, graph_format.line_thickness, DARKGRAY);

    // Points
    if (!alligned_points.empty()) {
        for (int i = 0; i < int(alligned_points.size()); i++) {
            std::vector<Vector2> point_vector = alligned_points[i];
            Color color = dark_colors[i];
            for (Vector2 point: point_vector) {
                DrawCircleV(point, graph_format.line_thickness/4, color);
            }
        }
    }

    EndTextureMode();
    return canvas.texture;
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

    DrawText(fps, 0, 0, 20, RED);

    EndDrawing();
}