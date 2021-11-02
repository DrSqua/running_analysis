#include <iostream>
#include <sstream>

#include "csv_parser.h"
#include "data_processer.h"
#include "WindowLoop.h"

using namespace std;

int main() {
    std::map<int,std::map<int, exercise_instance>> dataframe;
    string filepath = R"(C:\Users\Robbe\CLionProjects\csv_parser\emUUN_a8.csv)";
    dataframe = parse_csv(filepath);

    std::cout << dataframe[1][15];

    std::cout << mean_speed_per_route(dataframe, 1);

    WindowLoop window(800, 600, 60);
    while (window.running) {
        window.handle_event();
        window.update();
        window.draw();
    }

    return 0;
}
