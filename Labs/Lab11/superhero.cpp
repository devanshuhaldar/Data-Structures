#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

#include "superhero.h"
using namespace std;
Superhero::Superhero(){
    supname = "";
    realname = "";
    power = "";
    gob = true;
}

Superhero::Superhero(const string& supname_, const string& realname_, const string& power_){
    supname = supname_;
    realname = realname_;
    power = power_;
    gob = true;
}

const string Superhero::getName() const{
    return supname;
}

const string Superhero::getPower() const{
    return power;
}

const string Superhero::getRealName() const{
    return realname;
}

bool Superhero::isGood(){
    return gob;
}

bool Superhero::operator==(const string& guess){
    if (this->getRealName() == guess)
        return true;
    else return false;
}

bool Superhero::operator!=(const string& guess){
    if (this->getRealName() == guess)
        return false;
    else return true;
}

bool Superhero::operator>(const Superhero& a){
    if (this->getPower() == "Fire" &&  a.getPower()== "Wood"){
        return true;
    }else if(this->getPower() == "Wood" && a.getPower() == "Water")
        return true;
    else if(this->getPower() == "Water" && a.getPower() == "Fire")
        return true;
    else return false;
}

ostream& operator<<(ostream& os, const Superhero& a){
    cout<<"Superhero "<<a.getName()<<" has power "<<a.getPower()<<std::endl;
}

void operator-(Superhero& a){
    if (a.gob == false)
        a.gob = true;
    else if (a.gob == true)
        a.gob = false;
}