
#ifndef POOLWORLD_H
#define POOLWORLD_H

#include "PoolDatabase.h"

class PoolWorld {
public:
    const char * directory;
    int firstJobIDinThisPool;
    PoolDatabase pooldatabase;

    int pipeid_snd, pipeid_rcv;

    void make(int pipeid_snd, int pipeid_rcv, int firstJobIDinThisPool, const char * directory);
    void destroy();

    bool process_coordinator_message();

    void submit(char * fields[]);

    void suspend(char * fields[], int fd);
    void resume(char * fields[], int fd);
    void shutdown(char * fields[], int fd);
};

#endif /* WORLD_H */

