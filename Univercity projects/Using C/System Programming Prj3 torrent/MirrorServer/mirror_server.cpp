#include <stdio.h>
#include <sys/wait.h>      /* sockets */
#include <sys/types.h>      /* sockets */
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <netdb.h>          /* gethostbyaddr */
#include <unistd.h>          /* fork */  
#include <stdlib.h>          /* exit */
#include <ctype.h>          /* toupper */
#include <signal.h>          /* signal */

#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include "socketparams.h"
#include "World.h"

using namespace std;

int main(int argc, char** argv) {
    char * threadnum = 0;
    char * directory = 0;
    char * server_port = 0;
    int socketid;

    switch (argc) {
        case 7: // ./w -h1 10 -h2 10 -s 100
            if (strcmp(argv[1], "-p") == 0) {
                server_port = argv[2];
            }
            if (strcmp(argv[1], "-m") == 0) {
                directory = argv[2];
            }
            if (strcmp(argv[1], "-w") == 0) {
                threadnum = argv[2];
            }

            if (strcmp(argv[3], "-p") == 0) {
                server_port = argv[4];
            }
            if (strcmp(argv[3], "-m") == 0) {
                directory = argv[4];
            }
            if (strcmp(argv[3], "-w") == 0) {
                threadnum = argv[4];
            }

            if (strcmp(argv[5], "-p") == 0) {
                server_port = argv[6];
            }
            if (strcmp(argv[5], "-m") == 0) {
                directory = argv[6];
            }
            if (strcmp(argv[5], "-w") == 0) {
                threadnum = argv[6];
            }

            if (server_port == 0 || directory == 0 || threadnum == 0) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        default:
            printf("Error with argc/argv \n");
            return 0;
    }

    cout << "Port      of Server               : " << server_port << endl;
    cout << "Directory of Server               : " << directory << endl;

    int port;
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr *) &server;

    port = atoi(server_port);

    /* Create socket */
    if ((socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "socket error" << endl;
        return 0;
    }

    server.sin_family = AF_INET; /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port); /* The given port */

    /* Bind socket to address */
    if (bind(socketid, serverptr, sizeof (server)) < 0) {
        cerr << "bind error" << endl;
        return 0;
    }
    /* Listen for connections */
    if (listen(socketid, 5) < 0) {
        cerr << "listen error" << endl;
        return 0;
    }

    printf("Listening for connections to port %d\n", port);

    Queue::CAPACITY = 50;

    World world;

    world.make(socketid, directory, atoi(threadnum));

    for (int i = 0; i < atoi(threadnum); i++) {
        pthread_create(world.worker_threadids + i, NULL, consumer, &world);
    }


    // https://www.cmrr.umn.edu/~strupp/serial.html#5_2_1
    while (world.accept_wait() == false) {

    }
    
    for (int i = 0; i < atoi(threadnum); i++) {
        pthread_join(*(world.worker_threadids + i), NULL);
    }

    world.destroy();

    close(socketid);

    return 0;
}

