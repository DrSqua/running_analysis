#include <iostream>
#include <sstream>

#include "csv_parser.h"

using namespace std;

int main() {
    std::map<int,std::map<int, exercise_instance>> dataframe;
    string filepath = R"(C:\Users\Robbe\CLionProjects\csv_parser\emUUN_a8.csv)";
    dataframe = parse_csv(filepath);
    std::cout << dataframe[1][15];

    return 0;
}
