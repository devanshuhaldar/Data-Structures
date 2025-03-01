
#ifndef _cus_h
#define _cus_h
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

//#include "Pref.h"

using namespace std;

class Cus{
public:
    Cus();
    Cus(string name_, list<string> films_, list<string> preferences_);

    string getName();
    list<string> getFilms();
    list<string> get_preferences();

    void setPreferences(list<string> preferences_);
    void setName(string name_);
    void setFilms(list<string> films_);

    void receives(string movie); //?

    bool has_max_num_movies();
    bool preference_list_empty(list<string> movie_);
private:
    string name;
    list<string> films;
    list<string> prefs;
    
};
#endif
