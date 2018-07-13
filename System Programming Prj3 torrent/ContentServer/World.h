
#ifndef WORLD_H
#define WORLD_H

#include <pthread.h>

class World {
public:
    char * directory;
    int delay;
    
    int initiatorid;
    
    void make(int socketid, char * directory);
    void destroy();
    
    bool accept_wait();
    
    bool process_server_message(int fd);
    
    int execute(char * fields[], int elements, int newsockid);
};

#endif /* WORLD_H */

