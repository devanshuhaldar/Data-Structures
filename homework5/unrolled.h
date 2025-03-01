//Unrolled.h file for main.cpp
#ifndef unrolled_h_
#define unrolled_h_

#include <cassert>
#include <cstddef>
#include <ostream>
#include <iostream>

using namespace std;

const int NUM_ELEMENTS_PER_NODE = 6;

//class Node
template <class T>
class Node{
public:
    Node<T>* next_;
    Node<T>* prev_;

    //variables
    T elements_[NUM_ELEMENTS_PER_NODE];
    unsigned int num_elements_;

    Node() : next_(NULL), prev_(NULL), num_elements_(0) {}
    //Node(T arr[NUM_ELEMENTS_PER_NODE]) :  next_(NULL),prev_(NULL), num_elements_(NUM_ELEMENTS_PER_NODE), elements_(arr){}
    Node(T arr[],unsigned int s){
        
        next_ = NULL;
        prev_ = NULL;
        num_elements_ = s;
        for (unsigned int i = 0; i < NUM_ELEMENTS_PER_NODE; i++){
            elements_[i] = arr[i];
        }
    }

    
};

template <class T> class UnrolledLL;

//class list_iterator
template <class T>
class list_iterator{
public:
    list_iterator() : ptr_(NULL), offset_(0) {}  //create list iterator with no specification. Below is with specification.
    list_iterator(Node<T>* p,unsigned int o) : ptr_(p),offset_(o) {}
    list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_),offset_(old.offset_) {}
    list_iterator<T>& operator=(const list_iterator<T>& old) { //comparing with list iterator
    ptr_ = old.ptr_, offset_=old.offset_;  return *this; }
    ~list_iterator() {}

    T& operator*()  { return ptr_->elements_[offset_];}//ptr_->elements_;  }

   // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
      if(offset_==ptr_->num_elements_-1){ //if done with array, move to next node.
          ptr_=ptr_->next_;
          offset_=0;  //when you move to next node reset to first position in array.
      }
      else { 
          offset_++;
      }
      return *this;
    }
    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
      list_iterator<T> temp(*this);
      if(offset_==ptr_->num_elements_-1){
          ptr_=ptr_->next_;
          offset_=0; //same thing as said above.
      }
      else { 
          offset_++;
      }
      return temp;
    }

    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
      if (offset_==0){ //at beginning of array. move to previous NODE.
        ptr_=ptr_->prev_; 
        offset_=ptr_->prev_->num_elements_-1;
      }
      else { 
          offset_--; //move backwards regularly
      }
      return *this;
    }
    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
      list_iterator<T> temp(*this);
      if(offset_ == 0){
        ptr_=ptr_->prev_;
        offset_=ptr_->prev_->num_elements_-1;
      }    //same as said above.
      else { 
        offset_--;
      }
      return temp;
    }
   // the UnrolledLL class needs access to the private ptr_ member variable
    friend class UnrolledLL<T>;

  // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
     return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator<T>& r) const {
     return ptr_ != r.ptr_; }
private:
    Node<T>* ptr_;
    unsigned int offset_;  //iterator variables.
};


//unrolledLL class
template <class T>
class UnrolledLL {
public:
    UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {} //regular constructor
    UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old); } // copy constructor.
    UnrolledLL& operator= (const UnrolledLL<T>& old); //assignment operator.
    ~UnrolledLL() { this->destroy_list(); } //destructor.

    unsigned int size() const { return size_; } //i think this should be good? 
    bool empty() const { return head_ == NULL; } //empty node
    void clear() { this->destroy_list(); } //clears unrolledLL

    // read/write access to contents
    const T& front() const { return head_->elements_[0];  } //use these functions when size is 0. Should cause error. 
    T& front() { return head_->elements_[0]; }              //can move these return statements seperately down below.
    const T& back() const { return tail_->elements_[tail_->num_elements_-1]; }
    T& back() { return tail_->elements_[tail_->num_elements_-1]; } //takes last element in last node.

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();  //declaring all functions.
    void push_back(const T& v);
    void pop_back();
    void print(ostream& out);

    typedef list_iterator<T> iterator;
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_,0); } //returns first position for the iterator.
    iterator end() { return iterator(NULL,0); } //returns last position for iterator. 


private: 
    void copy_list(const UnrolledLL<T>& old);  //copy list.
    void destroy_list();  //destroys list

    Node<T>* head_; //member variables.
    Node<T>* tail_;
    unsigned int size_;
};


//IMPLEMENTATION =======================================================================================================================
//size,front,back,push_back,pop_back,push_front,pop_front,erase,insert
template <class T>
//=
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);  
  }
  return *this;
}
//==
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}
//!=
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }

//FUNCTION IMPLEMENTATIONS===============================================================================================================

/*template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::size(iterator itr){     

}*/


