#include <string>
#include <list>
#include <cassert>
#include <algorithm>

#include "customer.h"

using namespace std;

Customer::Customer(){
    first = "";
    last = "";
}

Customer::Customer(const string& f, const string& l){
    first = f;
    last = l;
}

const string Customer::getFirst() const{//gets first name
    return first;
}

const string Customer::getLast() const{//gets last name
    return last;
}

void Customer::setFirst(const string& f){// sets first name
    first = f;
}

void Customer::setLast(const string& l){ //sets last name
    last = l;
}

bool operator<(const Customer& a, const Customer& b){ //for map function sorting
    if (a.getLast() < b.getLast()) return true;
    if (a.getLast() > b.getLast()) return false;
    if (a.getLast() == b.getLast()){
        if (a.getFirst() < b.getFirst()) 
            return true;
        else return false;
    }
    return false;
}

bool operator==(const Customer& a, const Customer& b){ //for find function comparison
    if (a.getFirst() == b.getFirst() && a.getLast() == b.getLast()) 
        return true;
    else return false;
}