#include "GraphMinHash.h"

GraphMinHash::GraphMinHash(int number_of_hashes){
    _numhashes = number_of_hashes; 
}

int* GraphMinHash::hash(std::vector<int>& vec){
    int *hashes = new int[_numhashes];
    unsigned int hashed_value;
    unsigned int minhashed_value;
    // #pragma omp parallel for 
    for (int k=0; k < _numhashes; k++) {

        minhashed_value = std::numeric_limits<unsigned int>::max(); 
        hashes[k] = 0; 
        
        for (int i = 0; i < vec.size(); i++){
            // hashed_value = this->internalHash(vec[i], k); 
            hashed_value = MurmurHash(&(vec[i]), sizeof(int), k); 
            if (hashed_value < minhashed_value){
                minhashed_value = hashed_value; 
                hashes[k] = vec[i]; 
            }
        }
    }
    return hashes; 
}

void GraphMinHash::hash(std::vector<int>& vec, int* hashes){
    #pragma omp parallel for 
    for (int k=0; k < _numhashes; k++) {

        unsigned int hashed_value;
        unsigned int minhashed_value;

        minhashed_value = std::numeric_limits<unsigned int>::max(); 
        hashes[k] = 0; 
        
        for (int i = 0; i < vec.size(); i++){
            // hashed_value = this->internalHash(vec[i], k); 
            hashed_value = MurmurHash(&(vec[i]), sizeof(int), k); 
            if (hashed_value < minhashed_value){
                minhashed_value = hashed_value; 
                hashes[k] = vec[i]; 
            }
        }
    }
    return; 
}