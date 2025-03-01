//main file for homework 2. prints out all values, board, stats etc.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "player.h"
using namespace std;

//longest name
int long_name(vector<Player>& players){ // finds longest name of all the players
    int primary = players[0].getNameSize();
    for (long unsigned int i = 0; i < players.size(); ++i){
        if (primary < players[i].getNameSize()){
            primary = players[i].getNameSize();
        }
    }
    return primary;
}
//helper for sort function below. 
bool alpha(Player a, Player b)
{
    if (a.getLast()==b.getLast()){
        return a.getFirst()<b.getFirst();
    }else{
        return a.getLast()<b.getLast();
    }
    
}

//alphabetizes the names of bowlers. using last name first. if last name == then goes to first name. 
void alphabetize(vector<Player>& players){
    sort(players.begin(),players.end(),alpha);
}


//Read input file and create vector of first,last,vector of scores. As one value.
vector<Player> read(ifstream& infile){
    vector<Player> v;
    string first_name;
    string last_name;
    int num;
    while(infile>>first_name>>last_name){
        infile.clear();//clears the file. 
        vector<int> nums; //reset scores
        while(infile>>num){
            nums.push_back(num);
        }
        Player player(first_name,last_name,nums); //creates player
        infile.clear();
        v.push_back(player);
    }
    return v;
}

//prints standard statistics--> the person with highest score on top, lowest on bottom. 
void standard_stat(vector<vector<int>> totals, vector<Player>& players,ofstream &outputfile){
    sort(totals.begin(), totals.end());
    string line;
    int length = long_name(players);
    for (long int t = totals.size()-1; t>=0; --t){ //Print out statistics. highest score at top
        line = "";
        int total = totals[t][0];
        int person = totals[t][1];
        line += players[person].getFirst()+" "+players[person].getLast();
        int numl = to_string(total).size();//length of number
        for (int r = 0; r<(length-players[person].getNameSize()); ++r){ //spacing for after name.
            line+= " ";
        }
        for (int s = 0; s<(5-numl); ++s){//deals with extra spacing to line up the values in correct positions.
            line+=" ";
        }
        line+= to_string(total);
        outputfile<<line<<std::endl;
    }
}

void custom_stat(vector<vector<int>> cus, vector<Player>& players,ofstream &outputfile){
    sort(cus.begin(), cus.end());
    string line;
    int length = long_name(players);
    for (long int t = cus.size()-1; t>=0; --t){ //Print out statistics. highest score at top
        line = "";
        int total = cus[t][0];
        int person = cus[t][1];
        line += players[person].getFirst()+" "+players[person].getLast();
        int numl = to_string(total).size();//length of number
        for (int r = 0; r<(length-players[person].getNameSize()); ++r){ //spacing for after name.
            line+= " ";
        }
        for (int s = 0; s<(5-numl); ++s){//deals with extra spacing to line up the values in correct positions.
            line+=" ";
        }
        line+= to_string(total);
        outputfile<<line<<std::endl;
    }
}

vector<vector<int>> custom_stat_helper(vector<Player>& players){
    vector<vector<int>> strikes; 
    for (long unsigned int i = 0; i < players.size(); ++i){
        int count = 0;
        vector<int> scores = players[i].getScores();
        vector<int> stats;
        for (long unsigned int s = 0; s<scores.size(); ++s){
            if (scores[s]==10){
                count+=1;
            }
        }
        stats.push_back(count);
        stats.push_back(i);
        strikes.push_back(stats);
    }
    return strikes;
}

