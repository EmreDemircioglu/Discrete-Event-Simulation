#include <iostream>
#include <vector>
#include <fstream>
#include "Passenger.h"
#include "Counter.h"
#include "Simulator.h"
using namespace std;
int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }
    //reading from file starts

    ifstream infile(argv[1]);
    int i;
    infile >> i;
    int k;
    infile >> k;
    int j;
    infile >> j;
    vector<Passenger*> a;
    vector<Counter*> b;
    vector<Counter*> c;
    // reads from file creates passenger pointers and them to vector container a
    for(int t=0;t<i;++t){
        int temp;
        infile >> temp;

        int temp1;
        infile >> temp1;

        int temp2;
        infile >> temp2;

        int temp3;
        infile >> temp3;

        char temp4;
        infile >> temp4;

        char temp5;
        infile >> temp5;

        a.push_back(new Passenger(temp ,temp1,temp2,temp3,temp4,temp5));
    }
    // creates counter pointers for luggage counters and
    // adds them into vector container b
    for(int t=0;t<k;++t){
        b.push_back(new Counter());
    }
    // creates counter pointers for security counters and
    // adds them into vector container c
    for(int t=0;t<j;++t){
        c.push_back(new Counter());
    }

    //Creates simulator object
    Simulator att(i,a,b,c);


    //writing to file starts
    //executes the cases and writes the result into file
    ofstream myfile;
    att.case1();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;

    myfile.open (argv[2]);
    myfile<< att.averageWait << " " << att.missedPeople << endl;

    att.case2();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case3();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case4();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
  //  cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case5();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
 //   cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case6();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case7();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    att.case8();
    printf("%.4f",att.averageWait);
    cout<<endl;
    cout<<att.missedPeople<<endl;
   // cout<<att.averageWait<<endl;


    myfile << att.averageWait << " " << att.missedPeople << endl;

    myfile.close();
    //writing to file ends.

    //deletion of all new objects to prevent memory leak.
    for(auto &i:a){
        if(i){
            delete i;
        }
    }
    for(auto &i:b){
        if(i){
            delete i;
        }
    }
    for(auto &i:c){
        if(i){
            delete i;
        }
    }
    return 0;
}