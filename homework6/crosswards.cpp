#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

//makes a grid of same row and same column size as the grid passing in. And creates/returns a new grid of bools instead of chars. All starting at true.
vector<vector<bool> > make_bool_grid(const vector<vector<char> >& grid){
    vector<vector<bool> > print;
    for (int i = 0; i < grid.size(); i++){ 
        vector<bool> temp;
        for (int j = 0; j<grid[i].size(); j++){
            temp.push_back(true);
        }
        print.push_back(temp);
    }
    return print;
}

//prints the board. takes the changes bools from the print and knows what chars to print on the grid.
void print_board(vector<vector<char> > grid, vector<vector<bool> > print){//might remove & on grid 
    for (int i = 0; i < print.size(); i++){
        for (int j = 0; j < print[i].size(); j++){
            if (print[i][j]== true){
                grid[i][j]= '#';
            }
            cout<<grid[i][j];
        }
        cout<<std::endl;
    }
}

//creates the grid given a copy grid and print. This is just a copy grid with the #. But returns instead of prints. 
//I need this to check the validity.
vector<vector<char> > create_grid(vector<vector<char> >& grid, vector<vector< bool> >& print){
    vector<vector<char> > ans = grid;
    for (int i = 0; i<print.size(); i++){
        for ( int j = 0; j<print[i].size();j++){
            if (print[i][j]==true){
                ans[i][j]= '#';
            }
        }
    }
    return ans;
}

//Checks if the grid is valid or not. 
//Works for the case if you input a word does it create more words? that are not in the constraints?
//Counts number of words in grids and checks the number of constraints. They should match to be valid.
bool validity(vector<vector<char> > grid, vector<int> constraints, vector<string> dictionary,vector<vector<bool> > print ){
    int num_cons = constraints.size();
    string v_line; 
    string h_line;
    int num_words = 0;
    //HORIZONTAL
    //Checks through every row and column all the possible words.
    for (int row = 0; row < grid.size(); row++){
        for (int col = 0; col < grid[row].size(); col++){
            h_line = "";
            for (int cross = col; cross<grid[row].size(); cross++){
                h_line += grid[row][cross];
                for( int word = 0; word< dictionary.size(); word++){
                    if (h_line == dictionary[word]){//find word add to the counter.
                        num_words++;
                    }
                }

            }
        }
    }
    //Goes through every column and row. And checks all the words that are vertical.
    for (int row = 0; row < grid[0].size(); row++){
        for (int col = 0; col < grid.size(); col++){
            v_line = "";
            for (int cross = col; cross<grid.size(); cross++){
                v_line += grid[cross][row];
                for (int word = 0; word<dictionary.size(); word++ ){
                    if (v_line == dictionary[word])//if i find a word I add it to the counter. 
                        num_words++;
                }
            }
        }
    }
    if (num_words == num_cons) //checks if the number of words equals the number of constraints meaning it is valid.
        return true;
    else return false;
}

//Creates a vector<string> that is just all the words in the dictionary file inputed.
vector<string> make_words(ifstream& dictionary_file, ofstream& output){
    vector<string> words; 
    string word;
    while (dictionary_file >> word){
        words.push_back(word);
    }
    return words;
}

//Creates the grid. Inputed from the file. 
vector<vector<char> > make_grid(ifstream& grid_file, ofstream& output){
    grid_file.clear();
    vector<char> temp;
    vector<vector<char> > puzzle;
    string line; 
    while (grid_file >> line){
        if (line[0] != '!' && line[0] != '+'){
            for (int i = 0; i < line.size(); i++){
                temp.push_back(line[i]);
            }
            puzzle.push_back(temp);
            temp.clear();
        }
    }
    return puzzle;
}

//Creates a vector of ints that contains all of the constraints from the file inputed.
vector<int> make_constraints(ifstream& grid_file, ofstream& output){ 
    char c; 
    int x;
    vector<int> constraints;
    while (grid_file >> c){
        if (c == '+'){
            while (grid_file >> x){
                constraints.push_back(x);
            }
        }
    }
    grid_file.clear();
    return constraints;
}

