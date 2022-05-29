#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;


int main(){
    ofstream outfile;
    outfile.open("test");
    for (int i=0;i<200*1e6;i++){
        // generate random number
        int num = rand()%4;
        // print corresponding base
        switch (num){
            case 0:
                outfile << "A";
                break;
            case 1:
                outfile << "C";
                break;
            case 2:
                outfile << "G";
                break;
            case 3:
                outfile << "T";
                break;
        }
    }



}