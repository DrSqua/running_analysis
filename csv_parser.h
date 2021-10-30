//
// Created by Robbe on 30/10/2021.
//

#ifndef CSV_PARSER_CSV_PARSER_H
#define CSV_PARSER_CSV_PARSER_H

#include "vector"
#include "string"
#include "map"

struct exercise_instance {
    double distance{};
    int moving_time{};
    int elapsed_time{};
    std::string type_movement;
    std::string map;
    double average_speed{};
    double max_speed{};
    std::string date;

    friend std::ostream& operator<<(std::ostream &stream, exercise_instance &struct_instance);
};

std::map<int,std::map<int, exercise_instance>> parse_csv(const std::string& filepath);

#endif //CSV_PARSER_CSV_PARSER_H