#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

using namespace std;

int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
	    << "The indentation is proportional to the depth of the node\n"
	    << "so that the value stored at the root is the only value printed\n"
	    << "without indentation.  Also, for each node, the right subtree\n"
	    << "can be found above where the node is printed and indented\n"
	    << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Checkpoints 2 & 3
  ds_set<int> check1;
  check1.insert(1);
  check1.insert(200);
  check1.insert(19);
  check1.insert(8);
  check1.insert(-3);
  check1.insert(9);
  check1.insert(0);
  check1.insert(5);
  check1.insert(6);
  cout<<"Unbalanced Tree"<<std::endl;
  ds_set<int>::iterator ditr = check1.begin();
  ds_set<int>::iterator ds = check1.begin();
  for (; ditr!=check1.end(); ditr++){
    cout<<*ditr<<" ";
    if (*ditr == 200)
      break;
  }
  cout<<std::endl;
  for (; *ditr > *ds; ditr--){
    cout<<*ditr<<" ";
  }
  cout<<*ditr<<std::endl;
  cout<<std::endl;

  ds_set<int> check2;
  check2.insert(8);
  check2.insert(4);
  check2.insert(12);
  check2.insert(2);
  check2.insert(6);
  check2.insert(10);
  check2.insert(14);
  check2.insert(1);
  check2.insert(3);
  check2.insert(5);
  check2.insert(7);
  check2.insert(9);
  check2.insert(11);
  check2.insert(13);
  check2.insert(15);
  cout<<"Balanced Tree"<<std::endl;
  ds_set<int>::iterator itr = check2.begin();
  ds_set<int>::iterator s= check2.begin();
  for (; itr!=check2.end(); itr++){
    cout<<*itr<<" ";
    if (*itr == 15)
      break;
  }
  cout<<std::endl;
  for (; *itr > *s; itr--){
    cout<<*itr<<" ";
  }
  cout<<*itr<<std::endl;

  // Write code to test the forwards & backwards iterators!


  













  return 0;
}
