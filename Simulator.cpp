//
// Created by Emre Demircioğlu on 10.11.2018.
//

#include "Simulator.h"

Simulator::Simulator(int size, vector<Passenger*> &a, vector<Counter*> &lugc, vector<Counter*> &secc) {
    this->size=size;
    this->people=&a;
    this->lugcount=&lugc;
    this->seccount=&secc;
}
Simulator::~Simulator() {
    people= nullptr;
    seccount= nullptr;
    lugcount=nullptr;

}


void Simulator::fillArriveQueue() {
    for (const auto &i : *this->people) {
        arriveQueue.push(i);
    }
}
int Simulator::nextEventTime() {
    long temp=250000001;
    if(!arriveQueue.empty()) {
        temp = arriveQueue.front()->arriveTime - time;
    }
    for (const auto&i:*this->lugcount){
        if(i->operationTime>0 && i->operationTime<temp){
            temp=i->operationTime;
        }
    }
    for (const auto&i:*this->seccount){
        if(i->operationTime>0 && i->operationTime<temp){
            temp=i->operationTime;
        }
    }
    return temp;
}
void Simulator::leaveLuggage(queue<Passenger*> &s) {
    vector<Passenger*> temp;

    for (auto&i:*this->lugcount){
        if(i->operationTime==0 ){

            if(this->vipPolicy&&i->curr->vip=='V'){
                this->averageWait+=(double(time-i->curr->arriveTime))/size;
                if(time-i->curr->flightTime>0){
                    missedPeople+=1;
                }
            }else{

                temp.push_back(i->curr);
            }

            i->cutLink();
        }
    }
    long temp1=0;
    long temp2=50001;
    for(int k=0;k<temp.size();++k) {

        for (auto &i:temp) {
            if (temp1 < i->arriveTime && temp2 > i->arriveTime) {
                temp2 = i->arriveTime;
            }
        }
        for (auto &i:temp) {
            if (temp2 == i->arriveTime) {
                temp1 = i->arriveTime;
                s.push(i);
                break;
            }
        }
        temp2=50001;
    }

}
void Simulator::leaveSecurity(queue<Passenger*> &s) {
    for (auto&i:*this->seccount){
        if(i->operationTime==0 ){

            this->averageWait+=(double(time-i->curr->arriveTime))/size;
            if(time-i->curr->flightTime>0){
                missedPeople+=1;
            }

            i->cutLink();
        }
    }
    linksc(s);
}

void Simulator::arrive(queue<Passenger*> &l,queue<Passenger*> &s) {
    if(arriveQueue.front()->lug=='L'){
        l.push(arriveQueue.front());
    }else if(onlineCI){

        if(vipPolicy&&arriveQueue.front()->vip=='V'){

        }else{
            s.push(arriveQueue.front());
        }

    }else{
        l.push(arriveQueue.front());
    }

    arriveQueue.pop();
}
void Simulator::linksc(queue<Passenger*> &s) {
    for (auto&i:*this->seccount){
        if(i->curr== nullptr&&!s.empty()){
            i->linkPassenger(*s.front(),s.front()->secWait);
            s.pop();
        }
    }
}
void Simulator::linklc(queue<Passenger*> &l) {
    for (auto&i:*this->lugcount){
        if (i->curr==nullptr&&!l.empty()){
            i->linkPassenger(*l.front(),l.front()->lugWait);
            l.pop();
        }
    }
}

void Simulator::case1() {
    time=0;
    missedPeople=0;
    averageWait=0;
    fillArriveQueue();
    queue<Passenger*> lugw;
    queue<Passenger*> secw;
    for(;time<250000001;){
        leaveSecurity(secw);
        leaveLuggage(secw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }
        linksc(secw);
        linklc(lugw);
        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }
    }

}

