#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "L2Hash.h"
#include "MinHash.h"
#include "MurmurHash.h"
#include "RACE.h"
#include "driver.h"
#include "io.h"
#include "util.h"

/*

Heuristics for choosing reps and range
Range increases as W decreases
Range increases at higher powers K

Reps need to increase whenever sum p(x,q) becomes large
- there should be a range-reps tradeoff

sigma = 20.0

*/

int main() {
    /* Read in the dataset */
    std::cout << "Reading data..." << std::endl;
    // if running with cmake, use parent directory; otherwise check working directory and change relative path
    std::ifstream data_file("../dat/criteo_mini.txt");
    std::vector<std::vector<double>> data;
    ReadData(data_file, data);

    /* Verify everything got read properly */
    for (const auto& r : data) {
        for (auto& p : r) std::cout << " " << p << " ";
        std::cout << std::endl;
    }
}
