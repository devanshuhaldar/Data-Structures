#ifndef _unordered_
#define _unordered_

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

//Keytype:  pair<string, vector<int> > 
template <class KeyType> 
class Hash_Table{
public:
    Hash_Table() {}
    Hash_Table(unsigned int s) : table(s), sizem(0) {}  //constructor
    Hash_Table(const Hash_Table<KeyType>& old) : table(old.table), sizem(old.sizem) {}
    ~Hash_Table() {}

    unsigned int size() const {return sizem;}//returns size of the hash table

    void setOccupancy(const float o) {occupancy = o;} //sets the occupancy. Needed for my resize table

    //Insert genome sequence and position found in entire genome
    bool insert(const pair<string, int >& p){ 
        const float CAPACITY = (float)sizem/(float)table.size();  //returns float of how full the hash table is
        if (CAPACITY >= occupancy)//if hash table is larger than the occupancy limit --> resize
            this->resize_table(2*table.size()+1); //copied from ds hashset with the style of multypling by 2 and adding 1.

        unsigned int hash = hash_function(p.first);// position in hash table
        if (table[hash].first == ""){  //if empty
            KeyType temp;
            temp.first = p.first;
            temp.second.push_back(p.second);
            table[hash] = temp; //create a pair of string, vector<int> and insert in position
            sizem++; //update size
            return true;
        }else{
            if (table[hash].first == p.first){//sequence already exists, so just add an extra position
                table[hash].second.push_back(p.second);
                return true;
            }else{//Linear Probing. 
                int i = hash+1;
                while(!(table[i].first == "")){//not empty
                    if (table[i].first == p.first){
                        table[i].second.push_back(p.second);
                        return true;
                    }
                    i++;
                }
                //i should equal an empty bucket in vector by the linear probing
                KeyType temp; 
                temp.first = p.first;
                temp.second.push_back(p.second);
                table[i] = temp;
                sizem++; //create pair of string,vector<int> and insert in position (empty bucket)
                return true;
            }
        }              
    }
    

    //Finds position in hash table of the given sequence
    int find(string& seq){
        unsigned int hash = hash_function(seq); //hash position in hash table
        if (table[hash].first == seq)//if poisiton is the sequence just return position
            return hash;
        else{
            //Linear Probing
            int i = hash+1;
            while (i != table.size()-1){//continues going until reaches end of table
                if (table[i].first == seq){ //if you find sequence return
                    return i;
                }else i++; //otherwise keep going
            }
            if (i == hash) return i; //if last position is hash return
            else return -1; //otherwise doesn't exist in hash table (THIS CASE SHOULDN'T EXIST)
        }
    }

    //just for debugging. testing the hash table if it placed in positions and string correctly
    void print(){
        for (unsigned int i  = 0 ; i < table.size() ; i++){
            if (!(table[i].first == "")){
                cout<<table[i].first;
                for (unsigned int k = 0; k < table[i].second.size(); k++){
                    cout<<" --> "<<table[i].second[k];
                }
                cout<<std::endl;
            }
        }
    }

    //returns vector<int> of all positions for given string. Given the position needed to search for
    vector<int> getPositions(const int pos){
        return table[pos].second;
    }

private:
    vector<KeyType> table;
    unsigned int sizem;
    float occupancy;
    //My custom hash function. 
    //Gave special multiplying factor for each letter, and multiply again depending on its position. This should work well. Should be unique 
    int hash_function(string key){
        int val = 0;
        for (int i = 0; i < key.size(); i++){
            if (key[i] == 'A'){
                val += (2*val)*i;
            }else if (key[i] == 'T'){
                val += (3*val)*i;
            }else if (key[i] == 'C'){
                val += (4*val)*i;
            }else if (key[i] == 'G'){
                val += (5*val)*i;
            }else cerr<<"Not a genome letter"<<std::endl;
        }
        return val % table.size();
    }

    //Resizes table
    void resize_table(unsigned int new_size){
        vector<pair<string,vector<int> > > old_table = table; //old table
        table.clear();
        table.resize(2*new_size+1);
        //make table 2times as large
        for (unsigned int i = 0; i < old_table.size(); i++){
            table[i] = old_table[i]; //copy old data
        }
    }

    
};
#endif