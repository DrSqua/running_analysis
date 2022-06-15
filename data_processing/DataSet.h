#ifndef CSV_PARSER_DATASET_H
#define CSV_PARSER_DATASET_H

#include "raylib.h"
#include "vector"
#include "iostream"
#include <algorithm>

struct DataSet {
    std::vector<float> x_points{};
    std::vector<float> y_points{};

    [[nodiscard]] Vector2 at(long long int index) const {
        if (index > x_points.size() || index > y_points.size()) throw std::out_of_range("Dataset::at() out of range");
        return {x_points.at(index), y_points.at(index)};
    }


    //! Check methods
    // Returns true if both arrays are filled
    [[nodiscard]] bool filled() const {
        if (x_points.empty() || y_points.empty()) return false;
        return true;
    }
    // Returns true if both arrays are the same length
    [[nodiscard]] bool filled_equal() const {
        if (!filled()) return false;
        if (x_points.size() != y_points.size()) return false;
        return true;
    }
    // Returns true if both vectors of both arrays all have the same length
    [[nodiscard]] bool same_size(const DataSet& r_dataset) const {
        if (!filled() || !r_dataset.filled()) return false;
        if (x_points.size() != r_dataset.x_points.size()) return false;
        return true;
    }
};

template<class T1, class T2>
DataSet createDataset(std::vector<T1>& v1_input, std::vector<T2>& v2_input) {
    std::vector<float> v1_result;
    for (auto value : v1_input) {
        v1_result.push_back(static_cast<float>(value));
    }

    std::vector<float> v2_result;
    for (auto value : v2_input) {
        v2_result.push_back(static_cast<float>(value));
    }

    return {v1_result, v2_result};
}

std::vector<float> normalizeVector(const std::vector<float>& vector_input, float span);
DataSet normalizeDataset(const DataSet& dataSet_input, int x_span, int y_span);

#endif //CSV_PARSER_DATASET_H
