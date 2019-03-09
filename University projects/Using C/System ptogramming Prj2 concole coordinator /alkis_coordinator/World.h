
#ifndef WORLD_H
#define WORLD_H

#include "Database.h"


class World {
public:
    char * directory;
    Database database;
    
    int console_pipeid_snd, console_pipeid_rcv;
    
    void make(int pipeid_snd, int pipeid_rcv, char * directory);
    void destroy();
    
    bool select_wait();
    
    bool process_console_message();
    
    void process_pool_message(int fd);
    
    int submit(char * fields[]);
    
    void submitfrompool(char * fields[]);
};

#endif /* WORLD_H */

