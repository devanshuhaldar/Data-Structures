#ifndef _cus_h
#define _cus_h
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Customer{
public:
    Customer();
    Customer(const string& first_, const string& last_);

    const string getFirst() const; //gets first and last name
    const string getLast() const;
    
    void setFirst(const string& first_);
    void setLast(const string& last_);

private:
    string first;
    string last;
};

bool operator<(const Customer& a, const Customer& b); //helps with map sorting.
bool operator==(const Customer& a, const Customer& b); //helps with find function

#endif
