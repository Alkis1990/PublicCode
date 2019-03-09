#ifndef DATABASE_H
#define DATABASE_H

#include "Chain.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "findchain.h"

using namespace std;

// Database1: key = ENT_CALLER
// Database2: key = ENT_RECEIVER

class Database {
public:
    Chain * chains;
    int number_of_chains;
    int KEY;

    void make(int number_of_chains, int KEY);

    void destroy();

    void ins(char * fields[]);

    void del(char * fields[]);

    void find(char * fields[]);

    void indist(char * fields[]);

    void topdest(char * fields[]);
    
    void top(char * fields[]);

    void print();

    void dump(char * fields[]);
    
    bool space(char * fields[], Entry * e);
};

#endif /* DATABASE_H */

