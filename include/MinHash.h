#pragma once

#include <limits>
#include <vector>

#include "MurmurHash.h"


class MinHash {
 private:
	int _dim;
	int _numhashes;

 public:
	MinHash(int dimension, int number_of_hashes);
	int* getHash(const std::vector<double>& vec);
	void getHash(const std::vector<double>& vec, int* hashes);
	unsigned int internalHash(int input, int seed);
}; 



