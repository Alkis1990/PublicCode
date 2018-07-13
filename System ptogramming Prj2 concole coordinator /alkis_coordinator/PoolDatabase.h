#ifndef POOLDATABASE_H
#define POOLDATABASE_H

#include "Chain.h"
#include "PoolChain.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class PoolDatabase {
public:
    PoolChain poolchain;

    void make();

    void destroy();
    
    void status (char * fields[], int fd);
    
    void suspend(char * fields[], int fd);
    void resume(char * fields[], int fd);
    
};

#endif /* DATABASE_H */

