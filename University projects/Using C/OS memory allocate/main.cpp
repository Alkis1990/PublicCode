
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "mymalloc.h"

using namespace std;

void ** allocate_many_times(int N, int size) {
    void ** data = new void*[N];

    for (int i = 0; i < N; i++) {
        data[i] = mymalloc(size);
    }

    return data;
}

void show(void ** p, int i) {
    unsigned long int temp = (unsigned long int ) p[i];
    cout << dec << i << ":" << dec << temp << "\t" << hex << p[i] << endl;
}

void dokimi1() {
    void ** data;

    data = allocate_many_times(129, 25);

    for (int i = 0; i < 129; i++) {
        show(data, i);
    }
}

void dokimi2() {
    void ** data;

    data = allocate_many_times(65, 59);

    for (int i = 0; i < 65; i++) {
        show(data, i);
    }
}

void dokimi3() {
    void ** data;

    data = allocate_many_times(33, 111);

    for (int i = 0; i < 33; i++) {
        show(data, i);
    }
}

void dokimi4() {
    void ** data;

    data = allocate_many_times(17, 256);

    for (int i = 0; i < 17; i++) {
        show(data, i);
    }
}

void dokimi5() {
    void ** data;

    data = allocate_many_times(9, 512);

    for (int i = 0; i < 9; i++) {
        show(data, i);
    }
}

void dokimi6() {
    void ** data;

    data = allocate_many_times(5, 1024);

    for (int i = 0; i < 5; i++) {
        show(data, i);
    }
}

void dokimi7() {
    void ** data;

    data = allocate_many_times(3, 2048);

    for (int i = 0; i < 3; i++) {
        show(data, i);
    }
}

void dokimi8() {
    void ** data;

    data = allocate_many_times(2, 4096);

    for (int i = 0; i < 2; i++) {
        show(data, i);
    }
}


void dokimiMB1() {
//    void ** data;
    int N = 128;
    int P = 255;

    allocate_many_times((N*P)+1, 32);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB2() {
//    void ** data;
    int N = 64;
    int P = 255;

    allocate_many_times((N*P)+1, 64);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB3() {
//    void ** data;
    int N = 32;
    int P = 255;

    allocate_many_times((N*P)+1, 128);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB4() {
//    void ** data;
    int N = 16;
    int P = 255;

    allocate_many_times((N*P)+1, 256);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB5() {
//    void ** data;
    int N = 8;
    int P = 255;

    allocate_many_times((N*P)+1, 512);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB6() {
//    void ** data;
    int N = 4;
    int P = 255;

    allocate_many_times((N*P)+1, 1024);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiMB7() {
//    void ** data;
    int N = 2;
    int P = 255;

    allocate_many_times((N*P)+1, 2048);

//    for (int i = 0; i < N*P+1; i++) {
//        show(data, i);
//    }
}

void dokimiFree1() {
    void ** data;

    data = allocate_many_times(129, 32);

    for (int i = 0; i < 129; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 129; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(256, 32);
    
    for (int i = 0; i < 256; i++) {
        show(data, i);
    }
}

void dokimiFree2() {
    void ** data;

    data = allocate_many_times(65, 64);

    for (int i = 0; i < 65; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 65; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(128, 64);
    
    for (int i = 0; i < 128; i++) {
        show(data, i);
    }
}

void dokimiFree3() {
    void ** data;

    data = allocate_many_times(33, 128);

    for (int i = 0; i < 33; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 33; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(64, 128);
    
    for (int i = 0; i < 64; i++) {
        show(data, i);
    }
}

void dokimiFree4() {
    void ** data;

    data = allocate_many_times(17, 256);

    for (int i = 0; i < 17; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 17; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(32, 256);
    
    for (int i = 0; i < 32; i++) {
        show(data, i);
    }
}

void dokimiFree5() {
    void ** data;

    data = allocate_many_times(9, 512);

    for (int i = 0; i < 9; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 9; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(16, 512);
    
    for (int i = 0; i < 16; i++) {
        show(data, i);
    }
}

void dokimiFree6() {
    void ** data;

    data = allocate_many_times(5, 1024);

    for (int i = 0; i < 5; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 5; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(8, 1024);
    
    for (int i = 0; i < 8; i++) {
        show(data, i);
    }
}

void dokimiFree7() {
    void ** data;

    data = allocate_many_times(3, 2048);

    for (int i = 0; i < 3; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 3; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(4, 2048);
    
    for (int i = 0; i < 4; i++) {
        show(data, i);
    }
}

void dokimiFree8() {
    void ** data;

    data = allocate_many_times(2, 4096);

    for (int i = 0; i < 2; i++) {
        show(data, i);
    }
    
    for (int i = 0; i < 2; i++) {
        myfree((char*) data[i]);
    } 
    cout << "**********************************************" << endl;
    data = allocate_many_times(2, 4096);
    
    for (int i = 0; i < 2; i++) {
        show(data, i);
    }
}

void finaltest() {
    char *p[5000];
    int N = 5000;
    srand(time(0));

    int i;
    for (i = 0; i < N; i++) {
        int r = 1 + rand() % 5000;
        p[i] = mymalloc(r);
    }


    for (i = 0; i < N; i++) {
        int r = 1 + rand() % 100;
        if (r < 20) {
            r = rand() % N;
            if (p[i] != NULL) {
                cout << "Free ! " << endl;
                myfree(p[i]);
                p[i] = mymalloc(r);
            }
        }
    }

    exit(0);
}

void combined() {
    allocate_many_times(10,5);
    allocate_many_times(10,48);
    allocate_many_times(10,100);
    allocate_many_times(10,246);
    allocate_many_times(10,490);
    allocate_many_times(10,1014);
    allocate_many_times(10,1948);
    allocate_many_times(10,3996);
}


int main(int argc, char** argv) {
    dokimi1();
//    dokimi2();
//    dokimi3();
//    dokimi4();
//    dokimi5();
//    dokimi6();
//    dokimi7();
//    dokimi8();
    
//    dokimiMB1();
//    dokimiMB2();
//    dokimiMB3();
//    dokimiMB4();
//    dokimiMB5();
//    dokimiMB6();
//    dokimiMB7();

//    dokimiFree1();
//    dokimiFree2();
//    dokimiFree3();
//    dokimiFree4();
//    dokimiFree5();
//    dokimiFree6();
//    dokimiFree7();
//    
//    
//    combined();
    
    
    
    
    
    
    
    
    return 0;
}