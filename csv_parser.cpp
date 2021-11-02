#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "array"
#include "map"

#include "csv_parser.h"

using namespace std;

std::ostream& operator<<(std::ostream &stream, exercise_instance &struct_instance) {
    stream  << "    distance: " << struct_instance.distance << std::endl
            << "    moving_time: " << struct_instance.moving_time << std::endl
            << "    elapsed_time: " << struct_instance.elapsed_time << std::endl
            << "    movement_type: " << struct_instance.type_movement << std::endl
            << "    average_speed: " << struct_instance.average_speed << std::endl
            << "    max_speed: " << struct_instance.max_speed << std::endl
            << "    average_tempo: " << struct_instance.average_tempo << std::endl
            << "    date: " << struct_instance.date << std::endl
            << "    map: " << struct_instance.map << std::endl;
    return stream;
}

std::ostream& operator<<(std::ostream &stream, polyline &polyline_instance) {
    stream << polyline_instance.id << std::endl
            << polyline_instance.summary_polyline << std::endl
            << polyline_instance.resoure_state << std::endl;
    return stream;
}

polyline parse_string_to_polyline(std::string& raw_string) {
    polyline polyline_instance;
    return polyline_instance;
}

void add_exercise_instance_to_dataframe(std::map<int,std::map<int, exercise_instance>>& dataframe, exercise_instance& struct_instance, int route, int poging) {
    if (dataframe.find(route) != dataframe.end()) { // If there is a map for route #
        dataframe[route].insert(std::make_pair(poging, struct_instance));
    }
    else { // If there is no map for route # yet
        map<int, exercise_instance> route_map; // Route map is een dict met Pogingen als Keys
        route_map.insert(make_pair(poging, struct_instance));
        dataframe.insert(make_pair(route, route_map));
    }
}

vector<std::string> parse_string_to_vector(const string& raw_string) {
    vector<std::string> parsed_string;
    bool is_valid_to_split = true;
    int substring_start = 0;
    int substring_length = 0;

    for (std::string::size_type i = 0; i < raw_string.size(); ++i) {
        char c = raw_string[i];
        substring_length ++;
        if (c == ',') {  // ER IS EEN ,
            if (is_valid_to_split) {  // Als het ni tussen " staat dan moet ge substring maken en substring_start zetten

                parsed_string.push_back(raw_string.substr(substring_start, substring_length-1)); // -1 omda de length ++ krijgt voorda de split gebeurt

                substring_length = 0;
                substring_start = i + 1;
            } else {  // Als het wel tussen " staat

            }
        } else if (c == '"') { // Als " dan toggle
            is_valid_to_split = !is_valid_to_split;
        }
    }
    parsed_string.emplace_back(""); // Voor na de laatste komma
    return parsed_string;

    // vector<string> namen = {"athlete", "name", "distance", "moving_time", "elapsed_time", "total_elevation_gain", "type", "workout_type", "id", "external_id", "upload_id", "start_date", "start_date_local", "timezone", "start_latlng", "end_latlng", "achievement_count", "kudos_count", "comment_count", "athlete_count", "photo_count", "map", "trainer", "commute", "manual", "private", "flagged", "gear_id", "upload_id_str", "average_speed", "max_speed", "has_heartrate", "elev_high", "elev_low", "total_photo_count", "has_kudoed"};
    // cout << namen.size() << parsed_string.size();
    // for (int i = 0; i<36; i++) {
    //     cout << namen[i] << " |--| " << parsed_string[i] << endl;
    // }
}

// FUNCTION
void parse_string_into_map_as_struct(std::map<int,std::map<int, exercise_instance>>& dataframe, const string& raw_string) {
    // Declaration
    std::vector<std::string> line;
    std::string segment; // Elk stukje da wordt gesplitst door de ;
    std::string sub_segment; // Gwn voor de Route # Poging # nog is te splitsen
    exercise_instance struct_instance;
    int route;
    int poging;

    line = parse_string_to_vector(raw_string);
    for (int i=0; i<36; i++) {
        segment = line[i];
        segment.erase(std::remove(segment.begin(), segment.end(), '"'), segment.end());
        switch(i) {
            case 1: {
                // Route en Poging parsen
                std::stringstream ss_segment;  // Declaration stringstream_segment (omda da nodig is voor die getline)
                ss_segment << segment;  // string moet terug een stringstream object worden
                for (int j = 0; j < 4; j++) {
                    std::getline(ss_segment, sub_segment, ' ');
                    switch(j) {
                        case 1:
                            route = std::atoi(sub_segment.c_str());
                            break;
                        case 3:
                            poging = std::atoi(sub_segment.c_str());
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 2: { // Distance
                istringstream(segment) >> struct_instance.distance;
                break;
            }
            case 3: { // Moving time
                istringstream(segment) >> struct_instance.moving_time;
            }
            case 4: { // Elapsed time
                istringstream(segment) >> struct_instance.elapsed_time;
            }
            case 6: { // movement type
                struct_instance.type_movement = segment;
            }
            case 11: { // Local start date
                struct_instance.date = segment;
            }
            case 21: { // Map
                struct_instance.map = parse_string_to_polyline(segment);
            }
            case 29: { // Average Speed
                istringstream(segment) >> struct_instance.average_speed;
            }
            case 30: { // Max speed
                istringstream(segment) >> struct_instance.max_speed;
            }
            default:
                break;
        }
    }
    struct_instance.average_tempo = struct_instance.moving_time / struct_instance.distance;  // Dees moet nog is gefixt worden
    add_exercise_instance_to_dataframe(dataframe, struct_instance, route, poging);
}

// CSV PARSER
std::map<int,std::map<int, exercise_instance>> parse_csv(const string& filepath) {
    // Variable Declaration
    std::map<int,std::map<int, exercise_instance>> dataframe; // Vector met op elke index een map
    map<int, exercise_instance> route_map; // Een map per route
    exercise_instance exercise_instance; // Een struct per poging
    std::string raw_line; // Lijn die wordt gelezen (dus de rij van een csv)

    // Create connection
    std::ifstream data(filepath);
    if (!data.is_open())
    {
        std::exit(EXIT_FAILURE);  // RAISE IF FILE OPENING DOESN'T WORK
    }

    // Processing
    std::getline(data, raw_line); // skip the first line
    while (std::getline(data, raw_line))  // Loop through next lines
    {
        parse_string_into_map_as_struct(dataframe, raw_line);
    }
    return dataframe;
}