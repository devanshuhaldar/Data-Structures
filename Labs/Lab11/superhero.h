#ifndef _superhero_h
#define _superhero_h
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;
class Superhero{
public:
    Superhero();
    Superhero(const string& supname_, const string& realname_, const string& power_);

    const string getName() const;
    const string getPower() const;
    bool operator==(const string& guess);
    bool operator!=(const string& guess);
    bool operator>(const Superhero& a);
    friend void operator-( Superhero& a);
    bool isGood();
    //friend ostream& operator<<(ostream& os, const Superhero& a);
private:
    string supname;
    string realname;
    string power;
    bool gob;
    
    const string getRealName() const;
};

ostream& operator<<(ostream& os, const Superhero& a);
void operator-(const Superhero& a);

#endif