#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>

#include "dvd.h"

using namespace std;

DVD::DVD(){
    movie ="";
    count = -1;
}

DVD::DVD(string movie_, int count_){
    movie = movie_;
    count = count_;
}

string DVD::getMovie(){
    return movie;
}

int DVD::getCount(){
    return count;
}

void DVD::setMovie(string name){
    movie = name;
}

void DVD::setCount(int num){
    count = num;
}

bool DVD::available(){ // returns true if copies of the movie is > 0
    if (count > 0){
        return true;
    }
    else return false;
}

void DVD::shipped(){
    if (count>0){
        count--;
    }
    else if (count == 0){
        cout<<"Unable to ship. No more copies available"<<std::endl;
    }
}