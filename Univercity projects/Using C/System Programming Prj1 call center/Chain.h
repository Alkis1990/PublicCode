/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chain.h
 * Author: nikolaus
 *
 * Created on March 4, 2017, 10:57 PM
 */

#ifndef CHAIN_H
#define CHAIN_H

#include "Group.h"

#include <cstdio>

class Chain {
public:
    Group * group;
    Group * lastGroup;
    int number_of_people;
    int number_of_groups;
    
    void make();
    void destroy();
};

#endif /* CHAIN_H */

