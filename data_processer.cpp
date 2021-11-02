//
// Created by Robbe on 1/11/2021.
//
#include <iostream>
#include "csv_parser.h"
#include "data_processer.h"

double mean_speed_per_route(std::map<int,std::map<int, exercise_instance>> dataframe, int route) {
    double mean = 0;
    int poging_count = 0;
    std::map<int, exercise_instance> route_dataframe = dataframe[route];

    for (std::pair<int, exercise_instance> kv_pair : route_dataframe)
    {
        exercise_instance& struct_instance = kv_pair.second;
        mean += struct_instance.average_speed;
        poging_count ++;
    }

return mean/poging_count;
}