//
// Created by Robbe on 1/11/2021.
//

#ifndef CSV_PARSER_DATA_PROCESSER_H
#define CSV_PARSER_DATA_PROCESSER_H

#include "map"
#include "csv_parser.h"

double mean_speed_per_route(std::map<int, route_struct> dataframe, int route);

#endif //CSV_PARSER_DATA_PROCESSER_H
