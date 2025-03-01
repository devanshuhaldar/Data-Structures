
#include <map>
#include <utility>
#include <algorithm>
#include<iostream>
#include <ostream>
#include <vector>
using namespace std;

bool compare( pair<int,int> m1,  pair<int,int> m2){
    return m1.second<m2.second;
}
/*
void modes( vector<int> array){
    map<int, int> m;
    for (int i = 0; i < array.size(); i++){
        m[array[i]]++;
    }
    map<int,int>::iterator x = max_element(m.begin(),m.end(), compare);
    vector<int> n; 
    for (map<int,int>::iterator itr = m.begin(); itr!=m.end(); itr++){
        if (itr->second == x->second)
            n.push_back(itr->first);
        
    }
    
    for (int i = 0; i < n.size(); i++){
        cout<<n[i]<<std::endl;
    }
    
}*/

void modes(vector<int> array){
    typedef map<int,int> MAP;
    MAP m; 
    for (int i = 0; i < array.size(); i++){
        MAP::iterator f = m.find(array[i]);
        if (f!=m.end()){
            f->second++;
        }else{
            m.insert({array[i], 1});
            //MAP::iterator itr = m.insert(array[i], 1);
        }
    }
    MAP::iterator x = max_element(m.begin(), m.end(), compare);
    vector<int> n;
    for (MAP::iterator itr = m.begin(); itr!=m.end(); itr++){
        if(itr->second == x->second){
            n.push_back(itr->first);
        }
    }

    for (int i = 0; i < n.size(); i++)
        cout<<n[i]<<std::endl;
}

int main(){
    vector<int> array = {19 ,83 ,-12 ,83 ,65 ,19 ,45 ,-12, 45, 19 ,45};
    modes(array);
}