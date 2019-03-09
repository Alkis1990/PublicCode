/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "findchain.h"


unsigned int findchain(unsigned char * string) {
    unsigned char sum = 0;

    for (unsigned char *s = string; *s; s++) {
        sum ^= *s;
    }
    return (sum & 127);
}
