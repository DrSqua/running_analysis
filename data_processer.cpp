//
// Created by Robbe on 1/11/2021.
//
#include <iostream>
#include "algorithm"
#include "csv_parser.h"
#include "data_processer.h"

// Simpel Statistics
// Mean
double mean_of_vector(const std::vector<double>& input_vector) {
    double mean = 0;
    for (auto object: input_vector)
        mean += object;
    return mean / double(input_vector.size());
}

double median_of_vector(const std::vector<double>& input_vector) {
    return input_vector[0];
}

// Statistical Main ------------------------------------------------------------------------------------------
// Zet een vector van de waardes per attempt om naar de statistische vector
statistics_struct calc_statistics_vector(const std::vector<double>& input_vector) {
    statistics_struct statistics_instance;

    const auto [min, max] = std::minmax_element(begin(input_vector), end(input_vector));
    statistics_instance.min = *min;
    statistics_instance.max = *max;
    statistics_instance.mean = mean_of_vector(input_vector);
    statistics_instance.median = median_of_vector(input_vector); // Still to do

    return statistics_instance;
}

// Maakt een route_statistics_struct uit een route_struct
route_statistic_struct calculate_statistics_data(route_struct& route_instance) {
route_statistic_struct statistics_instance{};

statistics_instance.distance = calc_statistics_vector(route_instance.distance);
statistics_instance.moving_time = calc_statistics_vector(route_instance.moving_time);
statistics_instance.elapsed_time = calc_statistics_vector(route_instance.elapsed_time);
statistics_instance.average_speed = calc_statistics_vector(route_instance.average_speed);
statistics_instance.average_tempo = calc_statistics_vector(route_instance.average_tempo);
statistics_instance.max_speed = calc_statistics_vector(route_instance.max_speed);

std::cout << statistics_instance;

return statistics_instance;
}

// Structs
std::ostream &operator<<(std::ostream &stream, route_statistic_struct &statistics_instance) {
    stream  << "Distance speed => " << statistics_instance.distance << std::endl
            << "Moving Time    => " << statistics_instance.moving_time << std::endl
            << "Elapsed Time   => " << statistics_instance.elapsed_time << std::endl
            << "Average Speed  => " << statistics_instance.average_speed << std::endl
            << "Average Tempo  => " << statistics_instance.average_tempo << std::endl
            << "Max speed      => " << statistics_instance.max_speed << std::endl;

    return stream;
}

std::ostream &operator<<(std::ostream &stream, statistics_struct &data_instance) {
    stream  << "Max: " << data_instance.max
            << " Min: " << data_instance.min
            << " Mean: " << data_instance.mean
            << " Median: " << data_instance.median;
    return stream;
}
