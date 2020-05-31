#include "RACE.h"
#include "L2Hash.h"
#include "MurmurHash.h"
#include "MinHash.h"
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
	/* Read in the dataset */
	std::cout << "Reading data..." << std::endl;
	// if running with cmake, use parent directory; otherwise check working directory and change relative path
	std::ifstream data_file("../dat/criteo_mini.txt");
	std::vector<std::vector<double>> data;
//	ReadData(data_file, data);
	std::vector<double> d;
	VectorFeatures(data_file, d);

	/* Verify everything got read properly */
//	for (const auto& r : data) {
//		for (auto& p : r)
//			std::cout << " " << p << " ";
//		std::cout << std::endl;
//	}

	/*
	 * Pre-process into RACE. The first 13 features are integer features (use L2 hash), the last 26 features are
	 * categorical features (use MinHash). We need to combine them, so just insert the product of the two hashes into
	 * the sketch.
	 */
	const size_t L = 200, R = 1000;
	RACE sketch = RACE(L, R);  // 200 repetitions, 1000 range
	L2Hash l2 = L2Hash(13, L, 1.0);
	MinHash mh = MinHash(26, L);
	int* hashes = new int[L];
	int* minHashes = new int[L];
	std::cout << data.size() << std::endl;

	for (const auto& row : data) {
		std::vector<double> intFeatures = std::vector<double>(row.begin(), row.begin() + 13);
		std::vector<double> catFeatures = std::vector<double>(row.begin() + 13, row.end());


		l2.getHash(intFeatures, hashes);
		mh.getHash(catFeatures, minHashes);

		// TODO: is there an STL map operation?
		for (int i = 0; i < L; i++) {
			hashes[i] *= minHashes[i];
		}

		sketch.add(hashes);
	}
	delete[] hashes;

}
