
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "cus.h"

using namespace std;

Cus::Cus(){
    name = "";
}

Cus::Cus(string n, list<string> f, list<string> p){
    name = n;
    films = f;
    prefs = p;
}

string Cus::getName(){
    return name;
}

list<string> Cus::getFilms(){
    return films;
}

void Cus::setName(string n){
    name = n;
}

void Cus::setFilms(list<string> films_){
    films = films_;
}

bool Cus::has_max_num_movies(){
    if (films.size()==3){
        return true;
    } else return false;
}

bool Cus::preference_list_empty(list<string> preferences){
    if (preferences.size()==0){
        return true;
    } else return false;
}

list<string> Cus::get_preferences(){
    return prefs;
}

void Cus::setPreferences(list<string> p){
    prefs = p;
}

void Cus::receives(string movie){
    for (list<string>::iterator i = prefs.begin(); i !=prefs.end() ; i++){
        if (*i == movie){
            films.push_back(movie);
            prefs.erase(i);
            break;
        }
    }
}