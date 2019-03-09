
#ifndef WORLD_H
#define WORLD_H

#include "Database.h"
#include "Tree.h"


class World {
public:
    Database database1;
    Database database2;
    Tree tree;
    int number_of_chains1, number_of_chains2;
    
    void make(int number_of_chains1, int number_of_chains2, int groupbytes);
    void remake();
    void destroy();
    
    void ins(char * fields[]);
    void del(char * fields[]);
    void find(char * fields[]);
    void lookup(char * fields[]);
    void indist(char * fields[]);
    void topdest(char * fields[]);
    void top(char * fields[]);
    void print(char * fields[]);
    void dump(char * fields[]);
    void bye();
};

#endif /* WORLD_H */

