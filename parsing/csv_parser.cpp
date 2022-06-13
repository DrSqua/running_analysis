#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "array"
#include "map"

#include "csv_parser.h"

// Structs -------------------------------------------------------------------------------------------------------------
// Datum struct
bool start_time::operator==(const start_time &rhs) const {
    if (this->day==rhs.day && this->month==rhs.month && this->year==rhs.year && this->hour==rhs.hour && this->minute==rhs.minute && this->second==rhs.second) {
        return true;
    }
    else {
        return false;
    }
}
std::ostream &operator<<(std::ostream &stream, start_time &time_instance) {
    stream  << time_instance.day << '/' << time_instance.month << '/' << time_instance.year << '-'
            << time_instance.hour << ':' << time_instance.minute << ':' << time_instance.second;
    return stream;
}
bool start_time::operator<(const start_time &rhs) const {
    /* Compares two start_time structs
     *
     */
    if (this->year < rhs.year)
    return true;
    else if (this->year > rhs.year)
        return false;
    else {
        if (this->month < rhs.month)
            return true;
        else if (this->month > rhs.month)
            return false;
        else {
            if (this->day < rhs.day)
                return true;
            else
                return false;
        }
    }
}

std::ostream& operator<<(std::ostream &stream, RouteDataframe &route_instance) {
    stream  << "      attempt: ";
    RouteDataframe::print(route_instance.attempt); stream << std::endl
                                                          << "     distance: ";
    RouteDataframe::print(route_instance.distance); stream << std::endl
                                                           << "  moving_time: ";
    RouteDataframe::print(route_instance.moving_time); stream << std::endl
                                                              << " elapsed_time: ";
    RouteDataframe::print(route_instance.elapsed_time); stream << std::endl
                                                               << "movement_type: " << "" << std::endl
                                                               << "average_speed: ";
    RouteDataframe::print(route_instance.average_speed); stream << std::endl
                                                                << "    max_speed: ";
    RouteDataframe::print(route_instance.max_speed); stream << std::endl
                                                            << "average_tempo: ";
    RouteDataframe::print(route_instance.average_tempo); stream << std::endl
                                                                << "         date: ";
    RouteDataframe::print(route_instance.start_time); stream << std::endl << std::endl
                                                             << "          map: " << "" << std::endl;
    return stream;
}
RouteDataframe &RouteDataframe::operator+=(const RouteDataframe &rhs) {
    this->attempt.insert(std::end(this->attempt), std::begin(rhs.attempt), std::end(rhs.attempt));
    this->distance.insert(std::end(this->distance), std::begin(rhs.distance), std::end(rhs.distance));
    this->moving_time.insert(std::end(this->moving_time), std::begin(rhs.moving_time), std::end(rhs.moving_time));
    this->elapsed_time.insert(std::end(this->elapsed_time), std::begin(rhs.elapsed_time), std::end(rhs.elapsed_time));
    this->type_movement.insert(std::end(this->type_movement), std::begin(rhs.type_movement),
                               std::end(rhs.type_movement));
    this->average_speed.insert(std::end(this->average_speed), std::begin(rhs.average_speed),
                               std::end(rhs.average_speed));
    this->max_speed.insert(std::end(this->max_speed), std::begin(rhs.max_speed), std::end(rhs.max_speed));
    this->average_tempo.insert(std::end(this->average_tempo), std::begin(rhs.average_tempo),
                               std::end(rhs.average_tempo));
    this->start_time.insert(std::end(this->start_time), std::begin(rhs.start_time), std::end(rhs.start_time));
    this->map.insert(std::end(this->map), std::begin(rhs.map), std::end(rhs.map));
    return *this;
}

// Polyline struct
std::ostream& operator<<(std::ostream &stream, polyline &polyline_instance) {
    stream << polyline_instance.id << std::endl
            << polyline_instance.summary_polyline << std::endl
            << polyline_instance.resoure_state << std::endl;
    return stream;
}

