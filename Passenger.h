//
// Created by Emre Demircioğlu on 10.11.2018.
//

#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H

#include <iostream>
using namespace std;

/*
 * flightTime indicates a passenger's flight time
 * arriveTime indicates a passenger's arriving time
 * lugWait indicates a passenger's luggage hand out time
 * secWait indicates a passenger's security check time
 * lug indicates a passenger has a luggage('L') or not('N')
 * vip indicates a passenger is a vip('V') or not('N')
 *
 */

class Passenger{
public:
    int flightTime;
    int arriveTime;
    int lugWait;
    int secWait;
    char lug;
    char vip;
    // constructor of Passenger
    Passenger(int arr, int flig, int lugw, int secw, char lug, char vip);
    // destructor of Passenger
    //this is a default destructor because this object has no new in it
    ~Passenger();

};
struct Passptrs{
    //comparison function for Passenger pointers
    bool operator()(const Passenger* first,const Passenger* second);

};

#endif //PROJECT2_PASSENGER_H
