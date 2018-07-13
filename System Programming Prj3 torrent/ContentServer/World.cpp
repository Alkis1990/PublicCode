#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>      /* sockets */
#include <sys/socket.h>      /* sockets */
#include <netinet/in.h>      /* internet sockets */
#include <netdb.h>          /* gethostbyaddr */
#include <unistd.h>          /* fork */  
#include <stdlib.h>          /* exit */
#include <ctype.h>          /* toupper */

#include "World.h"
#include "socketparams.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#include <sys/select.h>
#include <unistd.h>

#include <errno.h>

using namespace std;

void World::make(int socketid, char * directory) {
    this->initiatorid = socketid;
    this->directory = directory;
}

void World::destroy() {

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

    if (process_server_message(newsockid)) {
        return true;
    }
    return false;
}

bool World::process_server_message(int newsockid) {
    SocketBuffer incomingbuffer;
    SocketBuffer buffer;
    read(newsockid, (void*) &incomingbuffer, sizeof (SocketBuffer));

    cout << "o content server elave: " << bufferdata(&incomingbuffer) << endl;

    char * p = incomingbuffer.data;

    int comma = 0;
    int elements = 0;
    while (*p != '\0') {
        if (*p == ' ') {
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

        while (*p != ' ' && *p != '\0') {
            buffer.data[j] = *p;
            p++;
            j++;
        }
        buffer.data[j] = '\0';
        p++;

        fields[i] = new char[j + 1];
        strcpy(fields[i], buffer.data);

        if (strcmp(fields[0], "FETCH") == 0) {
            j = 0;
            while (*p != '\0') {
                buffer.data[j] = *p;
                p++;
                j++;
            }
            buffer.data[j] = '\0';
            fields[1] = new char[j + 1];
            strcpy(fields[1], buffer.data);
            elements = 2;

            break;
        }
    }

    cout << "EXECUTE: " << endl;
    for (int i = 0; i < elements; i++) {
        if (fields[i] != NULL) {
            cout << "\t" << i << " " << fields[i] << endl;
        } else {
            cout << "\t" << i << " " << "NULL" << endl;
        }
    }

    execute(fields, elements, newsockid);

    close(newsockid);

    return false;
}

// creates a new pool if needed to the database
// adds the new job to the database
// returns the outgoing descriptor (snd) of that pool

// 1. LIST X DELAY
// 2. FETCH FILE


// https://www.lemoda.net/c/recursive-directory/

static void list_dir(const char * dir_name, int newsockid) {
    DIR * d;

    d = opendir(dir_name);

    if (!d) {
        fprintf(stderr, "Cannot open directory '%s': %s\n", dir_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct dirent * entry;
        const char * d_name;

        entry = readdir(d);
        if (!entry) {
            break;
        }
        d_name = entry->d_name;

        if (!(entry->d_type & DT_DIR)) {
            SocketBuffer buffer1;
            sprintf(buffer1.data, "%s/%s\n", dir_name, d_name);

            printf("found: %s \n", buffer1.data);
            write(newsockid, (void*) &buffer1, sizeof (SocketBuffer));
        }

        if (entry->d_type & DT_DIR) {
            if (strcmp(d_name, "..") != 0 &&
                    strcmp(d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];

                path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, d_name);
                //                printf("%s\n", path);

                if (path_length >= PATH_MAX) {
                    exit(EXIT_FAILURE);
                }
                /* Recursively call "list_dir" with the new path. */
                list_dir(path, newsockid);
            }
        }
    }

    if (closedir(d)) {
        fprintf(stderr, "Could not close '%s': %s\n", dir_name, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int World::execute(char * fields[], int elements, int newsockid) {
    if (strcmp(fields[0], "LIST") == 0) {
        // ======================= LIST  =====================
        printf("======================= LIST  =====================\n");

        delay = atoi(fields[2]);
        list_dir(directory, newsockid);

        SocketBuffer buffer1;
        strcpy(buffer1.data, "finish");
        write(newsockid, (void*) &buffer1, sizeof (SocketBuffer));
    }

    if (strcmp(fields[0], "FETCH") == 0) {
        // ======================= FETCH =====================
        printf("======================= FETCH  =====================\n");
        int i;
        for (i = 0; i < delay; i++) {
            printf("zzZzzzzz! \n");
            sleep(1);
        }
    }
    return 0;
}