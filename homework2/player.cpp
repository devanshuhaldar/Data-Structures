//player.cpp file containing functions for main.cpp
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#include "player.h"

using namespace std;

Player::Player(){
    first="";
    last="";
}

Player::Player(string& first_, string& last_, vector<int>& scores_){
    first = first_;
    last = last_;
    scores= scores_;
}

string Player::getFirst() {
  return first;
}

string Player::getLast() {
  return last;
}
	
vector<int> Player::getScores() {
  return scores;
}

int Player::getNameSize(){
    return first.size()+last.size()+1;//+1 for space.
}

int Player::getSum(){ //sum off all scores
    int sum = 0;
    for (long unsigned int i = 0; i<scores.size(); ++i){  
        sum+= scores[i];
    }
    return sum;
}

void Player::setFirst(string f) {
  first = f;
}

void Player::setLast(string l) {
  last = l;
}

void Player::setScores(vector<int> s) {
  scores = s; 
}

