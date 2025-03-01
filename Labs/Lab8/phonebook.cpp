// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

typedef map<int, string> MAP;
// add a number, name pair to the phonebook
void add(MAP & phonebook, int number, string const& name) {
  phonebook[number] = name;
} //O(1)

// given a phone number, determine who is calling
void identify( MAP & phonebook, int number) {
  MAP::iterator itr = phonebook.find(number);
  if (itr == phonebook.end()) 
    cout << "unknown caller!" << endl;
  else 
    cout << itr->second << " is calling!" << endl;
}//O(1)


int main() {
  // create the phonebook; initially all numbers are unassigned
  //MAP phonebook(10000, "UNASSIGNED");
  MAP phonebook;
  // add several names to the phonebook
  add(phonebook, 1111111, "fred");
  add(phonebook, 2222222, "sally");
  add(phonebook, 3333333, "george");
  //cout<<phonebook[1111]<<std::endl;
  // test the phonebook
  identify(phonebook, 2222222);
  identify(phonebook, 4444);
}
