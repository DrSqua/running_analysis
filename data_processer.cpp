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

double variantie_of_vector(const std::vector<double>& input_vector, double mean) {
    double variantie = 0;
    for (auto nummer : input_vector) {
        variantie += pow(nummer-mean, 2.0);
    }
    return variantie / double(input_vector.size() - (unsigned long long) {1});
}

double calc_standaardafwijking(double mean) {
    return sqrt(mean);
}

double calc_scheefheid(const std::vector<double>& input_vector, double mean) {
    double scheefheid = 0;

    return scheefheid;
}
// Statistical Main ------------------------------------------------------------------------------------------
// Zet een vector van de waardes per attempt om naar de statistische vector
statistics_struct calc_statistics_vector(const std::vector<double>& input_vector) {
    const auto [min, max] = std::minmax_element(begin(input_vector), end(input_vector));
    double mean = mean_of_vector(input_vector);
    double variantie = variantie_of_vector(input_vector, mean);
    return (statistics_struct)
    {*max, *min, mean, median_of_vector(input_vector), variantie, calc_standaardafwijking(variantie), calc_scheefheid(input_vector, mean)};
}
statistics_struct calc_statistics_struct(const std::vector<int>& input_vector) {
    const auto [min, max] = std::minmax_element(begin(input_vector), end(input_vector));
    return (statistics_struct){double(*max), double(*min), 0, 0, 0, 0};
}


// Maakt een route_statistics_struct uit een route_struct
route_statistic_struct calculate_statistics_data(route_struct& route_instance) {
route_statistic_struct statistics_instance{};

statistics_instance.attempt = calc_statistics_struct(route_instance.attempt);
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
    stream  << "Attempt        => " << statistics_instance.attempt << std::endl
            << "Distance speed => " << statistics_instance.distance << std::endl
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
            << " Median: " << data_instance.median
            << " Variantie: " << data_instance.variantie
            << " Standaardafwijking: " << data_instance.standaardafwijking
            << " Scheefheid: " << data_instance.scheefheid;
    return stream;
}
