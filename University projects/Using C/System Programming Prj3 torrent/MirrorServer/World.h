
#ifndef WORLD_H
#define WORLD_H

#include <pthread.h>

#include "Queue.h"

class World {
public:
    char * directory;
    static Queue * queue;
    
    int initiatorid;
    int threadnum;
    
    pthread_t * worker_threadids;
    pthread_t * manager_threadids;
    
    void make(int socketid, char * directory, int threadnum);
    void destroy();
    
    bool accept_wait();
    
    bool process_initiator_message(int fd);
    
    int execute(char * fields[], int elements);
};

void * consumer(void * params) ;
void * producer(void * params);

#endif /* WORLD_H */

