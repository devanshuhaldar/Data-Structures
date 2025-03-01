//Header file for player.cpp and main.cpp homework2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player{
public:
    Player();
    Player(string& first_, string& last_, vector<int>& scores_);

    string getFirst();
    string getLast(); //get first and last names and vector of scores
    vector<int> getScores();
    int getSum(); //gets sum of all scores
    int getNameSize(); //gets name size 

    void setFirst(string aFirst);
    void setLast(string aLast);
    void setScores(vector<int> aScores);


private:
    string first;
    string last;
    vector<int> scores;
};