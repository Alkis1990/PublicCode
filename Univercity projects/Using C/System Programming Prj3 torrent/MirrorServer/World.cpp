
#include <stdio.h>
#include <sys/types.h>      /* sockets */
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <netdb.h>          /* gethostbyaddr */
#include <unistd.h>          /* fork */  
#include <stdlib.h>          /* exit */
#include <ctype.h>          /* toupper */

#include "World.h"
#include "Queue.h"
#include "socketparams.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#include <sys/select.h>
#include <unistd.h>

using namespace std;

Queue * World::queue = NULL;

void * consumer(void * params) {
    SocketBuffer incomingbuffer;

    cout << "Consumer created ! " << endl;

    while (1) {
        char * pendingdownload = World::queue->obtain();

        printf("Downloading : %s ... \n", pendingdownload);

        char * p = (char*) pendingdownload;

        int semicolon = 0;
        int elements = 0;
        while (*p != '\0') {
            if (*p == '/') {
                semicolon++;
            }
            p++;
        }

        elements = semicolon + 1;

        //        cout << "Elements detected: " << elements << endl;

        char * fields[elements];

        p = (char*) pendingdownload;

        for (int i = 0; i < elements; i++) {
            int j = 0;

            while (*p != '/' && *p != '\0') {
                incomingbuffer.data[j] = *p;
                p++;
                j++;
            }
            incomingbuffer.data[j] = '\0';
            p++;

            fields[i] = new char[j + 1];
            strcpy(fields[i], incomingbuffer.data);
        }

        cout << "FETCH: " << endl;
        for (int i = 0; i < elements; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }

        int port;
        struct sockaddr_in server;
        struct sockaddr *serverptr = (struct sockaddr*) &server;
        struct hostent *rem;
        int socketid;

        if ((socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0 ||
                (rem = gethostbyname(fields[0])) == NULL) {
            cerr << "Error while initializing sockets !!! " << endl;
            return NULL;
        }

        port = atoi(fields[1]); /*Convert port number to integer*/

        server.sin_family = AF_INET; /* Internet domain */
        memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
        server.sin_port = htons(port); /* Server port */

        /* Initiate connection */
        if (connect(socketid, serverptr, sizeof (server)) < 0) {
            cerr << "Error while connecting via sockets !!! " << endl;
            return NULL;
        }

        SocketBuffer buffer3; // LIST IPPORT DELAY
        strcpy(buffer3.data, "FETCH ");
        strcat(buffer3.data, fields[4]);

        // send list
        write(socketid, (void*) &buffer3, sizeof (SocketBuffer));

        // download file ...
        SocketBuffer buffer4;
        read(socketid, (void*) &buffer4, sizeof (SocketBuffer));


        close(socketid);
    }

    return 0;
}

void * producer(void * params) {
    SocketBuffer incomingbuffer;
    cout << "Producer created for field: " << (char*) params << endl;


    char * p = (char*) params;

    int semicolon = 0;
    int elements = 0;
    while (*p != '\0') {
        if (*p == ':') {
            semicolon++;
        }
        p++;
    }

    elements = semicolon + 1;

    cout << "Elements detected: " << elements << endl;

    char * fields[elements];

    p = (char*) params;

    for (int i = 0; i < elements; i++) {
        int j = 0;

        while (*p != ':' && *p != '\0') {
            incomingbuffer.data[j] = *p;
            p++;
            j++;
        }
        incomingbuffer.data[j] = '\0';
        p++;

        fields[i] = new char[j + 1];
        strcpy(fields[i], incomingbuffer.data);
    }

    cout << "LIST: " << endl;
    for (int i = 0; i < elements; i++) {
        if (fields[i] != NULL) {
            cout << "\t" << i << " " << fields[i] << endl;
        } else {
            cout << "\t" << i << " " << "NULL" << endl;
        }
    }

    // fields[0] = IP
    // fields[1] = PORT
    // fields[2] = FILTER (FILE/DIRECTORY)
    // fields[3] = DELAY

    int port;
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct hostent *rem;
    int socketid;

    if ((socketid = socket(PF_INET, SOCK_STREAM, 0)) < 0 ||
            (rem = gethostbyname(fields[0])) == NULL) {
        cerr << "Error while initializing sockets !!! " << endl;
        return NULL;
    }

    port = atoi(fields[1]); /*Convert port number to integer*/

    server.sin_family = AF_INET; /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port); /* Server port */

    /* Initiate connection */
    if (connect(socketid, serverptr, sizeof (server)) < 0) {
        cerr << "Error while connecting via sockets !!! " << endl;
        return NULL;
    }

    SocketBuffer buffer3; // LIST IPPORT DELAY
    strcpy(buffer3.data, "LIST X ");
    strcat(buffer3.data, fields[3]);

    // send list
    write(socketid, (void*) &buffer3, sizeof (SocketBuffer));


    // receive list
    SocketBuffer buffer4;
    int i = 0;
    while (1) {
        i++;
        read(socketid, (void*) &buffer4, sizeof (SocketBuffer));
        if (strcmp(buffer4.data, "finish") == 0) {
            break;
        } else {
            // filter and produce
            if (strncmp(buffer4.data, fields[2], strlen(fields[2])) == 0) {
                printf("%d. %s   MATCH \n", i, buffer4.data);

                char * newarray = (char*) malloc(1000);
                sprintf(newarray, "%s/%s/%s", fields[0], fields[1], buffer4.data);
                World::queue->place(newarray);
            } else {
                printf("%d. %s   MISS \n", i, buffer4.data);
            }
        }
    }

    return 0;
}

