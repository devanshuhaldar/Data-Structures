//header file for jagged array class
//Homework 3 memory debugging
#ifndef jagged_array_h_
#define jagged_array_h_
using namespace std;

template <class T> class JaggedArray{
public:
    typedef unsigned int size_type;
    //CONSTRUCTOR, ASSIGN OPERATOR, DESTRUCTOR
    JaggedArray() {this-> create();}
    JaggedArray(size_type n) {this-> create(n);}
    JaggedArray( JaggedArray& ja) {copy(ja);}
    JaggedArray& operator=(JaggedArray& ja);
    ~JaggedArray() {
        if (isPacked()==false){ //destructor
            for (unsigned int i = 0; i<numbins_; i++){
                delete [] unpackedvalues_[i];
            } 
            delete [] unpackedvalues_;  
            delete [] count_;  
        }else{
            delete [] packedvalues_;
            delete [] offsets_;     
        } 
     };  //
    //MEMBER FUNCTIONS
    void clear(); //clear

    size_type numBins() const {return numbins_;}
    void print();
 // member functions public
    T getElement(size_type x, size_type y); 
    size_type numElements() const {return numelements_;} 
    bool isPacked();
    void addElement(size_type pos, T t );
    unsigned int numElementsInBin(size_type pos); 
    void removeElement(size_type x, size_type y);

    void pack();
    void unpack();
private:
    //PRIVATE MEMBER FUNCTIONS
    void create();
    void create(size_type n);   //functions should help with above. first part
    void copy(JaggedArray<T>& a);
    //PRIVATE VARIABLES/REPRESENTATIONS
    size_type numelements_;
    size_type numbins_;
    size_type* count_;    
    T** unpackedvalues_; 
    size_type* offsets_;
    T* packedvalues_;

    
};
//empty jagged array created
template <class T> void JaggedArray<T>::create(){
    numelements_ = 0;
    numbins_ = 0;
    count_ = NULL;
    unpackedvalues_ =NULL;
    offsets_ = NULL;
    packedvalues_ = NULL;
}

//Creates jaggedarray with integer included
template <class T> void JaggedArray<T>::create(size_type n){
    numbins_ = n;
    //start out not packed
    numelements_ = 0; 
    offsets_ = NULL;
    packedvalues_ = NULL;
    count_ = new size_type[n];  
    unpackedvalues_ = new T*[n]; 
    for (size_type i =0; i < n; i++){  // sets values to 0 and unpacked pointers to null.
        count_[i] = 0;
        unpackedvalues_[i]= NULL;
    }  
}

//clears jagged array
template <class T> void JaggedArray<T>::clear(){
    if (isPacked()==false){//unpacked
        for (size_type i =0; i < numbins_; i++){
            //delete [] count_;
            count_[i]=0;
            delete [] unpackedvalues_[i];
            unpackedvalues_[i]=NULL;
        }
    }else { //packed
        for (size_type i =0; i < numbins_; i++){
            delete [] offsets_;
            offsets_[i]=0;
            delete [] packedvalues_; //deletes and creates new values
            packedvalues_[i]=0;
        }
    }
    numelements_=0;
}

//avoids duplicating when copying 
template <class T> JaggedArray<T>& JaggedArray<T>::operator=(JaggedArray<T>& ja){
    if (this != &ja){
        delete [] count_;
        delete [] packedvalues_; 
        delete [] offsets_; 
        for (size_type i = 0; i < numbins_; i++){
         delete [] unpackedvalues_[i];
        }
        delete [] unpackedvalues_;
        this-> copy(ja); //delete everything than call copy constructor.
    }
    return *this;
}

