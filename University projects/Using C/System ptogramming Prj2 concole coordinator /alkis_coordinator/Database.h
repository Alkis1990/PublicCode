#ifndef DATABASE_H
#define DATABASE_H

#include "Chain.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Database {
public:
    Chain chain;

    void make();

    void destroy();

    bool space(time_t created_time, int td);

    void status(char * fields[], int fd);
    void status_all(char * fields[], int fd);
    void show_status(char * fields[], int fd);
    void show_pools(char * fields[], int fd);
    void show_active(char * fields[], int fd);
    void show_finished(char * fields[], int fd);


    void suspend(char * fields[]);
    void resume(char * fields[]);

    void suspend_pool(char * fields[]);
//    void resume(char * fields[]);



    void shutdown();
};

#endif /* DATABASE_H */

