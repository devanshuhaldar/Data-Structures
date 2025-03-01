
#ifndef _dvd_h
#define _dvd_h
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

using namespace std;

class DVD{
public:
    DVD();
    DVD(string movie_, int count_);

    string getMovie();
    int getCount();

    void setMovie(string name);
    void setCount(int num);
    void shipped();
    
    bool available();
    

private:
    string movie;
    int count;
};
#endif
