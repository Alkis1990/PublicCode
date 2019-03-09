
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "readparams.h"
#include "pipesparams.h"

using namespace std;


// ./mc -r pipe -w pipe -o command_file

int main(int argc, char** argv) {
    const char * command_file = 0;
    const char * main_p_snd = 0;
    const char * main_p_rcv = 0;
    int pipeid_snd;
    int pipeid_rcv;
    int i;

    bool read_from_keyboard = true;

    switch (argc) {
        case 5: // ./mc -r pipe -w pipe -o command_file
            if (strcmp(argv[1], "-r") == 0) {
                main_p_rcv = argv[2];
            }
            if (strcmp(argv[1], "-w") == 0) {
                main_p_snd = argv[2];
            }

            if (strcmp(argv[3], "-r") == 0) {
                main_p_rcv = argv[4];
            }
            if (strcmp(argv[3], "-w") == 0) {
                main_p_snd = argv[4];
            }
            if (main_p_rcv == 0 || main_p_snd == 0) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        case 7:
            if (strcmp(argv[1], "-r") == 0) {
                main_p_rcv = argv[2];
            }
            if (strcmp(argv[1], "-w") == 0) {
                main_p_snd = argv[2];
            }
            if (strcmp(argv[1], "-o") == 0) {
                command_file = argv[2];
            }

            if (strcmp(argv[3], "-r") == 0) {
                main_p_rcv = argv[4];
            }
            if (strcmp(argv[3], "-w") == 0) {
                main_p_snd = argv[4];
            }
            if (strcmp(argv[3], "-o") == 0) {
                command_file = argv[4];
            }

            if (strcmp(argv[5], "-r") == 0) {
                main_p_rcv = argv[6];
            }
            if (strcmp(argv[5], "-w") == 0) {
                main_p_snd = argv[6];
            }
            if (strcmp(argv[5], "-o") == 0) {
                command_file = argv[6];
            }

            if (main_p_rcv == 0 || main_p_snd == 0 || command_file == 0) {
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
    if (command_file != 0) {
        cout << "Command file                      : " << command_file << endl;
    }

    FILE * fp = stdin;

    pipeid_snd = open(main_p_snd, O_WRONLY);
    pipeid_rcv = open(main_p_rcv, O_RDONLY);

    if (pipeid_snd < 0) {
        printf("could not open pipe of master for writing \n");
        return -1;
    }

    if (pipeid_snd < 0) {
        printf("could not open pipe of master for reading \n");
        return -1;
    }


    if (command_file != NULL) {
        read_from_keyboard = false;
        fp = fopen(command_file, "r");
        if (fp == NULL) {
            read_from_keyboard = true;
        }
    }

    LineBuffer buffer;
    LineBuffer buffer2;

    while (1) {
        if (read_from_keyboard == true) {
            cout << " ? ";
        }
        if (fgets(buffer.data, sizeof (buffer.data), fp) <= 0) {
            if (read_from_keyboard == true) {
                break;
            } else if (read_from_keyboard == false) {
                fp = stdin;
                read_from_keyboard = true;
                continue;
                //                break;
            }
        }

        if (strncmp(buffer.data, "submit", 6) == 0) { // insert         
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            
            printf("H console stelnei ston coordinator submit me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // ---------------------------------------------
            PipeBuffer buffer4;
            PipeBuffer buffer5;
            read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
            read(pipeid_rcv, (void*) &buffer5, sizeof (PipeBuffer));

            printf("JobID: %s \tPID: %s \n", buffer4.data, buffer5.data);
        }

        if (strncmp(buffer.data, "status ", 7) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator status me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // ---------------------------------------------
            PipeBuffer buffer4;
            PipeBuffer buffer5;
            read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
            read(pipeid_rcv, (void*) &buffer5, sizeof (PipeBuffer));

            if (strcmp(buffer5.data, "active") == 0) {
//                PipeBuffer buffer6;
//                read(pipeid_rcv, (void*) &buffer6, sizeof (PipeBuffer));
//
                printf("JobID: %s Status: %s  (running for %d seconds) \n", buffer4.data, buffer5.data, 1821);
            } else {
                printf("JobID: %s Status: %s \n", buffer4.data, buffer5.data);
            }
        }


        if (strncmp(buffer.data, "status-all", 10) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator status all me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            PipeBuffer buffern;
            while (1) {
                read(pipeid_rcv, (void*) &buffern, sizeof (PipeBuffer));
                if (strcmp(buffern.data, "finish") == 0) {
                    break;
                } else {
                    printf("status: %s \n", buffern.data);
                }
            }
        }

        if (strncmp(buffer.data, "show-active", 11) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator show-active me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            i = 0;
            while (1) {
                PipeBuffer buffern;
                read(pipeid_rcv, (void*) &buffern, sizeof (PipeBuffer));
                i++;
                if (strcmp(buffern.data, "finish") == 0) {
                    break;
                } else {
                    printf("%d. JobID: %s \n", i, buffern.data);
                }
            }
        }

        if (strncmp(buffer.data, "show-pools", 10) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator show-pools me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            PipeBuffer buffer4;
            PipeBuffer buffer5;
            i = 0;
            while (1) {
                i++;
                read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
                if (strcmp(buffer4.data, "finish") == 0) {
                    break;
                } else {
                    read(pipeid_rcv, (void*) &buffer5, sizeof (PipeBuffer));
                    printf("%d. %s %s \n", i, buffer4.data, buffer5.data);
                }
            }
        }

        if (strncmp(buffer.data, "show-finished", 13) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator show-finished me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            i = 0;
            while (1) {
                PipeBuffer buffern;
                read(pipeid_rcv, (void*) &buffern, sizeof (PipeBuffer));
                i++;
                if (strcmp(buffern.data, "finish") == 0) {
                    break;
                } else {
                    printf("%d. JobID: %s \n", i, buffern.data);
                }
            }
        }


        if (strncmp(buffer.data, "suspend", 7) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator suspend me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            PipeBuffer buffer4;
            read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));

            printf("%s \n", buffer4.data);
        }
        

        if (strncmp(buffer.data, "resume", 6) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator suspend me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
            // -----------------------------------------------
            PipeBuffer buffer4;
            read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
            printf("%s \n", buffer4.data);
        }
        

        if (strncmp(buffer.data, "shutdown", 8) == 0) {
            PipeBuffer buffer3;
            strcpy(buffer3.data, buffer.data);
            printf("H console stelnei ston coordinator shutdown me data: %s \n", bufferdata(&buffer3));
            write(pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));

            // -----------------------------------------------
            PipeBuffer buffer4;
            read(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
            printf("%s \n", buffer4.data);
            break;
        }
    }
    if (fp != NULL) {
        fclose(fp);
    }

    close(pipeid_snd);
    close(pipeid_rcv);

    return 0;
}

