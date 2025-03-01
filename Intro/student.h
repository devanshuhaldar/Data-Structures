#ifndef __student_h_
#define __student_h_
#include <iostream>
#include <string>
#include <vector>
#include "name.h"

class Student {
public:
  // ACCESSORS
  const std::string& first_name() const { return name_.first(); }
  const std::string& last_name() const { return name_.last(); }
  const std::string& id_number() const { return id_number_; }
  double hw_avg() const { return hw_avg_; }
  double test_avg() const { return test_avg_; }
  double final_avg() const { return final_avg_; }
  // MODIFIERS
  bool read(std::istream& in_str, unsigned int num_homeworks, unsigned int num_tests);
  void compute_averages(double hw_weight);
  // PRINT HELPER FUNCTIONS
  std::ostream& output_name(std::ostream& out_str) const;
  std::ostream& output_averages(std::ostream& out_str) const;
private:
  // REPRESENTATION
  Name name_;
  std::string last_name_;
  std::string id_number_;
  std::vector<int> hw_scores_;
  double hw_avg_;
  std::vector<int> test_scores_;
  double test_avg_;
  double final_avg_;
};

// COMPARISON FUNCTION FOR SORTING
bool less_names(const Student& stu1, const Student& stu2);
#endif



/*#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "player.h"
//Assumeing read creates a vector of players.
using namespace std;

//longest name
int long_name(vector<Player>& players){
    int primary = players[0].getNameSize();
    for (long unsigned int i = 0; i < players.size(); ++i){
        if (primary < players[i].getNameSize()){
            primary = players[i].getNameSize();
        }
    }
    return primary;
}

//helps alphabetize function .
/*bool alpha(Player a, Player b)
{
    return a.getLast()<b.getLast();
}*/
bool alpha(Player a, Player b)
{
    if (a.getLast()==b.getLast()){
        return a.getFirst()<b.getFirst();
    }else{
        return a.getLast()<b.getLast();
    }
    
}

//alphabetizes the names of bowlers.
void alphabetize(vector<Player>& players){
    sort(players.begin(),players.end(),alpha);
}



//Read input file and create vector of first,last,vector of scores. As one value.
vector<Player> read(ifstream& infile){
    vector<Player> v;
    string first_name;
    string last_name;
    int num;
   // Player player;
    //while((infile) >> first_name >> last_name){
    while(infile>>first_name>>last_name){
       // while(infile>> first_name >> last_name){};
        //infile >> first_name >> last_name;
        infile.clear();
        vector<int> nums; //reset scores
        while(infile>>num){
            nums.push_back(num);
        }
        Player player(first_name,last_name,nums);
        infile.clear();
        v.push_back(player);
    }
    return v;
}


void standard_stat(vector<vector<int>> totals, vector<Player>& players){
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
        for (int s = 0; s<(5-numl); ++s){
            line+=" ";
        }
        line+= to_string(total);
        cout<<line<<std::endl;
    }
}



//standard print of bowling scores,sums, winners.
void standard(vector<Player>& players){
    const int WIDTH = 64;
    int length = long_name(players);
    int total = length+WIDTH;
   // unsigned int sum = 0;
    vector<vector<int>> totals; // totals of all players
    string line;
    string top = ""; // print top of box
    for (int i = 0; i< total+2; ++i){
        top+= "-";
    }
    cout<<top<<std::endl;
    alphabetize(players);
   // int count;
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
        for (long unsigned int s= 0; s<scores.size()-1; s+=2){
            int flag = 0;
            if (scores[s] == 10){//strike
                if (count==9){
                    line+= " X";
                }else{
                    line+="   X";
                }
                s--;
                if (s< scores.size()-3){
                    sum+=(10+scores[s+3]+scores[s+2]);
                } else {
                    if (s == 18446744073709551615)
                     sum+=(10+scores[s+3]+scores[s+2]);
                     else sum+=10;
                }
                flag = 2;
            }
            else if (scores[s]+scores[s+1]==10){//spare
                if (scores[s] == 0){
                    line+=" - /";
                }else{
                    line+=" "+to_string(scores[s])+ " /";
                }
                if (s< scores.size()-2){
                    sum+=10+scores[s+2];
                } else {
                    sum+=10;
                }
                flag = 1;

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
                sum+=scores[s]+scores[s+1];
            }
            if (count == 9){//s == scores.size()-2){
               // line+="Testing";
                sums.push_back(sum);
                //cout<<"HELLOOOOO";
                if (flag==2){//strike
                    if (scores[s+2]==10){
                        line+= " X";
                        
                    } else {
                        line+= " "+to_string(scores[s+2]);

                    }
                    //cout<<"YO"<<scores[s+3]<<"YO";
                    if (scores[s+3]==10){
                        line+=" X |";
                        break;
                    } 
                    else {
                        line+=" "+to_string(scores[s+3])+" |";
                        break;
                    }

                   /* if(p!=0) {
                        line+= " "+to_string(scores[s+1])+" "+to_string(scores[s+2])+" |";
                        break;
                    }*/

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
               // sums.push_back(sum);

            }
            else {
                sums.push_back(sum);
                line+=" |";
                count+=1;
            }
        }


       /* for (long unsigned int s = 0; s< scores.size(); ++s){
           
           
            
           
           
              OLD WAY
            sum+= scores[s];
            if (scores[s]== 0){
                line+= " -";
                count+=1;
            }
            else  
            {
                line+= " "+to_string(scores[s]);
                count+=1;
            }                              
             if (s==scores.size()-1){  
                line+="   |";
                sums.push_back(sum);
                count=0;
            }else if (count == 2){
                
                line+= " |";
                sums.push_back(sum);
                count = 0;
            }
            


        }*/
        cout<<line<<std::endl;  //PRINTS FIRST LINE OF NAME AND ALL SCORES
        //Line 2 
        line = "";
        vector<int> array;
        array.push_back(sums[sums.size()-1]);
        array.push_back(p);
      //  int array[] = {sums[sums.size()-1],p};
        totals.push_back(array);//Adds sum of this player into a vector that contains all sums of all players. Also adding person number
       // int spacing=0;
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
        cout<<line<<std::endl;
        cout<<top<<std::endl;

    }

    //STATISTICS
    
    cout<<""<<std::endl;
    standard_stat(totals,players);

}






int main(int argc, char* argv[]){
    if (argc != 4){
        cerr<<"Error occured. Did not provide 4 arguments"<<std::endl; //error. Sent to error terminal.
        return 0;
    }

    ifstream infile(argv[1]);
    //ofstream outfile(argv[2]);
    string type = argv[3];
    
    vector<Player> players = read(infile);

    if (type == "standard"){
        cout<<"Standard:"<<std::endl;

        /*for (long unsigned int i = 0; i < players.size(); i++){
            cout<<players[i].getFirst()<<std::endl;
            cout<<players[i].getLast()<<std::endl;
            for (long unsigned int x = 0; x< players[i].getScores().size(); x++){
                cout<<players[i].getScores()[x]<<std::endl;
            }
        }*/

        standard(players);
    }
    else if (type == "custom") {
        cout<<"Custom"<<std::endl;
        //custom();
    }
    else cout<<"Error-> User inputed wrong type";
} 
