//
// Created by Robbe on 1/11/2021.
//
#include <iostream>
#include "csv_parser.h"
#include "data_processer.h"

double mean_speed_per_route(std::map<int, route_struct> dataframe, int route) {
    double mean = 0;

    for (auto object : dataframe[route].average_speed)
        mean += object;

return mean / dataframe[route].average_speed.size();
}