template <class T>
void UnrolledLL<T>::push_front(const T& v) {
    ++size_; //adding element so increase size
    if(head_){ //if not null
        if(head_->num_elements_!=NUM_ELEMENTS_PER_NODE){ //node is not full
            T arr[NUM_ELEMENTS_PER_NODE]; //create brand new array
            for (unsigned int i = 0; i < head_->num_elements_;i++){
                arr[i+1] = head_->elements_[i];
            }
            arr[0] = v; //put elements from this array back into the node array.
            for (unsigned int j = 0; j< head_->num_elements_+1; j++){
                head_->elements_[j] = arr[j];
            }
            head_->num_elements_++;
        }else{ //node is full, make new one
            Node<T>* newp = new Node<T>(); //makes new node and sets pointers correctly
            head_->prev_=newp;
            newp->next_ = head_;
            head_=newp;
            head_->elements_[0]=v;
            head_->num_elements_++;
        }
    }else{ //if null create new node.
        Node<T>* newp = new Node<T>();
        tail_=head_=newp;
        head_->elements_[0]=v;
        head_->num_elements_++; 
    }
}


template <class T>
void UnrolledLL<T>::pop_front() {
    --size_;
    if(head_){//not null  (pointing to something)
        if(head_->num_elements_ == 1){ //need to remove the NODE
            Node<T>* temp = head_;
            if (head_->next_){//not null
                head_->next_->prev_=NULL;
            }
            //delete head_;
            head_ = head_->next_;
            delete temp;
        }
        else{ // more than one element in the node.
            T arr[NUM_ELEMENTS_PER_NODE];
            for (unsigned int i =0; i < head_->num_elements_-1; i++){
                arr[i] = head_->elements_[i+1];
            } //makes a copy array with no last element.
            for (unsigned int j = 0; j <NUM_ELEMENTS_PER_NODE;j++){
                head_->elements_[j]=arr[j];
            }
            head_->num_elements_--;
        }
    }else{
        cout<<"Cannot remove something that doesn't exist."<<std::endl;
        exit(1);
    }
}


template <class T>
void UnrolledLL<T>::push_back(const T& v) {
    ++size_;
    if (tail_){//if not null
        if (tail_->num_elements_!= NUM_ELEMENTS_PER_NODE){//if node is not full
            tail_->elements_[tail_->num_elements_] = v;
            tail_->num_elements_++;
        }
        else { // node is full 
            Node<T>* newp = new Node<T>(); //create new node. set pointers.
            tail_->next_=newp;
            newp->prev_ = tail_;
            tail_=newp; 
            tail_->elements_[0]=v;
            tail_->num_elements_++;
        }
    }else{
        Node<T>* newp = new Node<T>();
        head_ = tail_ = newp; //null so create new node.
        head_->elements_[0]=v;
        head_->num_elements_++;
    }
    
}


template <class T>
void UnrolledLL<T>::pop_back() {
    --size_;
    if(tail_){//not null  (pointing to something)
        if(tail_->num_elements_ == 1){ //need to remove the NODE
            Node<T>* temp = tail_;
            if (tail_->prev_){//not null
                tail_->prev_->next_=NULL;
            }
            tail_ = tail_->prev_;
            delete temp;
        }
        else{ // more than one element in the node.
            T arr[NUM_ELEMENTS_PER_NODE];
            for (unsigned int i = 0; i < tail_->num_elements_-1; i++){
                arr[i] = tail_->elements_[i];
            } //makes a copy array with no last element.
            for (unsigned int j  = 0 ; j  < NUM_ELEMENTS_PER_NODE; j++){
                tail_->elements_[j] = arr[j];
            }
            tail_->num_elements_--;
        }
    }else{
        cout<<"cannot pop something when no elements exist"<<std::endl;
        exit(1);
    }
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert(size_>0);
  --size_;
if (size_==0){ //if size equals 0. Just incase. 
    head_ = NULL;
    tail_ = NULL;
    iterator final(NULL,0);
    return final;
}
if (itr.ptr_!=NULL){
    if (itr.ptr_->num_elements_==1){ //delete node. and move to next node.
        if(itr.ptr_ == head_ && itr.ptr_==tail_){ //deletes a last node.
            head_ = NULL;
            tail_ = NULL;
            iterator final(itr.ptr_->next_,itr.offset_);
            delete itr.ptr_;
            return final; 
        }
        else if (itr.ptr_ == head_){ //deletes head node.
            head_->next_->prev_= NULL;
            head_ = itr.ptr_->next_;
            iterator final(head_,itr.offset_);
            delete itr.ptr_;
            return final;
 
        }else if (itr.ptr_== tail_){ //deletes last node.
            tail_->prev_->next_ = NULL;
            tail_ = itr.ptr_->prev_;
            iterator final(itr.ptr_->prev_,itr.offset_);
            delete itr.ptr_;
            return final;

        }else{ //deletes node in the middle of the UNROLLEDLL list
            itr.ptr_->prev_->next_ = itr.ptr_->next_;
            itr.ptr_->next_->prev_ = itr.ptr_->prev_;
            iterator final(itr.ptr_->next_,itr.offset_);
            delete itr.ptr_; //delets ptr.
            return final;
        }
    }else{ //stay at same node. remove element.       
        for (unsigned int i = itr.offset_; i < itr.ptr_->num_elements_-1; i++){
                itr.ptr_->elements_[i] = itr.ptr_->elements_[i+1];
            }
            itr.ptr_->elements_[itr.ptr_->num_elements_-1] = {};
            itr.ptr_->num_elements_--;

            if (itr.offset_==itr.ptr_->num_elements_){
                iterator final(itr.ptr_->next_,0);
                return final;
            }else{
                iterator final(itr.ptr_,itr.offset_);
                return final;
            }
        }
  
    }
    iterator final(NULL,0); //return NULL, shouldn't end up here but just incase.
    return final;
}



