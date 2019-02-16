//
// Created by Emre Demircioğlu on 10.11.2018.
//

#include "Passenger.h"


Passenger::Passenger(int arr, int flig, int lugw, int secw, char vip, char lug){
    this->arriveTime=arr;
    this->flightTime=flig;
    this->lugWait=lugw;
    this->secWait=secw;
    this->lug= lug;
    this->vip= vip;

}



Passenger::~Passenger() {

}

bool Passptrs::operator()(const Passenger* first,const Passenger* second){
    if(first->flightTime<second->flightTime){
        return false;
    }else if(first->flightTime==second->flightTime&&first->arriveTime<second->arriveTime){
        return false;
    }else{
        return true;
    }
}