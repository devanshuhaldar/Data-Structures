#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

//void find_words_recurs(const vector<string>& dictionary, vector<vector<char > >& grid, vector<int> constraints){}
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

bool validity(vector<vector<char> > grid, vector<int> constraints, vector<string> dictionary,vector<vector<bool> > print ){
    
    int num_cons = constraints.size();
    string v_line; 
    string h_line;
    int num_words = 0;
    //HORIZONTAL
    for (int row = 0; row < grid.size(); row++){
        for (int col = 0; col < grid[row].size(); col++){
            h_line = "";
            for (int cross = col; cross<grid[row].size(); cross++){
                h_line += grid[row][cross];
                for( int word = 0; word< dictionary.size(); word++){
                    if (h_line == dictionary[word]){
                        num_words++;
                    }
                }

            }
        }
    }
    for (int row = 0; row < grid.size(); row++){
        for (int col = 0; col < grid.size(); col++){
            v_line = "";
            for (int cross = col; cross<grid.size(); cross++){
                v_line += grid[cross][row];
                for (int word = 0; word<dictionary.size(); word++ ){
                    if (v_line == dictionary[word])
                        num_words++;
                }
            }
        }
    }
    if (num_words == num_cons)
        return true;
    else return false;
}

int num_solutions(vector<string> dictionary, vector<vector<char> > grid, vector<int> constraints){
    vector<vector<bool> > print = make_bool_grid(grid);
    vector<vector<char > > temp = grid; 
    int sols = 0;
    vector<int> initial = constraints;
    string h_line;
    string v_line;
    vector<string> h_extra; 
    vector<string> v_extra;
    for (int row = 0; row<grid.size(); row++){ // horizontal
        for (int col = 0; col <grid[row].size(); col++){
            h_line = "";
            vector<int> h_pos;
            for (int cross = col; cross< grid[row].size(); cross++){
                if (grid[row][cross]!='#')
                    h_line+= grid[row][cross];
                h_pos.push_back(cross);
                for (int word = 0; word < dictionary.size(); word++){
                    if (dictionary[word] == h_line){ // horizontal line
                        vector<int>::iterator itr = find(initial.begin(), initial.end(), h_line.size());
                        if (itr!=initial.end()){
                            for (int t = 0; t< h_pos.size(); t++){
                                print[row][h_pos[t]]= false;
                            }
                            initial.erase(itr);
                        }else{
                            sols++;
                            h_extra.push_back(h_line);
                        }
                    
                    }
                }
            }
        }
    }
     for (int row = 0; row<grid.size(); row++){ //grid[0]
        for (int col = 0; col < grid.size() ; col++){//vertical
            v_line = "";
            vector<int> v_pos;
            for (int cross = col; cross< grid.size(); cross++){
                v_line+= grid[cross][row];
                v_pos.push_back(cross);
                for (int word = 0; word < dictionary.size(); word++){
                    if (dictionary[word] == v_line){
                        vector<int>::iterator itr = find(initial.begin(), initial.end(), v_line.size());
                        if (itr!=initial.end()){   
                            for (int t= 0; t<v_pos.size();t++){
                                print[v_pos[t]][row] = false;
                            }            
                            initial.erase(itr);    
                        }else{
                            sols++;
                            v_extra.push_back(v_line);
                        }
                    }
                }
            }
        }
    } 
    int count = 0;
    vector<vector<char> > ans = create_grid(grid,print);
    bool question = validity(ans,constraints,dictionary,print);
    if (question == false)
        count--;
    
    for (int i = 0; i<sols; i++){
        vector<int> rest = constraints;
        string h_line; 
        string v_line;
        grid = temp;
        vector<string> d = dictionary;
        vector<vector<bool> > print = make_bool_grid(grid);
        for (int row = 0; row<grid.size(); row++){
            for (int col = 0; col<grid[row].size(); col++){
                h_line = "";
                vector<int> h_pos;
                for (int cross = col; cross<grid[row].size(); cross++){
                    h_line+= grid[row][cross];
                    h_pos.push_back(cross);
                    for (int word = 0; word<d.size(); word++){
                        vector<string>::iterator found = find(h_extra.begin(), h_extra.end(), h_line);
                        if (d[word]==h_line && found!=h_extra.end()){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), h_line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),h_line);
                            d.erase(str);
                            if (itr!=rest.end()){
                                for (int t = 0; t<h_pos.size(); t++){
                                    print[row][h_pos[t]] = false;
                                }
                                rest.erase(itr);
                                h_extra.erase(found);
                            }
                        }else if (d[word] == h_line && h_extra.size()==0){
                            vector<int>::iterator itr = find(rest.begin(),rest.end(), h_line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),h_line);
                            d.erase(str);
                            if (itr!=rest.end()){
                                for (int t= 0 ; t< h_pos.size(); t++){
                                    print[row][h_pos[t]] = false;
                                }
                            }
                        }

                    }
                }
            }
        }
        d = dictionary;
        for (int row = 0; row<grid.size();row++){ //grid[0]
            for (int col = 0; col < grid.size(); col++){//vertical
                vector<int> v_pos;
                v_line = "";
                for (int cross = col; cross< grid.size(); cross++){
                    v_line += grid[cross][row];
                    v_pos.push_back(cross);
                    for (int word = 0; word< d.size(); word++){
                        vector<string>::iterator found = find(v_extra.begin(), v_extra.end(), v_line);
                        if (d[word] == v_line && found!=v_extra.end()){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), v_line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),v_line);
                            d.erase(str);
                            if (itr!= rest.end()){
                                for ( int t = 0; t<v_pos.size(); t++){
                                    print[v_pos[t]][row] = false;
                                }
                                rest.erase(itr);
                                v_extra.erase(found);
                            }
                        }else if (d[word] == v_line && v_extra.end()==found){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), v_line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),v_line);
                            d.erase(str);
                            if (itr!=rest.end()){
                                for (int t = 0; t < v_pos.size(); t++){
                                    print[v_pos[t]][row] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        vector<vector<char> > ans = create_grid(grid,print);
        bool question = validity(ans,constraints,dictionary,print);
        if (question == false)
            count--;
    }
     if (initial.size()==0) //test 7 works, test 10 doesn't
        return sols+count+1;
    else return 0;
}