// copy constructor.
template <class T> void JaggedArray<T>::copy(JaggedArray<T>& ja){
    this->numelements_ = ja.numelements_;
    this->numbins_ = ja.numbins_;
    if (ja.isPacked()==false){
        this->unpackedvalues_ = new T*[this->numbins_];
        for (size_type i = 0; i < this->numbins_; i++){
            this->unpackedvalues_[i] = NULL;
        }
        this->count_ = new size_type[this->numbins_];
        for (size_type i = 0; i <this->numbins_; i++){
            this->count_[i] = ja.count_[i];   //creates this count _ [i]
        }
        for (size_type i = 0; i<this->numbins_; i++){
            //this-> count_[i]= ja.count_[i];
            if (this-> count_[i]!=0){
                this-> unpackedvalues_[i] = new T[this->count_[i]];
                for (size_type j = 0; j< this-> count_[i]; j++){
                    this->unpackedvalues_[i][j] = ja.unpackedvalues_[i][j];
                } 
            }
        }
        this-> offsets_ = NULL;
        this-> packedvalues_ =NULL; //set these values to null because you are unpacked.
    } else {
        this->packedvalues_ = new T [this-> numelements_];
        this->offsets_ = new size_type [this-> numbins_];
        for (size_type i = 0; i < this->numbins_; i++){
            this-> offsets_[i]=ja.offsets_[i]; 
        } 
        this->unpackedvalues_=NULL; //null because packed
        for (size_type j = 0; j < this-> numelements_;j++){
            this-> packedvalues_[j]=ja.packedvalues_[j];
        }
        this-> count_ = NULL; //value is null because packed.
    }

}

//Unpacking from packed jagged array
template <class T> void JaggedArray<T>::unpack(){
    size_type index = -1;
    unpackedvalues_ = new T*[numbins_];
    count_ = new size_type[numbins_];  //redclaring pointers and variables.
    for (size_type i = 0; i < numbins_-1; i++){
        count_[i] = offsets_[i+1]-offsets_[i];
    }
    count_[numbins_-1] = numelements_-offsets_[numelements_-1];  // count should work from this .
    for (size_type i = 0; i < numbins_; i ++){
        size_type count = count_[i];
        if (count != 0) {
            unpackedvalues_[i] = new T[count]; 
            for (size_type j = 0; j<count; j++){
                index++;
                unpackedvalues_[i][j]=packedvalues_[index];//position
            }
        }
        else unpackedvalues_[i]=NULL;
    } 
    delete [] offsets_;
    offsets_=NULL; //deleting and making variables to null because of it being unpacked now.
    delete [] packedvalues_;
    packedvalues_ = NULL; //set these 2 null at the end. once you have copied the data into unpacked.
}

//Pack function. pack from unpacked
template <class T> void JaggedArray<T>::pack(){
    packedvalues_ = new T[numelements_];
    offsets_ = new size_type[numbins_]; 
    size_type counter = 0;
    for (size_type i = 0; i<numbins_; i++){ //goes through values and makes them 0.
        if (i==0){
            offsets_[i] =0; 
        }else{ //makes values correspond with count_. 
            if (count_[i-1]!=0){
                counter+= count_[i-1];
            }
            offsets_[i] = counter;
        }
    }
    //create packedvalues array

    size_type c= 0;
    for (size_type i = 0 ; i < numbins_; i++){
        size_type count = count_[i];
        if (unpackedvalues_[i]!=0){
            for (size_type j = 0; j<count;j++){
                for (size_type z= c; z<numelements_; z++){ //basically knows how to order the values in unpacked to packed.
                    packedvalues_[z]= unpackedvalues_[i][j]; //c trackes the position in.
                    break;
                }
                c++;
            }
        }
    } 
    //same issue with unpack()
    delete [] count_;
    count_ = NULL;
    for (size_type i = 0; i < numbins_; i++)
        delete [] unpackedvalues_[i];
    delete [] unpackedvalues_;
    unpackedvalues_ = NULL; //delete and set to null because it is now packed.
    

}
//get element from either packed or unpacked.
template <class T> T JaggedArray<T>::getElement(size_type y, size_type x){
    if (y<0 || x<0 || y>numbins_ ){
        cerr<<"y or x is below 0 not valid"<<std::endl;
        exit(1); // error check
    }
    if (isPacked() == false)
     return unpackedvalues_[y][x];   //return val for unpacked
    else {  
        if ((y+1) == numbins_){ //return val for packed
            size_type z= numelements_ - offsets_[y]; // grabs value from packedvalues not unpacked.
            return packedvalues_[numelements_-z+x];
        } else {
            size_type z = offsets_[y+1]-offsets_[y];
            return packedvalues_[offsets_[y+1]-z+x]; 
        }
        
    }
}

