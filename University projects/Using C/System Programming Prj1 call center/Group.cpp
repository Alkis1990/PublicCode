/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Group.h"

int Group::GROUP_CAPACITY = 10;
 
Group::Group() {
    people = new Person[Group::GROUP_CAPACITY];
    nextGroup = NULL;
    number_of_people = 0;
}