//
// Created by Robbe on 12/12/2021.
//

#ifndef CSV_PARSER_GUI_H
#define CSV_PARSER_GUI_H

#include "iostream"
#include "string"
#include "map"
#include "vector"

//! Structs
struct MousePos {
    int x;
    int y;

    void set_pos(int nx, int ny) {x = nx, y = ny;}
};

struct Surface {
    int x_pos{};
    int y_pos{};
    int width{};
    int height{};
    int x_sum = x_pos + width;
    int y_sum = y_pos + height;

    [[nodiscard]] bool check_cursor(int x, int y) const {if (x_pos < x < x_sum && y_pos < y < y_sum) return true; else return false;};
};

struct GUIsurface {
    Surface* SurfaceInfo = nullptr;

    int layer{}; //! Mis is dees hier ni nodig, not sure

    std::string key;

    [[nodiscard]] bool in_bounds(MousePos* cursorpos) const {
        if (SurfaceInfo->x_pos < cursorpos->x && cursorpos->x < (SurfaceInfo->x_pos + SurfaceInfo->width) && SurfaceInfo->y_pos < cursorpos->y && cursorpos->y < (SurfaceInfo->y_pos + SurfaceInfo->height)) {
            // std::cout << SurfaceInfo->x << " < " << cursorpos->x << " < " << (SurfaceInfo->x + SurfaceInfo->width) << " && " << SurfaceInfo->y << " < " << cursorpos->y << " < " << (SurfaceInfo->y + SurfaceInfo->height) << std::endl;
            return true;}
        else
            return false;
    };
};

class GUI {
public:
    GUI() = default;
    explicit GUI(MousePos* cursor_ptr, std::map<std::string, bool>* booleans);

    void insert_surface(Surface* surface, std::string key);
    void insert_surface_on_layer(Surface* surface, int layer, std::string key); //!
    void insert_subsurface();

    void handle_input();

private:
    // Private methods
    void toggle_bool(const std::string& key) {
        if (boolean_dict->find(key) != boolean_dict->end()) {
            boolean_dict->at(key) = true;
        }
        else {
            std::cout << "ERROR: GUI::toggle_bool couldn't find key in the boolean dictionary";
        }
    };

    // Pointers
    MousePos* cursor_struct = nullptr;
    std::map<std::string, bool>* boolean_dict = nullptr;

    // Bounds checking objects
    std::vector<std::vector<GUIsurface>> GUIsurfacevector; // Eerste vector is per "laag", 2de vector is voor de hele laag (NIKS MAG OVERLAPPEN)
};


#endif //CSV_PARSER_GUI_H
