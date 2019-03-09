/* inet_str_client.c: Internet stream sockets client */
#include <stdio.h>
#include <sys/types.h>      /* sockets */
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <unistd.h>          /* read, write, close */
#include <netdb.h>          /* gethostbyaddr */
#include <stdlib.h>          /* exit */
#include <string.h>          /* strlen */

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "readparams.h"
#include "socketparams.h"

using namespace std;

// ./MirrorServer -p 3076 -m ./downloads -w 4

// ./MirrorInitiator -n 127.0.0.1 -p 3076 -s 127.0.0.1:2048:movies/comedy/rush\ hour\ 6/:5
// ./ContentServer -p 2048 -d ./movies


int main(int argc, char** argv) {
    const char * command_files = 0;
    const char * server_port = 0;
    const char * server_address = 0;
    int socketid;

    LineBuffer buffer;

    switch (argc) {
        case 7:
            if (strcmp(argv[1], "-n") == 0) {
                server_address = argv[2];
            }
            if (strcmp(argv[1], "-p") == 0) {
                server_port = argv[2];
            }
            if (strcmp(argv[1], "-s") == 0) {
                command_files = argv[2];
            }

            if (strcmp(argv[3], "-n") == 0) {
                server_address = argv[4];
            }
            if (strcmp(argv[3], "-p") == 0) {
                server_port = argv[4];
            }
            if (strcmp(argv[3], "-s") == 0) {
                command_files = argv[4];
            }

            if (strcmp(argv[5], "-n") == 0) {
                server_address = argv[6];
            }
            if (strcmp(argv[5], "-p") == 0) {
                server_port = argv[6];
            }
            if (strcmp(argv[5], "-s") == 0) {
                command_files = argv[6];
            }

            if (server_address == 0 || server_port == 0 || command_files == 0) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        default:
            printf("Error with argc/argv \n");
            return 0;
    }

    cout << "Address of server              : " << server_address << endl;
    cout << "Port of server                 : " << server_port << endl;
    cout << "Files:                         : " << command_files << endl;

    int port;
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct hostent *rem;

    if ((socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0 ||
            (rem = gethostbyname(server_address)) == NULL) {
        cerr << "Error while initializing sockets !!! " << endl;
        return -1;
    }

    port = atoi(server_port); /*Convert port number to integer*/

    server.sin_family = AF_INET; /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port); /* Server port */

    /* Initiate connection */
    if (connect(socketid, serverptr, sizeof (server)) < 0) {
        cerr << "Error while connecting via sockets !!! " << endl;
        return -1;
    }

    cout << "Connected successfully to " << server_address << ":" << server_port << endl;

    strcpy(buffer.data, command_files);

    SocketBuffer buffer3;
    strcpy(buffer3.data, buffer.data);

    printf("O initiator stelnei ston mirror server data: %s \n", bufferdata(&buffer3));
            
    write(socketid, (void*) &buffer3, sizeof (SocketBuffer));

    // ---------------------------------------------
//    SocketBuffer buffer4;
//    SocketBuffer buffer5;
//    read(socketid, (void*) &buffer4, sizeof (SocketBuffer));
//    read(socketid, (void*) &buffer5, sizeof (SocketBuffer));

//    printf("Files: %s \tBytes: %s \n", buffer4.data, buffer5.data);

    close(socketid);

    return 0;
}

