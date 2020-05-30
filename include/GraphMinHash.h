#pragma once 

#include <limits>
#include <vector>

#include "MurmurHash.h"


class GraphMinHash {
private: 
    int _numhashes; 

public: 
    GraphMinHash(int number_of_hashes); 
    int* hash(std::vector<int>& vec); 
    void hash(std::vector<int>& vec, int* hashes); 
}; 
