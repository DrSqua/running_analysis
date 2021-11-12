//
// Created by Robbe on 1/11/2021.
//

#ifndef CSV_PARSER_DATA_PROCESSER_H
#define CSV_PARSER_DATA_PROCESSER_H

#include "csv_parser.h"
#include <cmath>

// Structs -------------------------------------------------------------------------------------------------------------
// Statistics struct
struct statistics_struct {
    double max;
    double min;
    double mean;
    double median;
    double variantie;
    double standaardafwijking;
    double scheefheid;

    friend std::ostream& operator<<(std::ostream &stream, statistics_struct &data_instance);
};

// Route statistics struct ( keeps min, max
struct route_statistic_struct {
    // struct of statistics structs
    statistics_struct attempt;
    statistics_struct distance;
    statistics_struct moving_time;
    statistics_struct elapsed_time;
    statistics_struct average_speed;
    statistics_struct max_speed;
    statistics_struct average_tempo;

    friend std::ostream& operator<<(std::ostream &stream, route_statistic_struct &statistics_instance);
};

// Functions ----------------------------------------------------------------------------------------------------------
// Simple Statistics
double mean_of_vector(const std::vector<double>& input_vector);
double median_of_vector(const std::vector<double>& input_vector);
double variantie_of_vector(const std::vector<double>& input_vector, double mean);

//Main statistics
statistics_struct calc_statistics_vector(const std::vector<double>& input_vector);
route_statistic_struct calculate_statistics_data(route_struct& route_instance);


#endif //CSV_PARSER_DATA_PROCESSER_H
