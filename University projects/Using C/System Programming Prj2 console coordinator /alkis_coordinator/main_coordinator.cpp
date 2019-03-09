#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include "pipesparams.h"
#include "World.h"
#include "Database.h"

using namespace std;

int main(int argc, char** argv) {
    char * directory = 0;
    char * main_p_snd = 0;
    char * main_p_rcv = 0;
    int pipeid_snd;
    int pipeid_rcv;
    int jpmax = 0;

    switch (argc) {
        case 9: // ./w -h1 10 -h2 10 -s 100
            if (strcmp(argv[1], "-r") == 0) {
                main_p_rcv = argv[2];
            }
            if (strcmp(argv[1], "-w") == 0) {
                main_p_snd = argv[2];
            }
            if (strcmp(argv[1], "-l") == 0) {
                directory = argv[2];
            }
            if (strcmp(argv[1], "-n") == 0) {
                jpmax = atoi(argv[4]);
            }

            if (strcmp(argv[3], "-r") == 0) {
                main_p_rcv = argv[4];
            }
            if (strcmp(argv[3], "-w") == 0) {
                main_p_snd = argv[4];
            }
            if (strcmp(argv[3], "-l") == 0) {
                directory = argv[4];
            }
            if (strcmp(argv[3], "-n") == 0) {
                jpmax = atoi(argv[4]);
            }

            if (strcmp(argv[5], "-r") == 0) {
                main_p_rcv = argv[6];
            }
            if (strcmp(argv[5], "-w") == 0) {
                main_p_snd = argv[6];
            }
            if (strcmp(argv[5], "-l") == 0) {
                directory = argv[6];
            }
            if (strcmp(argv[5], "-n") == 0) {
                jpmax = atoi(argv[6]);
            }

            if (strcmp(argv[7], "-r") == 0) {
                main_p_rcv = argv[8];
            }
            if (strcmp(argv[7], "-w") == 0) {
                main_p_snd = argv[8];
            }
            if (strcmp(argv[7], "-l") == 0) {
                directory = argv[8];
            }
            if (strcmp(argv[7], "-n") == 0) {
                jpmax = atoi(argv[8]);
            }

            if (main_p_rcv == 0 || main_p_snd == 0 || jpmax == 0 || directory == 0) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        default:
            printf("Error with argc/argv \n");
            return 0;
    }

    cout << "Pipename of pipe out              : " << main_p_snd << endl;
    cout << "Pipename of pipe in               : " << main_p_rcv << endl;

    mkfifo(main_p_snd, 0666);
    mkfifo(main_p_rcv, 0666);


    pipeid_snd = open(main_p_snd, O_RDWR);
    pipeid_rcv = open(main_p_rcv, O_RDWR);

    if (pipeid_snd < 0) {
        printf("could not open pipe of master for writing \n");
        return -1;
    }

    if (pipeid_snd < 0) {
        printf("could not open pipe of master for reading \n");
        return -1;
    }
    
    Pool::POOL_CAPACITY = jpmax;

    World world;
    
    world.make(pipeid_snd, pipeid_rcv, directory);

    // https://www.cmrr.umn.edu/~strupp/serial.html#5_2_1
    while (world.select_wait() == false) {
        
    }

    world.destroy();
    
    close(pipeid_snd);
    close(pipeid_rcv);

    unlink(main_p_snd);
    unlink(main_p_rcv);

    return 0;
}

