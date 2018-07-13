#ifndef DATABASE_H
#define DATABASE_H

#include "Chain.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "findchain.h"
#include "MemoryChain.h"
#include "AddressBucket.h"
#include "AddressChain.h"

using namespace std;

#define NUMBER_OF_CHAINS 8
#define NUMBER_OF_ADDRESSCHAINS (8461)

class Allocator {
public:
    void make();
    
    char * mymalloc(size_t capacity);
    void myfree(char * address);
    
private:
    char * currentMemoryPage;
    
    MemoryChain memoryChain;
    
    Chain chains[NUMBER_OF_CHAINS];
    AddressChain addressChains[NUMBER_OF_ADDRESSCHAINS];

    int number_of_address_buckets;
    
    
    char * allocateAlignedBlock();
};

#endif /* DATABASE_H */

