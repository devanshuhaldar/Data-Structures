#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "Pref.h"

using namespace std;

Pref::Pref(){
    name = "";
}

Pref::Pref(string& name_, list<string>& movies_){
    movies = movies_;
    name = name_;
}

string Pref::getName(){
    return name;
}

list<string> Pref::getMovies(){
    return movies;
}

void Pref::setName(string name_){
    name = name_;
}

void Pref::setMovies(list<string> movies_){
    movies= movies_;
}