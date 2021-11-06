//
// Created by Robbe on 30/10/2021.
//

#ifndef CSV_PARSER_CSV_PARSER_H
#define CSV_PARSER_CSV_PARSER_H

#include "vector"
#include "string"
#include "map"

struct polyline {
    std::string id;
    std::string summary_polyline;
    int resoure_state;

    friend std::ostream& operator<<(std::ostream &stream, polyline &polyline_instance);
};

struct route_struct {
    std::vector<int> attempt;
    std::vector<double> distance;;
    std::vector<double> moving_time{};
    std::vector<double> elapsed_time{};
    std::vector<std::string> type_movement;
    std::vector<polyline> map;
    std::vector<double> average_speed{};
    std::vector<double> max_speed{};
    std::vector<double> average_tempo{};
    std::vector<std::string> date;

    friend std::ostream& operator<<(std::ostream &stream, route_struct &route_instance);

    route_struct& operator+=(const route_struct& rhs);
};

std::map<int, route_struct> parse_csv(const std::string& filepath);

#endif //CSV_PARSER_CSV_PARSER_H