//Prints the grids. Depends on number of solutions on how many times it gets printed.
void print_solve(vector<vector<string> >& words, vector<vector<char> >& grid, int num){
    string line; //Vector words contains the words that need to be printed for each grid.
    cout<<"Number of solution(s): "<<num<<std::endl; 
    for (int word = 0; word< num; word++){//How many times do I need to print the board
        vector<string> letters = words[word];
        vector<vector<bool> > print = make_bool_grid(grid);
        for (int row = 0; row<grid.size(); row++){ //goes through each row and col
            for (int col = 0; col< grid[row].size(); col++){
                line = "";
                vector<int> pos; //keeps track of the positions of the each character in the line.
                for (int cross = col; cross<grid[row].size(); cross++){ //this allows me to check through each possible word in the row/col.
                    line+= grid[row][cross]; //add char to line
                    pos.push_back(cross); // add position.
                    for (int i = 0; i<letters.size(); i++){  // go through words vector. 
                        if (line == letters[i]){
                            vector<string>::iterator str= find(letters.begin(), letters.end(), line);
                            letters.erase(str);
                            for (int t = 0; t< pos.size(); t++){
                                print[row][pos[t]] = false; // change these to false so it allows me to print the grid correctly.
                            }
                        }
                    }
                }
            }
        }
        //Vertical work.
        //SAME PROCESS AS ABOVE JUST VERTICAL.
        for (int row = 0; row<grid[0].size(); row++){
            for (int col = 0; col< grid.size(); col++){
                line = "";
                vector<int> pos;
                for (int cross = col; cross<grid.size(); cross++){
                    line+= grid[cross][row];
                    pos.push_back(cross);
                    for (int i = 0; i<letters.size(); i++){
                        if (line == letters[i]){
                            vector<string>::iterator str= find(letters.begin(), letters.end(), line);
                            letters.erase(str);
                            for (int t = 0; t< pos.size(); t++){
                                print[pos[t]][row]= false;
                            }
                        }
                    }
                }
            }
        }
        cout<<"Board:"<<std::endl;
        print_board(grid,print);//print board.
    }
}

//This is my recursive function
//Inputs the grid, dictionary words, constraints, words which is going to contain a vector of words for each possible grid solution
//Extra_words is going to contain words that are in the extra solutions. Like eke, sis, ski. (FOr blackout)
//restrictions is a copy of constraints but is inputed to help me with my initial condition. The first grid. Is going to work differently than the rest of the solutions.
vector<vector<string> > solve(vector<vector<char> > grid, vector<string>& dictionary, vector<int> constraints, vector<vector<string> >& words, vector<string>& extra_words, vector<int>& restrictions){
    string line;
    vector<int> cons = constraints; // copy of constraints. need to remove so i dont want to change constraints.
    vector<vector<bool> > print = make_bool_grid(grid); // create a print grid.
    if (extra_words.size() == 0 && restrictions.size() == 0 ){ // BASE CASE. Done with both solutions. Extra and initial is completed.
        return words;
    }
    else if (restrictions.size() != 0){ //First initial solution. First grid. Where I use te restrictions vector constraints.
        vector<string> sentence;  // going to containn all the words for the solution.
        vector<string> d = dictionary; //copy dictionary to check for same word in grid.
        for (int row = 0; row<grid.size(); row++){ // horizontal
            for (int col = 0; col <grid[row].size(); col++){
                line = "";
                vector<int> pos; //same explanation as above in the solve function.
                for (int cross = col; cross< grid[row].size(); cross++){
                    if (grid[row][cross]!='#') 
                        line+= grid[row][cross];
                    pos.push_back(cross);
                    for (int word = 0; word < d.size(); word++){
                        if (d[word] == line){ // horizontal line
                            vector<int>::iterator itr = find(restrictions.begin(), restrictions.end(), line.size());// if in restrictions. else add to extra words.
                            vector<string>::iterator str = find(d.begin(),d.end(), line);
                            d.erase(str);
                            if (itr!=restrictions.end()){
                                for (int t = 0; t< pos.size(); t++){
                                    print[row][pos[t]]= false;
                                }
                                sentence.push_back(line);
                                restrictions.erase(itr);
                            }else{
                                extra_words.push_back(line);
                            } //DO A COPY DICTIONARY WILL HELP WITH BLACKOUT 3
                        }
                    }
                }
            }
        }
        //Same as above just the vertical version.
        for (int row = 0; row<grid[0].size(); row++){ 
            for (int col = 0; col < grid.size() ; col++){//vertical
                line = "";
                vector<int> pos;
                for (int cross = col; cross< grid.size(); cross++){
                    line+= grid[cross][row];
                    pos.push_back(cross);
                    for (int word = 0; word < d.size(); word++){
                        if (d[word] == line){
                            vector<int>::iterator itr = find(restrictions.begin(), restrictions.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(), line);
                            d.erase(str);
                            if (itr!=restrictions.end()){  
                                for (int t= 0; t<pos.size();t++){
                                    print[pos[t]][row] = false;
                                }            
                                sentence.push_back(line);
                                restrictions.erase(itr);    
                            }else{
                                extra_words.push_back(line);
                            }
                        }
                    }
                }
            }
        } 
        words.push_back(sentence);
        if (sentence.size() == constraints.size()){
            vector<vector<char> > ans = create_grid(grid,print);
            bool question = validity(ans,constraints,dictionary,print);
            if (question == false){ //checks validity.
                extra_words.clear(); // since it is initial i need to clear everything before returning making sure it is 0. call the funciton .
                restrictions.clear();
                words.clear();
                return words;
            }else{
                solve(grid, dictionary, constraints, words, extra_words, restrictions); //else its valid call function.
            }
        }else {
            restrictions.clear();
            words.clear();
            extra_words.clear();
            return words;
        }
    }
    else if (extra_words.size() != 0){ //rest of solutions
        vector<string> sentence;
        string line;
        vector<vector<bool> > print = make_bool_grid(grid);
        vector<string> d = dictionary;
        for (int row = 0; row<grid.size(); row++){ //Horizontal
            for (int col = 0; col<grid[row].size(); col++){
                line = "";
                vector<int> pos;
                for (int cross = col; cross<grid[row].size(); cross++){
                    line+= grid[row][cross];
                    pos.push_back(cross);
                    for (int word = 0; word<d.size(); word++){
                        vector<string>::iterator found = find(extra_words.begin(), extra_words.end(), line);
                        if (d[word]==line && found!=extra_words.end()){ //Need to make sure I find this word in the extra words vector.
                            vector<int>::iterator itr = find(cons.begin(), cons.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),line);
                            d.erase(str); // erase from dicitonary. DEALS WITH COPIED WORDS IN GRID.
                            if (itr!=cons.end()){
                                for (int t = 0; t<pos.size(); t++){
                                    print[row][pos[t]] = false;
                                }
                                cons.erase(itr);
                                extra_words.erase(found);
                                sentence.push_back(line);
                            }
                        }else if (d[word] == line && extra_words.size()==0){  //It is a word that needs to be added but is not in extra words. SO like blues flees in blackout
                            vector<int>::iterator itr = find(cons.begin(),cons.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),line);
                            d.erase(str);
                            if (itr!=cons.end()){
                                for (int t= 0 ; t< pos.size(); t++){
                                    print[row][pos[t]] = false;
                                }
                                sentence.push_back(line);
                                cons.erase(itr);
                            }
                        }
                    }
                }
            }
        }
        //SAME AS ABOVE BUT VERTICAL VERSION
        for (int row = 0; row<grid[0].size();row++){ 
            for (int col = 0; col < grid.size(); col++){//vertical
                vector<int> pos;
                line = "";
                for (int cross = col; cross< grid.size(); cross++){
                    line += grid[cross][row];
                    pos.push_back(cross);
                    for (int word = 0; word< d.size(); word++){
                        vector<string>::iterator found = find(extra_words.begin(), extra_words.end(), line);
                        if (d[word] == line && found!=extra_words.end()){
                            vector<int>::iterator itr = find(cons.begin(), cons.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),line);
                            d.erase(str);
                            if (itr!= cons.end()){
                                for ( int t = 0; t<pos.size(); t++){
                                    print[pos[t]][row] = false;
                                }
                                cons.erase(itr);
                                extra_words.erase(found);
                                sentence.push_back(line);
                                
                            }
                        }else if (d[word] == line && extra_words.end()==found){
                            vector<int>::iterator itr = find(cons.begin(), cons.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),line);
                            d.erase(str);
                            if (itr!=cons.end()){
                                for (int t = 0; t < pos.size(); t++){
                                    print[pos[t]][row] = false;
                                }
                                sentence.push_back(line);
                                cons.erase(itr);
                            }
                        }
                    }
                }
            }
        }
        vector<vector<char> > ans = create_grid(grid,print);
        bool question = validity(ans,constraints,dictionary,print);
        if (question == false){ //check validity. then call function
            solve(grid,dictionary,constraints,words,extra_words,restrictions);
        }else{
            words.push_back(sentence);
            solve(grid,dictionary,constraints,words,extra_words,restrictions);
        }
    }
    return words;
}

