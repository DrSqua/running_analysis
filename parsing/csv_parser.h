//
// Created by Robbe on 30/10/2021.
//

#ifndef CSV_PARSER_CSV_PARSER_H
#define CSV_PARSER_CSV_PARSER_H

#include "iostream"

#include "vector"
#include "string"
#include "map"

// Structs -------------------------------------------------------------------------------------------------------------
struct start_time {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;

    bool operator==(const start_time& rhs) const;
    bool operator<(const start_time& rhs) const;
    friend std::ostream& operator<<(std::ostream &stream, start_time &time_instance);
};

struct polyline {
    std::string id;
    std::string summary_polyline;
    int resoure_state;

    friend std::ostream& operator<<(std::ostream &stream, polyline &polyline_instance);
};

struct RouteDataframe {
    std::vector<int> attempt;
    std::vector<double> distance;
    std::vector<double> moving_time{};
    std::vector<double> elapsed_time{};
    std::vector<std::string> type_movement;
    std::vector<polyline> map;
    std::vector<double> average_speed{};
    std::vector<double> max_speed{};
    std::vector<double> average_tempo{};
    std::vector<start_time> start_time;

    [[nodiscard]] bool empty() const {
        if (attempt.empty()) // TODO alle vectors checken (luie kut)
            return true;
        else
            return false;
    }

    friend std::ostream& operator<<(std::ostream &stream, RouteDataframe &route_instance);

    RouteDataframe& operator+=(const RouteDataframe& rhs);

    template<class T>
    static void print(const std::vector<T> &input_vector) {
        for (auto item : input_vector) {
            std::cout << item << " ";
        }
    }

    void reverse() {
        std::reverse(attempt.begin(), attempt.end());
        std::reverse(distance.begin(), distance.end());
        std::reverse(moving_time.begin(), moving_time.end());
        std::reverse(elapsed_time.begin(), elapsed_time.end());
        std::reverse(type_movement.begin(), type_movement.end());
        std::reverse(map.begin(), map.end());
        std::reverse(average_speed.begin(), average_speed.end());
        std::reverse(max_speed.begin(), max_speed.end());
        std::reverse(average_tempo.begin(), average_tempo.end());
        std::reverse(start_time.begin(), start_time.end());
    }
};

std::map<int, RouteDataframe> parse_running_csv(const std::string& filepath);

#endif //CSV_PARSER_CSV_PARSER_H