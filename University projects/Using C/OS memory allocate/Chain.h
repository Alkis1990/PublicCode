#ifndef CHAIN_H
#define CHAIN_H

#include "Bucket.h"

#include <cstdio>

class Chain {
public:
    Bucket * bucket;
    int number_of_buckets;
    int min;
    int max;
    
    int number_of_bits; // number of bits for a bitmap in this chain
    int number_of_bytes; // number of bytes for a bitmap in this chain
    
    void make(int min, int max);
};

#endif /* CHAIN_H */

