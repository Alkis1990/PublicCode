
#ifndef PIPEPARAMS_H
#define PIPEPARAMS_H

#define MAXPIPEBUFLENGTH 50

class PipeBuffer {
public:
    char data[MAXPIPEBUFLENGTH];
};

char * bufferdata(PipeBuffer * p);

#endif /* READPARAMS_H */

