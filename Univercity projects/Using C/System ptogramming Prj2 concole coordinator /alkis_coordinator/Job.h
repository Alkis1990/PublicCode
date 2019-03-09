
#ifndef JOB_H
#define JOB_H

#include <ctime>



class Job {
public:
    char jobid[20];
    char jobstatus[20]; // "active", "inactive", "terminated"
    time_t created_time; 
};

#endif /* PERSON_H */

