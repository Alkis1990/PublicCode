
#ifndef STRUCTURE_H
#define STRUCTURE_H

#define IDLENGTH 5
#define SEM_EMPTY_POS   0
#define SEM_FULL_POS    1
#define SEM_STATS       0

struct Part {
    char id[IDLENGTH + 1];
    char type;                          // X,Y,Z
    clock_t constructionTime;    
} Part;

struct Slot {
    struct Part part;
} Slot;

struct Statistics {
    double constructionDelay;
} Statistics;

union senum {
    int val;
    struct semid_ds * buff;
    unsigned short *array;
};

void downFull(int semid) ;

void downEmpty(int semid);

void downStats(int semid);

void upFull(int semid);

void upEmpty(int semid);

void upStats(int semid);


#endif /* STRUCTURE_H */
