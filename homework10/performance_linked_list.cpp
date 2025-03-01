#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

using namespace std;
// defined in performance.cpp
void usage();

//list sort
template <class T>
void list_sort(list<T> &lst, ostream &ostr, int &output_count){
  lst.sort();
  output_count = lst.size();
  typename list<T>::iterator itr = lst.begin();
  for (int i = 0; i < output_count; i++){
    ostr << *itr << "\n";
    itr++;
  }
}

//list remove duplicates
template <class T>
void list_remove_duplicates(list<T>& lst, ostream &ostr, int& output_count){
  output_count = 0;
  for (typename list<T>::iterator i = lst.begin(); i != lst.end(); i++){
    bool dup = false;
    for (typename list<T>::iterator j = lst.begin(); j != i ; j++){
      if (*i == *j){
        dup = true;
        break;
      }
    }
    if (!dup) {
      ostr << *i << "\n";
      output_count++;
    }
  }
}

//list mode
template <class T>
void list_mode(list<T>& lst, ostream& ostr, int &output_count){
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count =0;
  typename std::list<T>::iterator current = lst.begin();
  ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for (; current != lst.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output list
  output_count = 1;
  ostr << mode << "\n";
}

//list closest pair
void list_closest_pair(std::list<int>& lst, ostream& ostr, int& output_count){
  assert (lst.size() >= 2);
  // use the list sort algorithm
  lst.sort();
  output_count = 2;
  int best;
  list<int>::iterator best_itr = lst.end();
  list<int>::iterator best2_itr = lst.end();
  // the two elements with closest value must be next to each other in sorted order
  list<int>::iterator end = lst.end();
  end--;
  for (list<int>::iterator itr = lst.begin(); itr != end; itr++){
    itr++;
    int first = *itr;
    itr--;
    int second = *itr;
    int diff = first - second; 
    if (diff != 0){
      if (best_itr == lst.end() || diff< best){
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
  ostr << *best_itr << "\n";
  ostr << *(best2_itr) << "\n";
}

//list first sorted
template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)lst.size() >= optional_arg);
  // use the list sort algorithm
  lst.sort();
  output_count = optional_arg;
  typename list<T>::iterator itr = lst.begin();
  for (int i = 0; i < output_count; i++) {
    ostr << *itr << "\n";
    itr++;
  }
}

//list longest substring
void list_longest_substring(list<string>& lst, ostream& ostr, int& output_count){
  int best_size = 0;
  string best_str;
  for (list<string>::iterator i = lst.begin(); i != lst.end(); i++){
    for (list<string>::iterator j = i; j != lst.end(); j++){ //same explanation as in vector cpp
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

//list main
void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;
  // load the data into a list of strings
  if (type == "string"){
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a list of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  /*
  std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);*/
}
