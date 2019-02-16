//
// Created by Emre Demircioğlu on 10.11.2018.
//

#ifndef PROJECT2_COUNTER_H
#define PROJECT2_COUNTER_H

#include "Passenger.h"
/*
 * operationTime indicates the time counter will be occupied
 * curr pointer indicates the passenger who occupied this counter
 */
class Counter {
public:
    //default constructor
    Counter();
    int operationTime=-1;
    Passenger* curr= nullptr;
    //default destructor
    ~Counter();
    // links a passenger to a counter so this counter becomes occupied
    void linkPassenger( Passenger& a,int k);
    // cuts the link of the passenger so this counter becomes available
    void cutLink();
};


#endif //PROJECT2_COUNTER_H
