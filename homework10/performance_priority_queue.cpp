#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

using namespace std;
// defined in performance.cpp
void usage();

template <class T>
void pq_sort(priority_queue<T, vector<T>, greater<T> >& pq_min, ostream& ostr, int& output_count){
  output_count = pq_min.size();
  /*for (typename priority_queue<T, vector<T>, greater<T> >::iterator itr = pq_min.begin(); itr != pq_min.end(); itr++){
    ostr<<*itr<<"\n";
  }*/
  for (int i = 0 ; i < output_count; i++){
    ostr<<pq_min.top()<<"\n";
    pq_min.pop();
  }
}

template <class T>
void pq_remove_duplicates(priority_queue<T, vector<T>, greater<T> >& pq_min, ostream& ostr, int& output_count){
  //Not Feasible
}

template <class T>
void pq_mode(priority_queue<T, vector<T>, greater<T> >& pq_min, ostream& ostr, int& output_count){
  //go through popping everything and hold ints to check amount of times found
  int init_size = pq_min.size();
  T prev = pq_min.top();
  T best_type;
  int best = 0;
  int curr = 0;
  for (int i = 0; i < init_size; i++){
    if (prev == pq_min.top()){
      curr++;
      pq_min.pop();
    }else{
      if (curr > best){
        best = curr;
        best_type = prev;
      }
      curr = 0;
      prev = pq_min.top();
      pq_min.pop();
      curr++;
    }
  }
  ostr<<best_type<<"\n";
}

void pq_closest_pair(priority_queue<int, vector<int>, greater<int> >& pq_min, ostream& ostr, int& output_count){
  int init_size = pq_min.size();
  int best = pq_min.top();
  int prev = pq_min.top();
  int best_type1;
  int best_type2;
  int diff;
  for (int i = 0; i < init_size; i++){
    if (pq_min.top() != prev){
      diff = pq_min.top() - prev;
      if (diff < best){
        best = diff;
        best_type1 = pq_min.top();
        best_type2 = prev;
        prev = pq_min.top();
        pq_min.pop();
      }else{
        prev = pq_min.top();
        pq_min.pop();
      }
    }else pq_min.pop();
  }
  ostr<<best_type2<<std::endl;
  ostr<<best_type1<<std::endl;
}

template <class T>
void pq_first_sorted(priority_queue<T, vector<T>, greater<T> >& pq_min, ostream& ostr, int& output_count, int optional_arg){
  for (int i = 0; i < optional_arg; i++){
    ostr<<pq_min.top()<<"\n";
    pq_min.pop();

  
  }
}

void pq_longest_substring(priority_queue<string, vector<string>, greater<string> >& pq_min, ostream& ostr, int& output_count){
  //Not Feasible
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)
  if (type == "string"){
    priority_queue<string, vector<string>, greater<string> > pq_min;
    priority_queue<string,vector<string> > pq_max;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq_min.push(s);
      pq_max.push(s);
      input_count++;
    }
    if (operation == "sort")                      {pq_sort(pq_min,ostr,output_count);}
    else if (operation == "remove_duplicates")  {pq_remove_duplicates(pq_min,ostr,output_count); }
    else if (operation == "mode")              { pq_mode              (pq_min,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { pq_first_sorted      (pq_min,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { pq_longest_substring (pq_min,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a pq of integers
    priority_queue<int, vector<int>, greater<int> > pq_min;
    priority_queue<int,vector<int> > pq_max;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq_min.push(v);
      pq_max.push(v);
      input_count++;
    }
    if (operation == "sort")                    {pq_sort(pq_min,ostr,output_count);}
    else if (operation == "remove_duplicates")  {pq_remove_duplicates(pq_min,ostr,output_count); }
    else if (operation == "mode")              { pq_mode              (pq_min,ostr,output_count); }
    else if (operation == "closest_pair")      { pq_closest_pair      (pq_min,ostr,output_count); }
    else if (operation == "first_sorted")      { pq_first_sorted      (pq_min,ostr,output_count,optional_arg); }
    // "longest_supqring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  /*std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  exit(0);*/
}
