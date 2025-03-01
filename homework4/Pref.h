//pref.h
#ifndef _Pref_h
#define _Pref_h
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

using namespace std;

class Pref{
public:
    Pref();
    Pref(string& name_, list<string>& movies_);

    list<string> getMovies();
    string getName();

    void setName(string name_); 
    void setMovies(list<string> movies_);

private:
    string name;
    list<string> movies;

};
#endif