void custom(vector<Player>& players,ofstream &outputfile){
    const int WIDTH = 64;
    int length = long_name(players);
    int total = length+WIDTH;
    vector<vector<int>> totals; // totals of all players
    string line;
    string top = ""; // print top of box
    for (int i = 0; i< total+2; ++i){
        top+= "-";
    }
    outputfile<<top<<std::endl;
    alphabetize(players);
    for (long unsigned int p = 0; p< players.size(); ++p){
        vector<int> scores = players[p].getScores();
        vector<int> sums; //resets to nothing when passing into for loop again. (Next player). If it doesnt work try .clear()
        int sum=0;
        line = "";
        line += "| " + players[p].getFirst()+" "+players[p].getLast();
        for (int r = 0; r<(length-players[p].getNameSize()); ++r){ //spacing for after name.
            line+= " ";
        }
        line+= " |";
        int count = 0;
        long int size = scores.size();
        for (long int s= 0; s<size-1; s+=2){
            int flag = 0;
            if (scores[s] == 10){//strike
                if (count==9){
                    line+= " X";
                }else{
                    line+="   X";
                }
                s--;
                if (s< size-3){ //in the last box.
                    sum+=(10+scores[s+3]+scores[s+2]);
                } else {
                    if (s == -1)
                     sum+=(10+scores[s+3]+scores[s+2]);
                     else sum+=10;
                }
                flag = 2; //flags that it is a strike for later on . 
            }
            else if (scores[s]+scores[s+1]==10){//spare
                if (scores[s] == 0){
                    line+=" - /";
                }else{
                    line+=" "+to_string(scores[s])+ " /";
                }
                if (s< size-2){ // in the last box. 
                    sum+=10+scores[s+2];
                } else {
                    sum+=10;
                }
                flag = 1; //flags if it is a spare. for later on . 

            }
            else {//Normal Nums
                if (scores[s]== 0){
                    line+= " -";
                }
                else {
                    line+= " " +to_string(scores[s]);
                }

                if (scores[s+1] == 0){
                    line+=" -";
                }
                else {
                    line+= " "+ to_string(scores[s+1]);
                }
                sum+=scores[s]+scores[s+1]; //adds to sum. 
            }
            if (count == 9){
                sums.push_back(sum);
                if (flag==2){//strike
                    if (scores[s+2]==10){
                        line+= " X";
                    } else {
                        line+= " "+to_string(scores[s+2]);
                    }
                    //outputfile<<"YO"<<scores[s+3]<<"YO";
                    if (scores[s+3]==10){
                        line+=" X |";
                        break;
                    } 
                    else {
                        line+=" "+to_string(scores[s+3])+" |";
                        break;
                    }
                } else if (flag==1){//spare
                    if (scores[s+1]){
                        line+=" X |";
                        break;
                    }else{
                        line+= " "+to_string(scores[s+1])+" |";
                        break;
                    }
                } 
                else
                {
                    line+= "   |";
                }
            }
            else {
                sums.push_back(sum);
                line+=" |";
                count+=1;
            }
        }
        //NEXT SEQUENCE IS PRINTING SECOND LINE AFTER EACH PLAYERS.
        outputfile<<line<<std::endl;  //PRINTS FIRST LINE OF NAME AND ALL SCORES
        //Line 2 
        line = "";
        vector<int> array;
        array.push_back(sums[sums.size()-1]);
        array.push_back(p);
        totals.push_back(array);//Adds sum of this player into a vector that contains all sums of all players. Also adding person number
        line+= "| ";
        for (int y = 0; y<length; ++y){
            line+= " ";
        }
        line+= " |";
        for (long unsigned int x = 0; x< sums.size(); ++x){
            int spacing = 0;
            if (x==sums.size()-1){
                spacing = 6;
            }
            string value = to_string(sums[x]);
            if (spacing == 0){
                for (long unsigned int h = 0; h< (4-value.size()); ++h){
                    line+= " ";
                }
            }
            else if(spacing == 6){
                for (long unsigned int h = 0; h< (spacing-value.size()); ++h){
                    line+= " ";
                }
            }
            line+= value+" |";
        }
        outputfile<<line<<std::endl;
        outputfile<<top<<std::endl;
    }

    //STATISTICS
    outputfile<<""<<std::endl;
    custom_stat(custom_stat_helper(players),players,outputfile);
}