//returns number of elements in specific bin. 
template <class T> unsigned int JaggedArray<T>::numElementsInBin(size_type pos){
    if (pos<0 || pos>numbins_){
        cerr<<"Pos < 0 not valid"<<std::endl;
        exit(1);
    }
    if (isPacked()==false){
        return count_[pos];    // just returns value of count because count updated everytime elements are added to a bin
    } else {
        if (pos == numelements_ || pos+1 == numbins_){ //last case scenario. 
            return (numelements_-offsets_[pos]);
        }
        else return (offsets_[pos+1]-offsets_[pos]);
    }

}


//adds element to unpacked. PACKED CANNOT ACCESS
template <class T> void JaggedArray<T>::addElement(size_type pos, T t){
    if (pos<0 || pos>numbins_ || isPacked() == true){
        cerr<<"Pos value not applicable either less than 0 or greater than numbins. And/or attempting to add element while packed."<<std::endl;
        exit(1); //error check
    }
    if (isPacked()==false){ //unpacked
        numelements_++; 
        size_type og_count = count_[pos];
        count_[pos]+=1; 
        size_type new_count = count_[pos];
        T *arr = new T[new_count];
        for (size_type i =0; i < og_count; i++){ //copying old data
            arr[i] = unpackedvalues_[pos][i];  
        }
        arr[og_count]=t;
        delete [] unpackedvalues_[pos];
        unpackedvalues_[pos] = arr; 
    }
} 

// removes element. PACKED CANNOT ACCESS
template <class T> void JaggedArray<T>::removeElement(size_type y, size_type x){
    numelements_--;
    if (isPacked()==true || y< 0 || x < 0|| y>numbins_){
        cerr<<"Did not remove element. Cannot remove element when packed. And/or x or y value is less than or too big of a value."<<std::endl;
        exit(1);
    }
    if (isPacked() == false){
        size_type og_count = count_[y];
        count_[y]-=1; 
        size_type new_count = count_[y];
        T *arr = new T[new_count];
        for (size_type i =0; i<og_count ; i++){
            if (x != i){
                if (i>x){
                    arr[i-1]=unpackedvalues_[y][i]; //need to shorten array size then copy data excluding 
                    //the one position the val is trying to be removed .
                }else {
                    arr[i]=unpackedvalues_[y][i];
                }
            } 
        }
        delete [] unpackedvalues_[y];
        unpackedvalues_[y] = arr;
    } 
}
//print function
template <class T> void JaggedArray<T>::print(){
    cout<<"------------------------------------------------------------------------"<<std::endl;
    cout<<"Num Bins: "<<numbins_<<std::endl;
    cout<<"Num Elements: "<<numelements_<<std::endl;
    
    if (isPacked()==false){//counts
        cout<<"Counts:"<<std::endl;
        for (size_type i = 0; i<numbins_; i ++){
            cout<<count_[i]<<" ";
        }
        cout<<""<<std::endl;
        cout<<"Unpacked Values:"<<std::endl;//unpacked values
        for (size_type i = 0; i< numbins_; i++){
            size_type count = count_[i];
            
            for (size_type j = 0; j < count; j++){ 
                cout<<unpackedvalues_[i][j]<<" ";
            }
            cout<<""<<std::endl;
        }
        cout<<""<<std::endl;
        cout<<""<<std::endl;
    }
    if (isPacked() == true){
        cout<<"Offsets:"<<std::endl; //offsets
        for (size_type i = 0; i < numbins_; i++){
            cout<<offsets_[i]<<" ";
        }
        cout<<""<<std::endl;
        cout<<"Packed Values:"<<std::endl; //packedvalues
        for(size_type i= 0; i< numelements_; i++){
            cout<<packedvalues_[i]<<" ";
        }
        cout<<""<<std::endl;
    }
    cout<<"------------------------------------------------------------------------"<<std::endl; // helps make it clear everytime u print
}
template <class T>  bool JaggedArray<T>::isPacked(){
    if (count_ == NULL){
        return true; //if packed return true else false
    }
    else return false;
}

#endif