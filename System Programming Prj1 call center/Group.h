/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Group.h
 * Author: nikolaus
 *
 * Created on March 4, 2017, 10:56 PM
 */

#ifndef GROUP_H
#define GROUP_H

#include "Person.h"

#include <cstdio>

class Group {
public:
    Person * people;
    Group * nextGroup;
    
    int number_of_people;
    static int GROUP_CAPACITY;   
    
    Group();
};


#endif /* GROUP_H */

