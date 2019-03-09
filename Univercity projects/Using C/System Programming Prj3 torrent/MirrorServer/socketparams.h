
#ifndef SOCKETPARAMS_H
#define SOCKETPARAMS_H

#define MAXSOCKETBUFLENGTH 4096

class SocketBuffer {
public:
    char data[MAXSOCKETBUFLENGTH];
};

char * bufferdata(SocketBuffer * p);

#endif /* READPARAMS_H */

