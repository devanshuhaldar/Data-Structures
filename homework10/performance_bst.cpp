#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;
// defined in performance.cpp
void usage();

template <class T>
void bst_sort(map<T,int>& st, ostream& ostr, int& output_count){
  output_count = 0;
  for (typename map<T, int>::iterator itr = st.begin(); itr!=st.end(); itr++){
    for (int i = 0; i < itr->second ; i++)
      ostr<<itr->first<<"\n";
  }
}

template <class T>
void bst_remove_duplicates(set<T>& st, ostream& ostr, int& output_count){
  output_count = 0;
  for (typename set<T>::iterator itr = st.begin(); itr!=st.end(); itr++){
    //ostr<<*itr<<"\n";
    output_count++;
  }
}

template <class T>
void bst_mode(map<T,int>& st, ostream& ostr, int& output_count){
  typename map<T,int>::iterator init = st.begin();
  for (typename map<T,int>::iterator itr = st.begin(); itr != st.end(); itr++){
    if (init->second < itr->second){
      init = itr;
    }
  }
  ostr<<init->first<<"\n";
  output_count = 1;
}

void bst_closest_pair(map<int,int>& st, ostream& ostr,int& output_count){
  assert (st.size() >= 2);
  // use the set sort algorithm
  output_count = 2;
  int best;
  map<int,int>::iterator best_itr = st.end();
  map<int,int>::iterator best2_itr = st.end();
  // the two elements with closest value must be next to each other in sorted order
  map<int,int>::iterator end = st.end();
  end--;
  for (map<int,int>::iterator itr = st.begin(); itr != end; itr++){
    itr++;
    int first = itr->first;
    itr--;
    int second = itr->first;
    int diff = first - second; 
    if (diff != 0){
      if (best_itr == st.end() || diff < best){
        best = diff; 
        best_itr = itr;
        itr++;
        best2_itr = itr;
        itr--;
      }
    }
  }
  // print the two elements
  output_count = 2;
  ostr << best_itr->first << "\n";
  ostr << best2_itr->first << "\n";
}

template <class T>
void bst_first_sorted(map<T,int>& st, ostream& ostr, int& output_count, int optional_arg){
  assert (optional_arg >= 1);
  assert ((int)st.size() >= optional_arg);
  // use the sst sort algorithm
  output_count = optional_arg;
  typename map<T,int>::iterator itr = st.begin();
  int counter = 0;
  for (; itr!=st.end(); itr++){
    for (int i = 0; i < itr->second; i++){
      ostr<<itr->first<<"\n";
      counter++;
      if (counter == output_count)
        break;
    }
    if (counter == output_count)
      break;
  }
}

void bst_longest_substring(set<string>& st, ostream& ostr, int& output_count){
  int best_size = 0;
  string best_str;
  for (set<string>::iterator i = st.begin(); i != st.end(); i++){ //same explanation as in vector cpp
    for (set<string>::iterator j = i; j != st.end(); j++){
      string str = "";
      string str2 = "";
      string word1 = *i;
      string word2 = *j;
      if (word1 != word2){
        if (word1.size() >= word2.size()){
          for (int gen = 0 ; gen < word2.size(); gen++){
            str2 = "";
            for (int small = gen; small < word2.size(); small++){
              str2+=word2[small];
              str = "";
              for (int large = 0; large < word1.size(); large++){
                str+=word1[large];
                if (str2 == str){
                  if (str.size() > best_size){
                    best_str = str;
                    best_size = str.size();
                  }
                }
              }
            }
          }
        }else{//word2 greater
          for (int gen = 0 ; gen < word2.size(); gen++){
            str2 = "";
            for (int small = gen; small < word1.size(); small++){
              str2+=word1[small];
              str = "";
              for (int large = 0; large < word2.size(); large++){
                str+=word2[large];
                if (str2 == str){
                  if (str.size() > best_size){
                    best_str = str;
                    best_size = str.size();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  ostr<<best_str<<std::endl;
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  // std::map<std::string,int> mp;
  if (type == "string"){
    std::set<std::string> bst;
    std::string s;
    map<string,int> mp;
    input_count = 0;
    int sprev = 0;
    while (istr >> s) {
      if (operation == "remove_duplicates" || operation == "longest_substring"){
        bst.insert(s);
        if (sprev < bst.size()){
          if (operation == "remove_duplicates")
            ostr<<s<<std::endl;
          sprev++;
        }
      }
      mp[s] += 1;
      input_count++;
    }
    if (operation== "sort")  {bst_sort(mp, ostr, output_count);}
    else if (operation == "remove_duplicates")  { bst_remove_duplicates(bst, ostr, output_count);}//print as you insert into hash. 
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { bst_longest_substring (bst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a bst of integers
    std::set<int> bst;
    map<int,int> mp;
    int v;
    input_count = 0;
    int sprev = 0;
    while (istr >> v) {
      if (operation == "remove_duplicates"){
        bst.insert(v);
        if (sprev < bst.size()){
          ostr<<v<<std::endl;
          sprev++;
        }
      }
      mp[v] += 1;
      input_count++;
    }
    if (operation == "sort") {bst_sort(mp,ostr, output_count ); }
    else if (operation == "remove_duplicates") {bst_remove_duplicates(bst, ostr, output_count); }//print as you insert into hash. 
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  /*std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);*/
}