void Simulator::linklc(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &l) {
    for (auto&i:*this->lugcount){
        if (i->curr==nullptr&&!l.empty()){

            i->linkPassenger(*l.top(),l.top()->lugWait);
            l.pop();
        }
    }
}
void Simulator::linksc(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s) {
    for (auto&i:*this->seccount){
        if(i->curr== nullptr&&!s.empty()){

            i->linkPassenger(*s.top(),s.top()->secWait);
            s.pop();
        }
    }
}
void Simulator::leaveLuggage(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s) {

    for (auto &i:*this->lugcount) {
        if (i->operationTime == 0) {

            if (this->vipPolicy && i->curr->vip == 'V') {
                this->averageWait += double(time - i->curr->arriveTime) / size;
                if (time - i->curr->flightTime > 0) {
                    missedPeople += 1;
                }
            } else {

                s.push(i->curr);

            }

            i->cutLink();
        }
    }

}
void Simulator::leaveSecurity(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s) {
    for (auto&i:*this->seccount){
        if(i->operationTime==0 ){

            this->averageWait+=double(time-i->curr->arriveTime)/size;
            if(time-i->curr->flightTime>0){
                missedPeople+=1;
            }

            i->cutLink();
        }
    }
    linksc(s);
}
void Simulator::arrive(priority_queue<Passenger*,vector<Passenger*>,Passptrs> &l,priority_queue<Passenger*,vector<Passenger*>,Passptrs> &s) {
    if(arriveQueue.front()->lug=='L'){
        l.push(arriveQueue.front());
        linklc(l);
    }else if(onlineCI){

        if(vipPolicy&&arriveQueue.front()->vip=='V'){

        }else{
            s.push(arriveQueue.front());
            linksc(s);
        }

    }else{
        l.push(arriveQueue.front());
        linklc(l);
    }

    arriveQueue.pop();
}

void Simulator::case2() {
    time=0;
    missedPeople=0;
    averageWait=0;
    fillArriveQueue();

    priority_queue<Passenger*,vector<Passenger*>,Passptrs> lugw;
    priority_queue<Passenger*,vector<Passenger*>,Passptrs> secw;
    for(;time<250000001;){

        leaveSecurity(secw);

        leaveLuggage(secw);
        linksc(secw);

        linklc(lugw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }

        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }

    }

}
void Simulator::case3() {
    time=0;
    missedPeople=0;
    averageWait=0;
    vipPolicy=true;
    fillArriveQueue();
    queue<Passenger*> lugw;
    queue<Passenger*> secw;
    for(;time<250000001;){
        leaveSecurity(secw);
        leaveLuggage(secw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }
        linksc(secw);
        linklc(lugw);
        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }
    }
    vipPolicy=false;

}
void Simulator::case4() {
    time=0;
    missedPeople=0;
    averageWait=0;
    vipPolicy=true;
    fillArriveQueue();

    priority_queue<Passenger*,vector<Passenger*>,Passptrs> lugw;
    priority_queue<Passenger*,vector<Passenger*>,Passptrs> secw;
    for(;time<250000001;){

        leaveSecurity(secw);

        leaveLuggage(secw);
        linksc(secw);

        linklc(lugw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }



        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }

    }
    vipPolicy=false;
}
void Simulator::case5() {
    time=0;
    missedPeople=0;
    averageWait=0;
    onlineCI=true;
    fillArriveQueue();
    queue<Passenger*> lugw;
    queue<Passenger*> secw;
    for(;time<250000001;){
        leaveSecurity(secw);
        leaveLuggage(secw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }
        linksc(secw);
        linklc(lugw);
        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }
    }
    onlineCI=false;

}

void Simulator::case6() {
    time=0;
    missedPeople=0;
    averageWait=0;
    onlineCI=true;
    fillArriveQueue();

    priority_queue<Passenger*,vector<Passenger*>,Passptrs> lugw;
    priority_queue<Passenger*,vector<Passenger*>,Passptrs> secw;
    for(;time<250000001;){

        leaveSecurity(secw);

        leaveLuggage(secw);
        linksc(secw);

        linklc(lugw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }



        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }

    }
    onlineCI=false;

}
void Simulator::case7() {
    time=0;
    missedPeople=0;
    averageWait=0;
    onlineCI=true;
    vipPolicy=true;
    fillArriveQueue();
    queue<Passenger*> lugw;
    queue<Passenger*> secw;
    for(;time<250000001;){
        leaveSecurity(secw);
        leaveLuggage(secw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }
        linksc(secw);
        linklc(lugw);
        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }
    }
    onlineCI=false;
    vipPolicy=false;

}
void Simulator::case8() {
    time=0;
    missedPeople=0;
    averageWait=0;
    onlineCI=true;
    vipPolicy=true;
    fillArriveQueue();

    priority_queue<Passenger*,vector<Passenger*>,Passptrs> lugw;
    priority_queue<Passenger*,vector<Passenger*>,Passptrs> secw;
    for(;time<250000001;){

        leaveSecurity(secw);

        leaveLuggage(secw);
        linksc(secw);

        linklc(lugw);
        if(!arriveQueue.empty()&&time==arriveQueue.front()->arriveTime) {
            arrive(lugw, secw);
        }



        int t=nextEventTime();
        time+=t;
        for ( auto&i:*this->lugcount){
            i->operationTime-=t;
        }
        for ( auto&i:*this->seccount){
            i->operationTime-=t;
        }

    }
    onlineCI=false;
    vipPolicy=false;

}