template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_;
  if (itr.ptr_->num_elements_ < NUM_ELEMENTS_PER_NODE){//overfilled array
    T arr[NUM_ELEMENTS_PER_NODE];
    for (unsigned int i = itr.offset_+1; i < itr.ptr_->num_elements_+1; i++){
        arr[i] = itr.ptr_->elements_[i-1];
    } //creates new array
    arr[itr.offset_]=v;
    for (unsigned int i = itr.offset_; i < itr.ptr_->num_elements_+1; i++){
        itr.ptr_->elements_[i]=arr[i];
    }//puts values of the array back into the array in the elements

    itr.ptr_->num_elements_++; //increases size of array. value
    if (itr.ptr_->num_elements_-1==itr.offset_){ //-1
        iterator result(itr.ptr_->next_,0); //last position in array. move to next node.
        return result;
    }else{
        iterator result(itr.ptr_, itr.offset_);//stay at this node. more elements left for iterator to go through.
        return result;
    }
  }else{
      //create new node and split.
    Node<T>* temp = new Node<T>; //new node.
    T old_array[NUM_ELEMENTS_PER_NODE]; //old array. 
    T new_array[NUM_ELEMENTS_PER_NODE]; //new array.
    unsigned int old_count = 1;
    unsigned int new_count = 0;

    //create old array
    for (unsigned int i = 0; i < itr.offset_; i++){
        old_array[i] = itr.ptr_->elements_[i];
        old_count++;
    }
    old_array[itr.offset_] = v; // create array for old node. Contains all elements from start up to insert position.

    //create new array. Contains all elements after insertion position to end.
    for (unsigned int j = 0; j< NUM_ELEMENTS_PER_NODE-itr.offset_; j++){
        new_array[j] = itr.ptr_->elements_[j+itr.offset_];
        new_count++; 
    }

    //copy old array back into itr.ptr
    for (unsigned int i =0; i < old_count; i++){
        itr.ptr_->elements_[i] = old_array[i];
    }
    //copy new array into temp node.
    for (unsigned int i = 0; i< new_count; i++){
        temp->elements_[i] = new_array[i];
    }
    temp->elements_.insert()
    temp->num_elements_ = new_count; //update counts.
    itr.ptr_->num_elements_ = old_count;

    if (itr.ptr_==tail_) {
        itr.ptr_->next_ = temp;
        temp->prev_ = itr.ptr_;
        temp->next_ = NULL; //if it is the end.  
        tail_ = temp;
    } else{
        itr.ptr_->next_->prev_ = temp; //normal node. 
        temp->next_ = itr.ptr_->next_;
        itr.ptr_->next_=temp;
        temp->prev_ = itr.ptr_;
    }
    iterator result(itr.ptr_->next_,0); //move to next node.
    return result;
  }
//NULL.
    iterator result(NULL,0);
    return result;
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
    size_ = old.size_;
    if (size_==0){
        head_=tail_=0; //copies list. 
        return;
    }
    head_ = new Node<T>(old.head_->elements_,old.head_->num_elements_);
    tail_=head_;
    Node<T>* old_p = old.head_->next_;  
    while (old_p) {
        tail_->next_ = new Node<T>(old_p->elements_,old_p->num_elements_);
        tail_->next_->prev_ = tail_; //changing pointers.
        tail_ = tail_->next_;
        old_p = old_p->next_;
    }
}


template <class T>
void UnrolledLL<T>::destroy_list() {    
    while(tail_!=head_){ //starts from back and goes to front. deleting all nodes.
        Node<T>* temp = tail_;
        tail_= tail_->prev_;
        tail_->next_ = NULL;
        delete temp;
    }
    Node<T>* temp = head_;
    head_=NULL; //deletes last node.
    tail_=NULL;
    if (temp) // if not null 
        delete temp;
}

template <class T>
void UnrolledLL<T>::print(ostream& out){
    out<<"UnrolledLL, size: "<<size_<<std::endl;
    Node<T>* temp = head_;
    while (temp->next_!=NULL){
        out<<"node: ["<<temp->num_elements_<<"]";
        for (unsigned int i = 0; i < temp->num_elements_; i++){
            out<<" "<<temp->elements_[i];
        }
        out<<std::endl;
        temp = temp->next_;
    }
    out<<"node: ["<<tail_->num_elements_<<"]";
    for (unsigned int i = 0; i< tail_->num_elements_;i++){
        out<<" "<<tail_->elements_[i];
    }
    out<<std::endl;
}
#endif

