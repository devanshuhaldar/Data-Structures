// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <algorithm>
#include "dvd.h"
#include "cus.h"
using namespace std;


// several type defs to keep things neat
// (hint, these are STL lists)
typedef list<DVD> inventory_type; //dvd name and number of them
typedef list<Cus> customers_type; // just customer names
typedef list<string> preference_type; // customer name and list of movies they want in order(preference)



// ==================================================================

// Helper function prototypes
string read_customer_name(istream &istr);
string read_dvd_name(istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const string &dvd_name);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  ofstream ostr(argv[2]);
  if (!ostr) {
    cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }


  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;
  // read in and handle each of the 8 keyword tokens

  string token;
  while (istr >> token) {
    if (token == "dvd") {
      string dvd_name = read_dvd_name(istr);
      int copies; //reads in dvd name
      istr >> copies;
      
      bool flag = true;
      if (inventory.size()>0){
        for (list<DVD>::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++){ //goes through each dvd
          if (inventory_itr->getMovie()== dvd_name){
            flag = false;
            int original = inventory_itr->getCount(); //adds copies if movie already in inventory
            int final= original + copies;
            inventory_itr->setCount(final);
          }
        }
      }
      if (flag == true){  // if copy of movie doesn't exist in inventory
        DVD a(dvd_name,copies);
        inventory.push_back(a);
      }

      string copy;
      if (copies ==1){
        copy = "copy";  //for syntax
      }else {
        copy = "copies";
      }
      ostr<<copies<<" "<<copy<<" of "<<dvd_name<<" added"<<std::endl;

      

    } else if (token == "customer") {
      string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;

      preference_type preferences; //preference list
      
      for (int i = 0; i < num_movies; i++) {
        string dvd_name = read_dvd_name(istr); //movie name
        list<string>::iterator itr;
        itr = find(preferences.begin(),preferences.end(),dvd_name);
        
        bool in_stock = false; //checks if movie is in inventory
        for (inventory_type::iterator inventory_itr = inventory.begin(); inventory_itr != inventory.end(); inventory_itr++){
          if (inventory_itr->getMovie()==dvd_name){
            in_stock = true;
          }
        }

        if (in_stock == false){ // not in stock movie or duplicates of movies
          ostr<<"WARNING: No movie named "<<dvd_name<<" in the inventory"<<std::endl;
        } else if (itr!=preferences.end()){//warnings.
          ostr<<"WARNING: Duplicate movie "<<dvd_name<<" on preference list!"<<std::endl;
        } else{
           preferences.push_back(dvd_name);// push back dvd name to preference list
          }

      }

     
      bool customer_found=false; //checks if customer is added already
      for (customers_type::iterator c = customers.begin(); c!=customers.end();c++){
        if (c->getName()==customer_name){
          customer_found = true;
        }
      }

      if (customer_found == false){
        list<string> empty; //adds customer with no added movies.
        Cus c(customer_name, empty, preferences);
        customers.push_back(c);
        ostr<<"new customer: "<<customer_name<<std::endl; //successfully adds customer
      } 
      else { //warning
        ostr<<"WARNING: Already have a customer named "<<customer_name<<std::endl;
      }
      

    } else if (token == "ship") {
//implements shipping function
      shipping_algorithm(inventory,customers,ostr);
      
    } else if (token == "return_oldest") {
      string movie2; 
      string customer_name = read_customer_name(istr);
      int error = 0;
      int emptylist=0;
      for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
        if (c->getName()==customer_name){
          list<string> movies = c->getFilms();
          if (movies.size()==0){
            emptylist++; //if list is empty.
            error++; //person exists
          } else {
            movie2 = movies.front();
            movies.pop_front(); //list not empty 
            c->setFilms(movies);
            error++;
          }
          break;
        }
      }
      for (inventory_type::iterator d = inventory.begin(); d!=inventory.end(); d++){
        if (d->getMovie() == movie2){
          int x = d->getCount();
          x++;  //adding book back to inventory 
          d->setCount(x);   //updating count
        }
      }
      if (error!=0 && emptylist==0) //if no empty list and person exists
        ostr<<customer_name<<" returns "<<movie2<<std::endl;  
      else if (emptylist!=0) //empty list
        ostr<<"WARNING: "<<customer_name<<" has no DVDs to return!"<<std::endl;
      else if(error==0) //person doesn't exist
        ostr<<"WARNING: No customer named "<<customer_name<<std::endl;

    } else if (token == "return_newest") {
      string customer_name = read_customer_name(istr);
      string movie; 
      int error = 0; //values to check for warnings
      int emptylist = 0;
      for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
        if (c->getName()==customer_name){
          list<string> movies = c->getFilms();
          if (movies.size()==0){
            emptylist++; //empty list
            error++;
          }else {
            movie = movies.back();
            movies.pop_back(); //non empty list
            c->setFilms(movies);
            error++;
          }
          break;
        }
      }

      for (inventory_type::iterator d = inventory.begin(); d!=inventory.end(); d++){
        if (d->getMovie() == movie){
          int x = d->getCount();
          x++;  //adding book back to inventory
          d->setCount(x);
        }
      } 

      if (error!=0 && emptylist==0) //no empty list and person exists
        ostr<<customer_name<<" returns "<<movie<<std::endl;  
      else if (emptylist!=0) //empty list
        ostr<<"WARNING: "<<customer_name<<" has no DVDs to return!"<<std::endl;
      else if(error==0)//person doesn't exist
        ostr<<"WARNING: No customer named "<<customer_name<<std::endl;

    } else if (token == "print_customer") {
      string customer_name = read_customer_name(istr);

      //person doesn't exist
      int error = 0;
      for (customers_type::iterator c= customers.begin();c!=customers.end();c++){
        if (c->getName()==customer_name){ 
          error++;
        }
      }
      if(error != 0){
        for (customers_type::iterator c = customers.begin();c!=customers.end();c++){
          if (customer_name == c->getName()){
            list<string> films = c->getFilms();
            list<string> prefs = c->get_preferences();
            if (films.size() !=0){
              string syntax;
              if (films.size()==1){
                syntax = "movie";
              } //syntax for movie vs movies. 1 vs more than 1.
              else syntax = "movies";
              ostr<<customer_name<<" has "<<films.size()<<" "<<syntax<<":"<<std::endl;
              for(preference_type::iterator f = films.begin(); f!=films.end(); f++){
                ostr<<"    "<<*f<<std::endl; // printing the correct way
              }
            }else {
              ostr<<customer_name<<" has no movies"<<std::endl;
            }
            if (prefs.size()!=0){
              ostr<<"  preference list:"<<std::endl; //prints preference list out correctly
              for (preference_type::iterator p =prefs.begin(); p!=prefs.end(); p++ ){
                ostr<<"    "<<*p<<std::endl;
              }
            }

          }
        }
      }else { ostr<<"WARNING: No customer named "<<customer_name<<std::endl;} // no customer.

    } else if (token == "print_dvd") { //prints dvd
      string dvd_name = read_dvd_name(istr);

      /* YOU MUST FINISH THIS IMPLEMENTATION */
      int error= 0;
      for (inventory_type::iterator i = inventory.begin(); i!=inventory.end(); i++){
        if (dvd_name == i->getMovie()){
          error++;
        } //movie exists
      }

      if (error == 0){ //movie doesnt exist
        ostr<<"WARNING: No movie named "<<dvd_name<<" in the inventory"<<std::endl;
      }else {
        int available = 0;
        int total = 0; //copies available vs total amount of copies. 

        for (inventory_type::iterator i = inventory.begin(); i!=inventory.end();i++){
          if (i->getMovie()==dvd_name){
            available = i->getCount();
          } //gets count of movie from customer
        }
        for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
          list<string> films = c->getFilms();
          for (list<string>::iterator f = films.begin(); f!=films.end();f++){
            if (*f == dvd_name){ 
              total++; // gets amount of copies that exist. 
            }
          }
        }
//printing correctly
        
      ostr<<dvd_name<<':'<<std::endl;
      string copy1;
      string copy2;
      if (total ==1){
        copy1 = "copy";
      }else {
        copy1 = "copies";
      }
      if(available==1){
        copy2 = "copy";
      }
      else{ //syntax
        copy2= "copies";
      }

      if (available != 0 && total!=0 )
        ostr<<"  "<<total<<" "<<copy1<<" checked out and "<<available<<" "<<copy2<<" available"<<std::endl;
      else if(available == 0)
        ostr<<"  "<<total<<" "<<copy1<<" checked out"<<std::endl; //printing syntax
      else if (total==0)
        ostr<<"  "<<available<<" "<<copy2<<" available"<<std::endl;

      }
      
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
      


    } else if (token == "add_preference") {

      string customer_name = read_customer_name(istr);
      string dvd_name = read_dvd_name(istr);
      int error=0;
      int incurrent= 0; //warning variables

      //checks if dvd is in current list
      for (customers_type::iterator s = customers.begin(); s!=customers.end();s++){
        if (customer_name == s->getName()){
          list<string> currentlist = s->getFilms();
          for (list<string>::iterator itr = currentlist.begin(); itr != currentlist.end(); itr++){
            if (dvd_name == *itr){
              incurrent++; //movie is in the current list
            }
          }
        }
      }

      for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
        if (customer_name == c->getName()){
          list<string> preferences = c->get_preferences();
          for (list<string>::iterator p = preferences.begin(); p!=preferences.end(); p++){
            if(*p == dvd_name){
              error++; //movie in pref list
            }
          }
        }
      }
      bool exist = false;
      for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
        if (c->getName()==customer_name){
          exist = true; //person exists
        }
      }

      bool found = false;
      for (inventory_type::iterator t = inventory.begin(); t!=inventory.end();t++){
        if (dvd_name == t->getMovie()){
          found = true; //movie exists
        }
      }
      
      if (found == true && error ==0 && exist == true && incurrent == 0){ //movie exists in inventory
      //customer doesnt have already in pref list, customer exists, customer doesn't have movie in current list
        for (customers_type::iterator c = customers.begin(); c!=customers.end(); c++){
          if (customer_name == c->getName()){
            list<string> preferences = c->get_preferences();
            preferences.push_back(dvd_name);
            c->setPreferences(preferences);
            break;
          }
        }
      } else if (found == false){ //movie no exist
        ostr<<"WARNING: No movie named "<<dvd_name<< " in the inventory"<<std::endl;
      } else if (error!=0){ //movie in pref list
        ostr<<"WARNING: "<<customer_name<<" already has "<<dvd_name<<" on his/her preference list!"<<std::endl;
      }else if (exist == false){ //person no exist
        ostr<<"WARNING: No customer named "<<customer_name<<std::endl;
      } else if (incurrent != 0){ //movie in curr list
        ostr<<"WARNING: "<<customer_name<<" currently has "<<dvd_name<<"!"<<std::endl;
      }

    } else {
      ostr << "ERR: Unknown token " << token << std::endl;
      //exit(1);
    }
  }
}


// ==================================================================


// A customer name is simply two strings, first & last name
string read_customer_name(istream &istr) {
  string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
string read_dvd_name(istream &istr) {
  string token;
  istr >> token;
  assert (token[0] == '"');
  string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->getMovie() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}


// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//

void shipping_algorithm(inventory_type &inventory, customers_type &customers, ostream &ostr) {

  ostr << "Ship DVDs" << std::endl; //ostr

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //

  
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty(customer_itr->get_preferences())) {
      // move on to the next customer
      customer_itr++;
      continue;
    }
    

    // a helper flag variable
    bool sent_dvd = false;
  
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {
      
      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr); 
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 
        
        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->getName() << " receives " << *preferences_itr << std::endl;  
        inventory_itr->shipped();                         
        customer_itr->receives(*preferences_itr);//added parameter
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance

        
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);
        
        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    
    if (!sent_dvd) {
      customer_itr++;
    }
  }
}
  



// ==================================================================