//standard print of bowling scores,sums, winners.
void standard(vector<Player>& players,ofstream &outputfile){
    const int WIDTH = 64;
    int length = long_name(players);
    int total = length+WIDTH;
    vector<vector<int>> totals; // totals of all players
    string line;
    string top = ""; // print top of box
    for (int i = 0; i< total+2; ++i){
        top+= "-";
    }
    outputfile<<top<<std::endl;
    alphabetize(players);
    for (long unsigned int p = 0; p< players.size(); ++p){
        vector<int> scores = players[p].getScores();
        vector<int> sums; //resets to nothing when passing into for loop again. (Next player). If it doesnt work try .clear()
        int sum=0;
        line = "";
        line += "| " + players[p].getFirst()+" "+players[p].getLast();
        for (int r = 0; r<(length-players[p].getNameSize()); ++r){ //spacing for after name.
            line+= " ";
        }
        line+= " |";
        int count = 0;
        long int size = scores.size();
        for (long  int s= 0; s<size-1; s+=2){
            int flag = 0;
            if (scores[s] == 10){//strike
                if (count==9){
                    line+= " X";
                }else{
                    line+="   X";
                }
                s--;
                if (s< size-3){ //in the last box.
                    sum+=(10+scores[s+3]+scores[s+2]);
                } else {
                    if (s ==-1)
                     sum+=(10+scores[s+3]+scores[s+2]);
                     else sum+=10;
                }
                flag = 2; //flags that it is a strike for later on . 
            }
            else if (scores[s]+scores[s+1]==10){//spare
                if (scores[s] == 0){
                    line+=" - /";
                }else{
                    line+=" "+to_string(scores[s])+ " /";
                }
                if (s<size-2){ // in the last box. 
                    sum+=10+scores[s+2];
                } else {
                    sum+=10;
                }
                flag = 1; //flags if it is a spare. for later on . 

            }
            else {//Normal Nums
                if (scores[s]== 0){
                    line+= " -";
                }
                else {
                    line+= " " +to_string(scores[s]);
                }

                if (scores[s+1] == 0){
                    line+=" -";
                }
                else {
                    line+= " "+ to_string(scores[s+1]);
                }
                sum+=scores[s]+scores[s+1]; //adds to sum. 
            }
            if (count == 9){
                sums.push_back(sum);
                if (flag==2){//strike
                    if (scores[s+2]==10){
                        line+= " X";
                    } else {
                        line+= " "+to_string(scores[s+2]);
                    }
                    //outputfile<<"YO"<<scores[s+3]<<"YO";
                    if (scores[s+3]==10){
                        line+=" X |";
                        break;
                    } 
                    else {
                        line+=" "+to_string(scores[s+3])+" |";
                        break;
                    }
                } else if (flag==1){//spare
                    if (scores[s+1]){
                        line+=" X |";
                        break;
                    }else{
                        line+= " "+to_string(scores[s+1])+" |";
                        break;
                    }
                } 
                else
                {
                    line+= "   |";
                }
            }
            else {
                sums.push_back(sum);
                line+=" |";
                count+=1;
            }
        }
        //NEXT SEQUENCE IS PRINTING SECOND LINE AFTER EACH PLAYERS.
        outputfile<<line<<std::endl;  //PRINTS FIRST LINE OF NAME AND ALL SCORES
        //Line 2 
        line = "";
        vector<int> array;
        array.push_back(sums[sums.size()-1]);
        array.push_back(p);
        totals.push_back(array);//Adds sum of this player into a vector that contains all sums of all players. Also adding person number
        line+= "| ";
        for (int y = 0; y<length; ++y){
            line+= " ";
        }
        line+= " |";
        for (long unsigned int x = 0; x< sums.size(); ++x){
            int spacing = 0;
            if (x==sums.size()-1){
                spacing = 6;
            }
            string value = to_string(sums[x]);
            if (spacing == 0){
                for (long unsigned int h = 0; h< (4-value.size()); ++h){
                    line+= " ";
                }
            }
            else if(spacing == 6){
                for (long unsigned int h = 0; h< (spacing-value.size()); ++h){
                    line+= " ";
                }
            }
            line+= value+" |";
        }
        outputfile<<line<<std::endl;
        outputfile<<top<<std::endl;
    }

    //STATISTICS
    outputfile<<""<<std::endl;
    standard_stat(totals,players,outputfile);

}

int main(int argc, char* argv[]){
    if (argc != 4){
        cerr<<"Error occured. Did not provide 4 arguments"<<std::endl; //error. Sent to error terminal.
        return 0;
    }
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    string type = argv[3];
    vector<Player> players = read(infile);
    if (type == "standard"){
        standard(players,outfile);
    }
    else if (type == "custom") {
        custom(players,outfile);
        
    }
    else cerr<<"Error-> User inputed wrong type";
}