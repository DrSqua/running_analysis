#include <iostream>
#include <sstream>
#include <iomanip>

#include "csv_parser.h"

using namespace std;

int main() {
    string groot = "__bam__boop";
    cout << groot.substr(2, 0);


    std::map<int,std::map<int, exercise_instance>> dataframe;
    string filepath = R"(C:\Users\Robbe\CLionProjects\csv_parser\emUUN_a8.csv)";

    dataframe = parse_csv(filepath);
    cout << dataframe[1][15];
    return 0;
}
