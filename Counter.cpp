//
// Created by Emre Demircioğlu on 10.11.2018.
//

#include "Counter.h"
Counter::Counter() {}
void Counter::linkPassenger( Passenger &a,int k) {
    this->curr=&a;
    this->operationTime=k;

}
void Counter::cutLink() {
    this->curr= nullptr;

}
Counter::~Counter() {

    if(curr){
        delete curr;
    }
}