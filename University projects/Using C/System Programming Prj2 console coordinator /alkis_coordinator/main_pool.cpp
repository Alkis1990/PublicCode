

#include <fcntl.h>

#include "main_pool.h"
#include "PoolWorld.h"

#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void main_pool(int firstJobIDinThisPool, const char * directory, const char *main_p_snd, const char * main_p_rcv) {
    int pipeid_snd;
    int pipeid_rcv;
    
    printf("Pool created with the following parameters: %d %s %s %s \n",firstJobIDinThisPool, directory, main_p_snd, main_p_rcv);

    cout << "Pool: Pipename of pipe out              : " << main_p_snd << endl;
    cout << "Pool: Pipename of pipe in               : " << main_p_rcv << endl;

    cout << "Pool: open  pipe out              : " << main_p_snd << endl;
    pipeid_snd = open(main_p_snd, O_RDONLY);
    cout << "Pool: open  pipe in              : " << main_p_snd << endl;
    pipeid_rcv = open(main_p_rcv, O_WRONLY);
    
    cout << "Pool: ready: " << endl;

    if (pipeid_snd < 0) {
        cout << "Pool: could not open pipe of master for writing \n" << endl;
        exit(-1);
    }

    if (pipeid_snd < 0) {
        cout << "Pool: could not open pipe of master for reading \n" << endl;
        exit(-1);
    }
    
    PoolWorld poolworld;
    
    poolworld.make(pipeid_snd, pipeid_rcv, firstJobIDinThisPool, directory);

    // https://www.cmrr.umn.edu/~strupp/serial.html#5_2_1
    printf("Pool %d select() \n",firstJobIDinThisPool );
    int x = 0;
    while (poolworld.process_coordinator_message()== false && x++ < 10) {
        
    }

    poolworld.destroy();
    
    close(pipeid_snd);
    close(pipeid_rcv);

    unlink(main_p_snd);
    unlink(main_p_rcv);
    
    exit(0);
}
