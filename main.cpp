#include <iostream>
#include <sstream>

#include "data_processing/csv_parser.h"
#include "data_processing/data_processer.h"
#include "WindowLoop.h"

using namespace std;

int main() {
    std::map<int, route_struct> dataframe;
    string filepath = R"(C:\Users\Robbe\CLionProjects\csv_parser\emUUN_a8.csv)";
    dataframe = parse_running_csv(filepath);
    // std::cout << dataframe[1];

    WindowLoop window(dataframe, 800, 600, 60, 16, 100);
    while (window.is_loop_good()) {
        window.handle_events();
        window.update();
        window.draw();
    }
    return 0;
}