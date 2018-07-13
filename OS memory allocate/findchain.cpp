

#include <cstdlib>

#include <iostream>

#include "findchain.h"
#include "Allocator.h"

using namespace std;

unsigned int findchain(size_t capacity)  {
    if (capacity <= 32) {
        return 0;
    }
    if (capacity <= 32*2) {
        return 1;
    }
    if (capacity <= 32*2*2) {
        return 2;
    }
    if (capacity <= 32*2*2*2) {
        return 3;
    }
    if (capacity <= 32*2*2*2*2) {
        return 4;
    }
    if (capacity <= 32*2*2*2*2*2) {
        return 5;
    }
    if (capacity <= 32*2*2*2*2*2*2) {
        return 6;
    }
    if (capacity <= 32*2*2*2*2*2*2*2) {
        return 7;
    }
    
    cout << "ooops ! error in library: out of range in findchain_insert \n";
    exit(0);
}

// returns a value from 0 to 8640 (max address chain)
unsigned int findcategory(char * address) {
    unsigned long int address_value = (unsigned long int )address;
    
    unsigned int category  = (unsigned int) ((address_value / 4096) % NUMBER_OF_ADDRESSCHAINS);
    
    return category;
}