// Functions -----------------------------------------------------------------------------------------------------------
start_time parse_string_to_date(std::string& raw_string) { // vb 2021-09-17T17:36:25Z MOET NOG IS OPNIUEW, DE ss_string RESETTEN WERKT NI
    start_time date_instance{};
    std::string subsegment;
    std::stringstream ss_string;
    std::stringstream ss2; // ffs
    std::stringstream ss3; // too tired for this

    std::vector<std::string> stringvector;

    // Split van datum en tijd
    ss_string << raw_string;
    while(std::getline(ss_string, subsegment, 'T'))
    {
        stringvector.push_back(subsegment);
    }

    // Datum
    ss2 << stringvector[0];
    while(std::getline(ss2, subsegment, '-'))
    {
        stringvector.push_back(subsegment);
    }

    // Tijd
    ss3 << stringvector[1];
    while(std::getline(ss3, subsegment, ':'))
    {
        stringvector.push_back(subsegment);
    }

    date_instance.year = std::atoi(stringvector[2].c_str());
    date_instance.month = std::atoi(stringvector[3].c_str());
    date_instance.day = std::atoi(stringvector[4].c_str());
    date_instance.hour = std::atoi(stringvector[5].c_str());
    date_instance.minute = std::atoi(stringvector[6].c_str());
    stringvector[7].pop_back();
    date_instance.second = std::atoi(stringvector[7].c_str());

    // std::cout << date_instance;

    return date_instance;
}

polyline parse_string_to_polyline(std::string& raw_string) {
    polyline polyline_instance;
    return polyline_instance;
}

std::vector<std::string> parse_string_to_vector(const std::string& raw_string) {
    std::vector<std::string> parsed_string;
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
                substring_start = int(i) + 1;
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

void parse_string_into_map_as_struct(std::map<int, RouteDataframe>& dataframe, const std::string& raw_string) {
    // Declaration
    std::vector<std::string> line;
    std::string segment; // Elk stukje da wordt gesplitst door de ;
    std::string sub_segment; // Gwn voor de Route # attempt # nog is te splitsen
    RouteDataframe route_object;
    int route;

    line = parse_string_to_vector(raw_string);
    for (int i=0; i<36; i++) {
        segment = line[i];
        segment.erase(std::remove(segment.begin(), segment.end(), '"'), segment.end());
        switch(i) {
            case 1: {
                // Route en attempt parsen
                std::stringstream ss_segment;  // Declaration std::stringstream_segment (omda da nodig is voor die getline)
                ss_segment << segment;  // std::string moet terug een std::stringstream object worden
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
               std::istringstream(segment) >> d;
                route_object.distance.push_back(d);
                break;
            }
            case 3: { // Moving time
                double d;
               std::istringstream(segment) >> d;
                route_object.moving_time.push_back(d);
                break;
            }
            case 4: { // Elapsed time
                double d;
               std::istringstream(segment) >> d;
                route_object.elapsed_time.push_back(d);
                break;
            }
            case 6: { // movement type
                route_object.type_movement.push_back(segment);
                break;
            }
            case 11: { // Local start date
                route_object.start_time.push_back(parse_string_to_date(segment));
                break;
            }
            case 21: { // Map
                route_object.map.push_back(parse_string_to_polyline(segment));
                break;
            }
            case 29: { // Average Speed
                double d;
               std::istringstream(segment) >> d;
                route_object.average_speed.push_back(d);
                break;
            }
            case 30: { // Max speed
                double d;
               std::istringstream(segment) >> d;
                route_object.max_speed.push_back(d);
                break;
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
        dataframe.insert(std::make_pair(route, route_object));
    }
    // std::cout << dataframe[1] << std::endl;
}

// CSV PARSER
std::map<int, RouteDataframe> parse_running_csv(const std::string& filepath) {
    // Variable Declaration
    std::map<int, RouteDataframe> dataframe; // Vector met op elke index een map
    std::map<int, RouteDataframe> route_map; // Een map per route
    RouteDataframe exercise_instance; // Een struct per attempt
    std::string raw_line; // Lijn die wordt gelezen (dus de rij van een csv)

    // Create connection
    std::ifstream data(filepath);
    if (!data.is_open())
    {
        throw std::invalid_argument("parse_running_csv() can't open file");
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