void solutions(vector<string>& dictionary, vector<vector<char > >& grid, vector<int>& constraints, int num_solutions){
    //INITIAL
    //.horizontal
    vector<vector< char > > temp = grid;
    vector<int> initial = constraints;
    vector<string> temp_dict = dictionary;
    cout<<"Number of solution(s): "<<num_solutions<<std::endl;
    cout<<"Board:"<<std::endl;
    vector<vector<bool> > print = make_bool_grid(grid);
    string h_line;
    string v_line;
    vector<string> h_extra; 
    vector<string> v_extra;
    for (int row = 0; row<grid.size(); row++){ // horizontal
        for (int col = 0; col <grid[row].size(); col++){
            h_line = "";
            vector<int> h_pos;
            for (int cross = col; cross< grid[row].size(); cross++){
                if (grid[row][cross]!='#')
                    h_line+= grid[row][cross];
                h_pos.push_back(cross);
                for (int word = 0; word < temp_dict.size(); word++){
                    if (temp_dict[word] == h_line){ // horizontal line
                        vector<int>::iterator itr = find(initial.begin(), initial.end(), h_line.size() );
                        vector<string>::iterator str = find(temp_dict.begin(), temp_dict.end(), h_line);
                        temp_dict.erase(str);
                        if (itr!=initial.end()){
                            for (int t = 0; t< h_pos.size(); t++){
                                print[row][h_pos[t]] = false;
                            }
                            initial.erase(itr);
                        }else{
                            h_extra.push_back(h_line);
                        }
                    
                    }
                }
            }
        }
    }
    for (int row = 0; row<grid.size(); row++){
        for (int col = 0; col < grid.size() ; col++){//vertical
            v_line = "";
            vector<int> v_pos;
            for (int cross = col; cross< grid.size(); cross++){
                v_line+= grid[cross][row];
                v_pos.push_back(cross);
                for (int word = 0; word < temp_dict.size(); word++){
                    if (temp_dict[word] == v_line){
                        vector<int>::iterator itr = find(initial.begin(), initial.end(), v_line.size());
                        vector<string>::iterator str = find(temp_dict.begin(), temp_dict.end(), v_line);
                        temp_dict.erase(str);
                        if (itr!=initial.end()){
                            for (int t =0; t< v_pos.size(); t++){
                                print[v_pos[t]][row] = false;
                            }                    
                            initial.erase(itr);    
                        }else{
                            v_extra.push_back(v_line);
                        }
                    }
                }
            }
            
        }
    } 
    
    print_board(grid,print);
    //Rest of the solutions
    
    for (int i = 0; i < num_solutions-1; i++){
        cout<<"Board:"<<std::endl;
        vector<int> rest = constraints;
        temp_dict = dictionary;
        
        grid = temp;
        vector<vector<bool> > print = make_bool_grid(grid);
        string h_line;
        string v_line;
        for (int row = 0; row < grid.size(); row++){
            for (int col = 0; col < grid[row].size(); col++){//horizontal
                h_line = "";
                vector<int> h_pos;
                for (int cross = col; cross< grid[row].size(); cross++){
                    if (grid[row][cross] != '#')
                        h_line += grid[row][cross];
                    h_pos.push_back(cross);
                    for (int word = 0; word < temp_dict.size(); word++){
                        vector<string>::iterator found = find(h_extra.begin(), h_extra.end(), h_line);
                        if (temp_dict[word] == h_line && found!=h_extra.end()){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), h_line.size());
                            vector<string>::iterator str = find(temp_dict.begin(), temp_dict.end(), v_line);
                            temp_dict.erase(str);
                            if( itr!= rest.end()){
                                for ( int t = 0; t< h_pos.size(); t++){
                                    print[row][h_pos[t]] = false;
                                }
                                rest.erase(itr);
                                h_extra.erase(found);
                            }
                        }else if (temp_dict[word]== h_line &&  h_extra.size()==0){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), h_line.size());
                            vector<string>::iterator str = find(temp_dict.begin(), temp_dict.end(), v_line);
                            temp_dict.erase(str);
                            if (itr!=rest.end()){
                                for (int t = 0; t<h_pos.size(); t++){
                                    print[row][h_pos[t]]= false;
                                }
                                rest.erase(itr);
                            }
                        }
                    }
                }
            }
        }//have ski in v_extra when v_extra should be empty
        temp_dict = dictionary;
        for (int row = 0; row<grid.size();row++){
            for (int col = 0; col < grid.size(); col++){//vertical
                vector<int> v_pos;
                v_line = "";
                for (int cross = col; cross< grid.size(); cross++){
                    v_line += grid[cross][row];
                    v_pos.push_back(cross);
                    for (int word = 0; word< temp_dict.size(); word++){
                        vector<string>::iterator found = find(v_extra.begin(), v_extra.end(), v_line);
                        if (temp_dict[word] == v_line && found!=v_extra.end()){
                            
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), v_line.size());
                            if (itr!= rest.end()){
                                for ( int t = 0; t<v_pos.size(); t++){
                                    print[v_pos[t]][row] = false;
                                }
                                rest.erase(itr);
                                v_extra.erase(found);
                            }
                        }else if (temp_dict[word] == v_line && v_extra.end()==found){
                            vector<int>::iterator itr = find(rest.begin(), rest.end(), v_line.size());
                            if (itr!=rest.end()){
                                for (int t = 0; t < v_pos.size(); t++){
                                    print[v_pos[t]][row] = false;
                                }
                                rest.erase(itr);
                            }
                        }
                    }
                }
            }
        }
        print_board(grid,print);
    }
    
}

