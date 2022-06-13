#ifndef CSV_PARSER_DATASET_H
#define CSV_PARSER_DATASET_H

#include "raylib.h"
#include "vector"
#include "iostream"

struct DataSet {
    std::vector<float> x_points{5.0f, 10.0f, 50.0f};
    std::vector<float> y_points{20.0f, 15.0f, 50.0f};

    [[nodiscard]] Vector2 at(long long int index) const {
        if (index > x_points.size() || index > y_points.size()) throw std::out_of_range("Dataset::at() out of range");
        return {x_points.at(index), y_points.at(index)};
    }

    [[nodiscard]] bool filled() const {
        if (x_points.empty() || y_points.empty()) return false;
        return true;
    }
};

template<class T1, class T2>
DataSet createDataset(std::vector<T1>& v1, std::vector<T2>& v2) {
    std::vector<float> v1_result;
    for (auto value : v1) {
        v1_result.push_back(static_cast<float>(value));
    }

    std::vector<float> v2_result;
    for (auto value : v2) {
        v1_result.push_back(static_cast<float>(value));
    }

    return {v1_result, v2_result};
}

#endif //CSV_PARSER_DATASET_H
