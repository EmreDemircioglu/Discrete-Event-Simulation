//
// Created by Emre Demircioğlu on 10.11.2018.
//

#ifndef PROJECT2_SIMULATOR_H
#define PROJECT2_SIMULATOR_H



#include <iostream>
using namespace std;
#include <vector>
#include "Passenger.h"
#include <queue>
#include "Counter.h"
#include <list>
/*
 * people vector pointer that points the vector which is filled with Passenger pointers
 * lugcount vector pointer that points the vector which is filled with luggage Counter pointers
 * seccount vector pointer that points the vector which is filled with security Counter pointers
 * arriveQueue FIFO queue which will hold the passenger pointers in arriving order
 * size (int) number of passenger
 * time (int) time used in cases
 * missedPeople (long) number of people that missed their flight
 * averageWait (double) number of average waiting time
 * vipPolicy indicates there is vip policy or not
 * onlineCI indicates there is online check in policy or not
 */
class Simulator {
public:
    /*
     * constructor of Simulator
     * links people to passengers
     * links lugcount pointer to lugc
     * links seccount pointer to secc
     */
    Simulator(int size,vector<Passenger*>& passengers,vector<Counter*> &lugc,vector<Counter*> &secc);
    //destructor of Simulator
    //this is a default destructor because this object has no new in it and
    //pointers in this class points already existing objects.
    ~Simulator();
    vector<Passenger*>* people;
    vector<Counter*>* lugcount;
    vector<Counter*>* seccount;
    queue<Passenger*> arriveQueue;
    int size;
    long time=0;
    int missedPeople=0;
    double averageWait=0;

    //implementation of case1
    void case1();
    //implementation of case2
    void case2();
    //implementation of case3
    void case3();
    //implementation of case4
    void case4();
    //implementation of case5
    void case5();
    //implementation of case6
    void case6();
    //implementation of case7
    void case7();
    //implementation of case8
    void case8();
private:
    bool vipPolicy=false;
    bool onlineCI=false;

    //links passengers to available luggage counters for first in first out
    void linklc(queue<Passenger*> &l);

    //links passengers to available luggage counters for first fly first out
    void linklc(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &l);

    //links passengers to available security counters for first in first out
    void linksc(queue<Passenger*> &s);

    //links passengers to available security counters for first fly first out
    void linksc(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s);

    //takes passenger from people then pushes them into arriveQueue
    void fillArriveQueue();

    //calculates and returns when will be a next event
    int nextEventTime();

    //cuts the links of luggage counters then sends them to either FIFO security queue or plane
    void leaveLuggage(queue<Passenger*> &s);

    //cuts the links of luggage counters then sends them to either FFFO security queue or plane
    void leaveLuggage(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s);

    //cuts the links of security counters then sends them to plane.
    // After this calls linksc function for with parameter FIFO security queue
    void leaveSecurity(queue<Passenger*> &s);

    //cuts the links of security counters then sends them to plane.
    // After this calls linksc function for with parameter FFFO security queue
    void leaveSecurity(priority_queue<Passenger*, vector<Passenger*>,Passptrs> &s);

    //takes arriving passenger and
    //either pushes it to FIFO luggage queue
    //or links it to a luggage counter
    //or pushes it to FIFO security queue
    //or links it to a security counter
    //or sends it to the plane
    void arrive(queue<Passenger*> &l,queue<Passenger*> &s);

    //takes arriving passenger and
    //either pushes it to FFFO luggage queue
    //or links it to a luggage counter
    //or pushes it to FFFO security queue
    //or links it to a security counter
    //or sends it to the plane
    void arrive(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &l,priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s);
};


#endif //PROJECT2_SIMULATOR_H
