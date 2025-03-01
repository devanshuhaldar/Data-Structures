#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

#include "Unordered.h"

using namespace std;

//Creates the Hash Table and returns it.
Hash_Table<pair<string,vector<int> > > make_hash_table(int table_size,const string& file_name, const int kmer, float occupancy ){
        
    if (table_size == -1)
        table_size = 100;
    if (occupancy == -1.0) //default set
        occupancy = .5;
    
    Hash_Table<pair<string,vector<int> > > hash(table_size); //Construct hash table
    hash.setOccupancy(occupancy); //set occupancy

    //Create one string containing entire genome sequence. 
    ifstream infile(file_name);
    string line;
    string entire_genome = "";
    while(infile>>line){
        entire_genome += line; 
    }
    
    for (long unsigned int i = 0; i < entire_genome.size()-kmer; i++){ //go through each positions and include into hash table.
        string seq = "";
        for (int k = 0; k < kmer; k++){ //each sequence in hash table should be of size kmer
            seq += entire_genome[i+k];
        }
        pair<string, int> p(seq, i);
        hash.insert(p);
    }
    return hash;
}

//Returns true if genome sequence has no matches in the hash table 
//helper function for solve_query()
bool hasNoMatch(const vector<int>& positions, int mismatch, const string& genome, string& str, const pair<string, int>& query){
    //Code is basically copied from solve_query() function. But here, the goal is to return true or false to see if it has any matches.
    //I was having an issue with printing No Match so many times. So a simple function like this can allow me to print No Match once.
    
    for (int i = 0; i < positions.size(); i++){ //go through each position.
        mismatch = 0; //reset mismatches and string.
        str = "";
        for (int j = 0; j < query.first.size(); j++){ //go through genome sequence of size kmer
            if (mismatch <= query.second){ //if you have not overflowed mismatches
                if (genome[positions[i] + j] == query.first[j]){//matching
                    str+=genome[positions[i]+j];
                }else{//did not match
                    mismatch++;
                    str+=genome[positions[i]+j];
                }
            }else{
                break; // no matches found. so break.
            }
        }
        if (mismatch <= query.second){
            return false;
        }
        
    }//should end up here if it never found a single match
    return true;
}

//Main query searching and finding function
void solve_query( Hash_Table<pair<string,vector<int> > >& table, const pair<string, int>& query, const int kmer, const string& file_name){
    cout<<"Query: "<<query.first<<std::endl;
    string seed = ""; //seed sequence
    ifstream infile(file_name);
    string line;
    string genome = ""; 
    while(infile>>line){
        genome += line; //contains whole genome
    }

    for (int i = 0; i < kmer; i++)
        seed += query.first[i]; //gather seed
    int pos = table.find(seed); //find the seed in the hash table
    vector<int> positions = table.getPositions(pos); //get all the positions in which the seed was found 

    int mismatch;
    string str;
    for (int i = 0; i < positions.size(); i++){//go through all found positions and check
        mismatch = 0;
        str = "";//reset mismatch and str
        for (int j = 0; j < query.first.size(); j++){
            if (mismatch <= query.second){
                if (genome[positions[i] + j] == query.first[j]){//matching
                    str+=genome[positions[i]+j];
                }else{//did not match
                    mismatch++; //update mismatch
                    str+=genome[positions[i]+j];
                }
            }else{
                break;
            }
        }
        if (mismatch <= query.second)//found a sequence within the mismatch constraint so print.
            cout<<positions[i]<<" "<<mismatch<<" "<<str<<std::endl;
        else if (hasNoMatch(positions, mismatch, genome, str, query)){ //entire seed does not have a sequence (no match)
            cout<<"No Match"<<std::endl;
            break;
        }
    }

}

//main 
int main(){
    string str;
    string file_name;
    int table_size = -1;
    float occupancy = -1.0; //allows me to check in the other makehashtable function if I need to set these variables to the default
    int kmer;
    int mismatch;
    string sequence;
    Hash_Table<pair<string,vector<int> > > table;
    pair< string, int>  query; //query contains just a simple string and int
    while (cin>> str){
        if (str == "genome"){
            cin>>file_name;
        }else if (str == "table_size"){
            cin>>table_size;
        }else if (str == "occupancy"){
            cin>>occupancy;
        }else if (str == "kmer"){
            cin>>kmer;
            table = make_hash_table(table_size, file_name, kmer, occupancy); // create hash table
        }else if (str == "query"){
            cin>>mismatch>>sequence;
            query.first = sequence;
            query.second = mismatch;
            solve_query(table, query, kmer, file_name); //call solve query function
        }else if (str == "quit"){
            break; //stop 
        }
    }
}