int main(int argc, char* argv[]){
    if (argc!=5){
        cerr<<"ERROR: 5 arguments not used"<<std::endl;
        return 0;
    }
    ifstream dictionary_file(argv[1]);
    ifstream grid_file(argv[2]);
    ofstream output(argv[4]);

    vector<string> dictionary = make_words(dictionary_file, output);
    vector<int> constraints = make_constraints(grid_file, output);
    vector<vector<char> > grid = make_grid(grid_file, output);
    
    vector<string> extra_words;
    vector<int> restrictions = constraints;
    vector<vector<string> > words;
    vector<vector<string> > sol = solve(grid, dictionary, constraints, words, extra_words, restrictions);
    /*
    TEST CASES 

    Puzzle 1:
        Tests for no hashtags if whole puzzle filled.

        Dictionary File      = puzzle1_dict.txt
        Grid/Constraint File = puzzle1.txt

    Puzzle 2:
        Tests for all corner cases. Word in each corner.
        
        Dictionary File      = puzzle2._dict.txt
        Grid/Constraint File = puzzle2.txt
    */
    int a = strcmp(argv[3],"all_solutions");
    int b = strcmp(argv[3],"one_solution");
    if (b == 0){
        if (sol.size()==0){
            cout<<"Number of solution(s): 0"<<std::endl;
        }
        else print_solve(sol,grid,1);
    }else if (a == 0){ 
        if (sol.size()==0)
            cout<<"Number of solution(s): 0"<<std::endl;        
        else print_solve(sol,grid,sol.size());
    }
}