void World::make(int socketid, char * directory, int threadnum) {
    this->initiatorid = socketid;
    this->directory = directory;
    this->threadnum = threadnum;

    worker_threadids = new pthread_t[threadnum];

    queue = new Queue();
    queue->make();
}

void World::destroy() {
    delete [] worker_threadids;
    delete queue;
}

bool World::accept_wait() {
    int newsockid = 0;

    socklen_t clientlen;
    struct sockaddr_in client;
    struct sockaddr *clientptr = (struct sockaddr *) &client;

    clientlen = sizeof (client);

    /* accept connection */
    if ((newsockid = accept(initiatorid, clientptr, &clientlen)) < 0) {
        return false;
    }

    cout << "Accepted connection" << endl;

    if (process_initiator_message(newsockid)) {
        return true;
    }
    return false;
}

bool World::process_initiator_message(int fd) {
    SocketBuffer incomingbuffer;
    SocketBuffer buffer;
    read(fd, (void*) &incomingbuffer, sizeof (SocketBuffer));

    cout << "o coordinator elave: " << bufferdata(&incomingbuffer) << endl;

    char * p = incomingbuffer.data;

    int comma = 0;
    int elements = 0;
    while (*p != '\0') {
        if (*p == ',') {
            comma++;
        }
        p++;
    }

    elements = comma + 1;

    cout << "Elements detected: " << elements << endl;

    char * fields[elements];

    p = incomingbuffer.data;

    for (int i = 0; i < elements; i++) {
        int j = 0;

        while (*p != ',' && *p != '\0') {
            buffer.data[j] = *p;
            p++;
            j++;
        }
        buffer.data[j] = '\0';
        p++;

        fields[i] = new char[j + 1];
        strcpy(fields[i], buffer.data);
    }

    cout << "EXECUTE: " << endl;
    for (int i = 0; i < elements; i++) {
        if (fields[i] != NULL) {
            cout << "\t" << i << " " << fields[i] << endl;
        } else {
            cout << "\t" << i << " " << "NULL" << endl;
        }
    }

    execute(fields, elements);

    return false;
}

// creates a new pool if needed to the database
// adds the new job to the database
// returns the outgoing descriptor (snd) of that pool

int World::execute(char * fields[], int elements) {
    manager_threadids = new pthread_t[elements];

    for (int i = 0; i < elements; i++) {
        pthread_create(manager_threadids + i, NULL, producer, fields[i]);
    }

    for (int i = 0; i < elements; i++) {
        pthread_join(*(manager_threadids + i), NULL);
    }

    return 0;
}