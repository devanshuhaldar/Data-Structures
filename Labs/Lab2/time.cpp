#include <iostream>
#include "time.h"

Time::Time(){
    hour = 1;
    minute = 1;
    second = 1;
}

Time::Time(int aHour, int aMinute, int aSecond){
    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

int Time::getHour() const{
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::setHour(int h ){
    hour = h;
}

void Time::setMinute(int m){
    minute = m;
}

void Time::setSecond(int s){
    second = s;
}

void Time::PrintAMPM(){
    if (hour>12){
        hour = hour-12;
        std::cout<<hour<<':'<<minute<<':'<<second<<" pm"<<std::endl;
    }
    else{
        std::cout<<hour<<':'<<minute<<':'<<second<<" am"<<std::endl;
    }
}

bool IsEarlierThan(const Time& t1, const Time& t2){
    if (t1.getHour() < t2.getHour()){
        return true;
    }
    else if (t2.getHour() < t1.getHour()){
        return false;
    }
    else{//hours are equal
        if (t1.getMinute()<t2.getMinute()){
            return true;
        }
        else if (t2.getMinute()<t1.getMinute()){
            return false;
        }
        else {//minutes are equal
            if(t1.getSecond()<t2.getSecond()){
                return true;
            }
            else {//t2 second < t1 second
                return false;
            }
        }
    }
    return false; //same time
}
