#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "array"
#include "map"

#include "csv_parser.h"

using namespace std;

std::ostream& operator<<(std::ostream &stream, route_struct &route_instance) {
    stream  << "      attempt: " << "" << std::endl
            << "     distance: " << "" << std::endl
            << "  moving_time: " << "" << std::endl
            << " elapsed_time: " << "" << std::endl
            << "movement_type: " << "" << std::endl
            << "average_speed: " << "" << std::endl
            << "    max_speed: " << "" << std::endl
            << "average_tempo: " << "" << std::endl
            << "         date: " << "" << std::endl
            << "          map: " << "" << std::endl;
    return stream;
}

route_struct &route_struct::operator+=(const route_struct &rhs) {
    this->attempt.insert(std::end(this->attempt), std::begin(rhs.attempt), std::end(rhs.attempt));
    this->distance.insert(std::end(this->distance), std::begin(rhs.distance), std::end(rhs.distance));
    this->moving_time.insert(std::end(this->moving_time), std::begin(rhs.moving_time), std::end(rhs.moving_time));
    this->elapsed_time.insert(std::end(this->elapsed_time), std::begin(rhs.elapsed_time), std::end(rhs.elapsed_time));
    this->type_movement.insert(std::end(this->type_movement), std::begin(rhs.type_movement), std::end(rhs.type_movement));
    this->average_speed.insert(std::end(this->average_speed), std::begin(rhs.average_speed), std::end(rhs.average_speed));
    this->max_speed.insert(std::end(this->max_speed), std::begin(rhs.max_speed), std::end(rhs.max_speed));
    this->average_tempo.insert(std::end(this->average_tempo), std::begin(rhs.average_tempo), std::end(rhs.average_tempo));
    this->date.insert(std::end(this->date), std::begin(rhs.date), std::end(rhs.date));
    this->map.insert(std::end(this->map), std::begin(rhs.map), std::end(rhs.map));

    return *this;
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
void parse_string_into_map_as_struct(std::map<int, route_struct>& dataframe, const string& raw_string) {
    // Declaration
    std::vector<std::string> line;
    std::string segment; // Elk stukje da wordt gesplitst door de ;
    std::string sub_segment; // Gwn voor de Route # attempt # nog is te splitsen
    route_struct route_object;
    int route;

    line = parse_string_to_vector(raw_string);
    for (int i=0; i<36; i++) {
        segment = line[i];
        segment.erase(std::remove(segment.begin(), segment.end(), '"'), segment.end());
        switch(i) {
            case 1: {
                // Route en attempt parsen
                std::stringstream ss_segment;  // Declaration stringstream_segment (omda da nodig is voor die getline)
                ss_segment << segment;  // string moet terug een stringstream object worden
                for (int j = 0; j < 4; j++) {
                    std::getline(ss_segment, sub_segment, ' ');
                    switch(j) {
                        case 1:
                            route = std::atoi(sub_segment.c_str());
                            break;
                        case 3:
                            route_object.attempt.push_back(std::atoi(sub_segment.c_str()));
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            case 2: { // Distance
                double d;
                istringstream(segment) >> d;
                route_object.distance.push_back(d);
                break;
            }
            case 3: { // Moving time
                double d;
                istringstream(segment) >> d;
                route_object.moving_time.push_back(d);
            }
            case 4: { // Elapsed time
                double d;
                istringstream(segment) >> d;
                route_object.elapsed_time.push_back(d);
            }
            case 6: { // movement type
                route_object.type_movement.push_back(segment);
            }
            case 11: { // Local start date
                route_object.date.push_back(segment);
            }
            case 21: { // Map
                route_object.map.push_back(parse_string_to_polyline(segment));
            }
            case 29: { // Average Speed
                double d;
                istringstream(segment) >> d;
                route_object.average_speed.push_back(d);
            }
            case 30: { // Max speed
                double d;
                istringstream(segment) >> d;
                route_object.max_speed.push_back(d);
            }
            default:
                break;
        }
    }
    route_object.average_tempo.push_back(route_object.moving_time.back() / route_object.distance.back());  // Dees moet nog is gefixt worden

    if (dataframe.find(route) != dataframe.end()) { // If there is a map for route #
        dataframe[route] += route_object;
    }
    else { // If there is no map for route # yet
        dataframe.insert(make_pair(route, route_object));
    }
}

// CSV PARSER
std::map<int, route_struct> parse_csv(const string& filepath) {
    // Variable Declaration
    std::map<int, route_struct> dataframe; // Vector met op elke index een map
    map<int, route_struct> route_map; // Een map per route
    route_struct exercise_instance; // Een struct per attempt
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