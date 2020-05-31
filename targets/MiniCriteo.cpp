#include "RACE.h"
#include "L2Hash.h"
#include "MurmurHash.h"
#include "io.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

#include "util.h"
#include "driver.h"


/*

Heuristics for choosing reps and range
Range increases as W decreases
Range increases at higher powers K

Reps need to increase whenever sum p(x,q) becomes large
- there should be a range-reps tradeoff

sigma = 20.0

*/


int main() {
	std::cout << "Reading data..." << std::endl;
	std::ifstream data_file("criteo_mini.txt");

	std::vector<std::vector<double>> data;


	ReadData(data_file, data);

	for (const auto& r : data) {
		for (auto &p : r)
			std::cout << " " << p << " ";
		std::cout << std::endl;
	}

	return 0;
}
