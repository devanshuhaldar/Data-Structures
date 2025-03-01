#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>

#include "customer.h"

using namespace std;

typedef map<string,int> costume_type;//inventory
typedef map<Customer,string> customer_type;//customer: costume
typedef map<string, vector<Customer> > people_type;//costume: customers

// prototypes for the helper functions
void addCostume(costume_type &costume_shop);
void rentCostume(costume_type& costume_shop, customer_type& customers, people_type& people);
void lookup( costume_type& costume_shop, customer_type& customers, people_type& people);
void printPeople(customer_type& customers, people_type& people);

int main() {
  // three data structures store all of the information for efficiency
  costume_type costume_shop;
  people_type people;
  customer_type customers;
  char c;
  while (cin >> c) {
    if (c == 'a') {
      addCostume(costume_shop);
    } else if (c == 'r') {
      rentCostume(costume_shop,customers,people);
    } else if (c == 'l') {
      lookup(costume_shop,customers,people);
    } else if (c == 'p') {
      printPeople(customers, people);
    } else {
      cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addCostume(costume_type& costume_shop) {
  string costume_name;
  int num;
  cin >> costume_name >> num;
  costume_shop[costume_name] += num; //creating the inventory
  if (num == 1)
    cout<<"Added "<<num<<" "<<costume_name<<" costume."<<std::endl;
  else cout<<"Added "<<num<<" "<<costume_name<<" costumes."<<std::endl;
}



void rentCostume(costume_type& costume_shop, customer_type& customers, people_type& people) {
  string first_name;
  string last_name;
  string costume_name;
  cin >> first_name >> last_name >> costume_name;
  
  Customer a(first_name, last_name);
  costume_type::iterator itr = costume_shop.find(costume_name); 
  customer_type::iterator str = customers.find(a);
  vector<Customer> old = people[costume_name]; //customers that are currently holding this costume.

  if (itr == costume_shop.end()){//costume not in shop
    cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<std::endl;
    customer_type::iterator itr = customers.find(a);
    if (itr==customers.end()){//customer does not exist
      customers[a] = "";
    }
  }else if (costume_shop[costume_name] == 0){//no copies currently available
    cout<<"No "<<costume_name<<" costumes available."<<std::endl;
    customer_type::iterator itr = customers.find(a);
    if (itr==customers.end()){//customer does not exist
      customers[a] = ""; //create customer but make the costume nonexistent
    }
  }else if (str!=customers.end()){ //customer exists
    if (customers[a] == costume_name){
      cout<<first_name<<" "<<last_name<<" already has a "<<costume_name<<" costume."<<std::endl;
    }else{//different costume wanting to be rented
      costume_shop[customers[a]] +=1; //old costume
      costume_shop[costume_name] -=1; // new costume
      vector<Customer> temp = people[customers[a]];
      vector<Customer>::iterator itr = find(temp.begin(),temp.end(), a);
      if (itr!=temp.end())
        temp.erase(itr);
      people[customers[a]] = temp; //removing person from this old costume, customer list
      if (customers[a].size() !=0) //had a costume previously
        cout<<first_name<<" "<<last_name<<" returns a "<<customers[a]<<" costume before renting a "<<costume_name<<" costume."<<std::endl;
      else cout<<first_name<<" "<<last_name<<" rents a "<<costume_name<<" costume."<<std::endl;
      customers[a] = costume_name;
      old.push_back(a); //adds customer to costume customer list
    }
  }else{//customer does not exist
    customers[a] = costume_name;
    costume_shop[costume_name] -=1;
    cout<<first_name<<" "<<last_name<<" rents a "<<costume_name<<" costume."<<std::endl;
    old.push_back(a);//adds customer to costume customer list
  }
  people[costume_name] = old;
  
}


void lookup(costume_type& costume_shop, customer_type& customers, people_type& people) { //CHRONOLOGICALLY ORDERED
  string costume_name;
  cin >> costume_name;
  costume_type::iterator cost = costume_shop.find(costume_name);
  if (cost!=costume_shop.end()){ //costume exists
    cout<<"Shop info for "<<costume_name<<" costumes:"<<std::endl;
    if (cost->second != 0){
      if (cost->second == 1){
        cout<<"  "<<costume_shop[costume_name]<<" copy available"<<std::endl;
      }else cout<<"  "<<costume_shop[costume_name]<<" copies available"<<std::endl;
    }
    vector<Customer> temp = people[costume_name]; //all customers that have this costume currently
    if (temp.size() == 1){
      cout<<"  "<<temp.size()<<" copy rented by:"<<std::endl;
    }else if (temp.size() != 0){
      cout<<"  "<<temp.size()<<" copies rented by:"<<std::endl;
    }

    for (int i = 0; i <temp.size() ; i++){ 
      cout<<"    "<<temp[i].getFirst()<<" "<<temp[i].getLast()<<std::endl;
    }

  }else cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<std::endl;

}


void printPeople( customer_type& customers,  people_type& people) {
  if (customers.size()==1)
    cout<<"Costume info for the "<<customers.size()<<" party attendee:"<<std::endl;
  else cout<<"Costume info for the "<<customers.size()<<" party attendees:"<<std::endl;

  for (customer_type::iterator itr = customers.begin(); itr!=customers.end(); itr++){
    Customer temp = itr->first;
    string costume_name = itr->second;
    if (costume_name.size() == 0){ //costume exists
      cout<<"  "<<temp.getFirst()<<" "<<temp.getLast()<<" does not have a costume."<<std::endl;
    }else{
      cout<<"  "<<temp.getFirst()<<" "<<temp.getLast()<<" is wearing a "<<costume_name<<" costume."<<std::endl;
    }
  }
}

