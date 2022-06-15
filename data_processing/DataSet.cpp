//
// Created by Robbe on 14/06/2022.
//
#include "DataSet.h"

DataSet normalizeDataset(const DataSet &dataSet_input, const int x_span, const int y_span) {
    return {normalizeVector(dataSet_input.x_points, (float)x_span), normalizeVector(dataSet_input.y_points, (float)y_span)};
}

std::vector<float> normalizeVector(const std::vector<float> &vector_input, const float span) {
    auto minimum = *std::min_element(vector_input.begin(), vector_input.end()); // Die * Is Belangrijk, moek nog is goe snappen
    auto maximum = *std::max_element(vector_input.begin(), vector_input.end());
    auto parameter = span/(maximum-minimum);

    std::vector<float> normalized_vector{};
    normalized_vector.reserve(vector_input.size());
    for (auto value : vector_input) {
            normalized_vector.emplace_back((value - minimum) * parameter);
        }
    return normalized_vector;
}
