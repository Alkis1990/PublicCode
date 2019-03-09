#ifndef ADDRESSBUCKET_CHAIN_H
#define ADDRESSBUCKET_CHAIN_H

#include "AddressBucket.h"

#include <cstdio>

class AddressChain {
public:
    AddressBucket * addressBucket;
    
    void make();
    void destroy();
};

#endif /* CHAIN_H */