vector<string> make_words(ifstream& dictionary_file, ofstream& output){
    vector<string> words; 
    string word;
    while (dictionary_file >> word){
        words.push_back(word);
    }
    
    return words;
}

vector<vector<char> > make_grid(ifstream& grid_file, ofstream& output){
    vector<char> temp;
    vector<vector<char> > puzzle;
    string line;
    while (getline(grid_file,line)){
        for (int i = 0; i < line.size(); i ++){
            temp.push_back(line[i]);
        }
        puzzle.push_back(temp);
        temp.clear();
    }
    return puzzle;
}

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

vector<vector<string> > solve( vector<vector<char> > grid, vector<string>& dictionary, vector<int> constraints, vector<vector<string> >& words, vector<string>& extra_words, vector<int>& restrictions){
    string line;
    vector<int> cons = constraints;
    vector<vector<bool> > print = make_bool_grid(grid);
    if (extra_words.size() == 0 && restrictions.size() == 0 ){ // done with both solutions
       // cout<<"SOLUTION 1: "<<words.size()<<std::endl;
        return words;
    }
    else if (restrictions.size() != 0){ //First initial solution
        //cout<<"SOLUTION 2: "<<words.size()<<std::endl;
        vector<string> sentence; 
        for (int row = 0; row<grid.size(); row++){ // horizontal
            for (int col = 0; col <grid[row].size(); col++){
                line = "";
                vector<int> pos;
                for (int cross = col; cross< grid[row].size(); cross++){
                    if (grid[row][cross]!='#')
                        line+= grid[row][cross];
                    pos.push_back(cross);
                    for (int word = 0; word < dictionary.size(); word++){
                        if (dictionary[word] == line){ // horizontal line
                            vector<int>::iterator itr = find(restrictions.begin(), restrictions.end(), line.size());
                            if (itr!=restrictions.end()){
                                for (int t = 0; t< pos.size(); t++){
                                    print[row][pos[t]]= false;
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
        for (int row = 0; row<grid.size(); row++){ //grid[0]
            for (int col = 0; col < grid.size() ; col++){//vertical
                line = "";
                vector<int> pos;
                for (int cross = col; cross< grid.size(); cross++){
                    line+= grid[cross][row];
                    pos.push_back(cross);
                    for (int word = 0; word < dictionary.size(); word++){
                        if (dictionary[word] == line){
                            vector<int>::iterator itr = find(restrictions.begin(), restrictions.end(), line.size());
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
        vector<vector<char> > ans = create_grid(grid,print);
        bool question = validity(ans,constraints,dictionary,print);
        if (question == false){
            extra_words.clear();
            restrictions.clear();
            solve(grid, dictionary, constraints, words, extra_words, restrictions);
        }else{
            solve(grid, dictionary, constraints, words, extra_words, restrictions);
        }
    }
    else if (extra_words.size() != 0){ //rest of solutions
        //cout<<"SOLUTION 3: "<<words.size()<<std::endl;
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
                        if (d[word]==line && found!=extra_words.end()){
                            vector<int>::iterator itr = find(cons.begin(), cons.end(), line.size());
                            vector<string>::iterator str = find(d.begin(),d.end(),line);
                            d.erase(str);
                            if (itr!=cons.end()){
                                for (int t = 0; t<pos.size(); t++){
                                    print[row][pos[t]] = false;
                                }
                                cons.erase(itr);
                                extra_words.erase(found);
                                sentence.push_back(line);
                            }
                        }else if (d[word] == line && extra_words.size()==0){ 
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
        for (int row = 0; row<grid.size();row++){ //grid[0]
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
        /*//return words;
        cout<<std::endl;
        for (int i = 0 ; i < sentence.size(); i++)
            cout<<" "<<sentence[i]<<" ";
        cout<<std::endl;
        cout<<"Extra_words size: "<<extra_words.size()<<std::endl;
        cout<<"Constraints size: "<<constraints.size()<<std::endl;*/
        vector<vector<char> > ans = create_grid(grid,print);
        bool question = validity(ans,constraints,dictionary,print);
        if (question == false){
            solve(grid,dictionary,constraints,words,extra_words,restrictions);
        }else{
            words.push_back(sentence);
            solve(grid,dictionary,constraints,words,extra_words,restrictions);
        }
    }

    
    return words;
}

void print_solve(vector<vector<string> >& words, vector<vector<char> >& grid ){
    string line;
    cout<<"Number of solution(s): "<<words.size()<<std::endl;
    for (int word = 0; word< words.size(); word++){
        vector<vector<bool> > print = make_bool_grid(grid);
        for (int row = 0; row<grid.size(); row++){
            for (int col = 0; col< grid[row].size(); col++){
                line = "";
                vector<int> pos;
                for (int cross = col; cross<grid[row].size(); cross++){
                    line+= grid[row][cross];
                    pos.push_back(cross);
                    for (int i = 0; i<words.size(); i++){
                        if (line == words[word][i]){
                            for (int t = 0; t< pos.size(); t++){
                                print[row][pos[t]] = false;
                            }
                        }
                    }
                }
            }
        }

        for (int row = 0; row<grid.size(); row++){
            for (int col = 0; col< grid.size(); col++){
                line = "";
                vector<int> pos;
                for (int cross = col; cross<grid.size(); cross++){
                    line+= grid[cross][row];
                    pos.push_back(cross);
                    for (int i = 0; i<words.size(); i++){
                        if (line == words[word][i]){
                            for (int t = 0; t< pos.size(); t++){
                                print[pos[t]][row]= false;
                            }
                        }
                    }
                }
            }
        }
        cout<<"Board:"<<std::endl;
        print_board(grid,print);
    }
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
    
    vector<int> restrictions = constraints;
    vector<string> extra_words;
    vector<vector<string> > words;
    vector<vector<string> > sol = solve(grid, dictionary, constraints, words, extra_words, restrictions);
    //cout<<"sol size: "<<sol.size()<<std::endl;
    print_solve(sol,grid);
    
    /*
    int num = num_solutions(dictionary,grid,constraints);
    int a = strcmp(argv[3],"all_solutions");
    int b = strcmp(argv[3],"one_solution");
    if (b == 0){
        if (num==0)
            cout<<"Number of solution(s): 0"<<std::endl;
        else solutions(dictionary,grid,constraints,1);//cout<<"Number of solution(s): "<<num<<std::endl;
    }else if (a == 0){
        if (num==0)
            cout<<"Number of solution(s): 0"<<std::endl;        //  TEST 10 WONT WORK, Test 7 works from this
        else solutions(dictionary,grid,constraints,num);
    }*/
}