//
// Created by Robbe on 12/12/2021.
//

#include "GUI.h"
GUI::GUI(MousePos* cursor_ptr, std::map<std::string, bool>* booleans) {
    cursor_struct = cursor_ptr;
    boolean_dict = booleans;
}

void GUI::handle_input() {
    // Loop through vector in reverse order (ATM NI)
    for (const auto& layer_vector : GUIsurfacevector) {
        for (const auto& GUIsurface_instance : layer_vector) {
            if (GUIsurface_instance.in_bounds(cursor_struct)) {
                toggle_bool(GUIsurface_instance.key);
                return;
            }
        }
    }
}

void GUI::insert_surface(Surface *surface, std::string key) {
    //! Creates a new layer with the given surface as GUIsurface
    if (GUIsurfacevector.empty()) { // Er bestaat niks
        GUIsurfacevector.push_back({{surface, 0, std::move(key)}});
    } else {
        int layer = (int)GUIsurfacevector.size() - 1;
        GUIsurfacevector.push_back({{surface, layer, std::move(key)}});
    }
}

void GUI::insert_surface_on_layer(Surface *surface, int layer, std::string key) {
    //! Inserts a surface into a given layer, creates a new layer if layer does not exist
    // TODO Nog een check toevoegen die door de gespecifieerde "layer" gaat en ervoor zorgt dat er geen overlappingen zijn

    if (GUIsurfacevector.empty() || GUIsurfacevector.size() <= layer) { // Er bestaat niks
        GUIsurfacevector.push_back({{surface, layer, std::move(key)}}); // Hier kan er eigenlijk nog een foutje gebeuren als de gegeven layer min. 2 lagen hoger is dan de lengte van de vector
    } else {
        GUIsurfacevector[layer].push_back({surface, layer, std::move(key)});
    }
}