#ifndef hash_table_
#define hash_table_

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

//Keytype:  pair<string, vector<int> > 
template <class KeyType>//, class HashFunc>
class Hash_Table{
public:
    Hash_Table(unsigned int s) : table(s),sizem(0) {} //
    Hash_Table(const Hash_Table<KeyType>& old) : table(old.table), sizem(old.sizem) {}
    ~Hash_Table() {}

    unsigned int size() const {return sizem;}
    typedef typename vector<pair<string, vector<int> > >::iterator hash_itr;
    class iterator{
    public:
        friend class Hash_Table;
    private:
        Hash_Table* m_hs;
        int m_index;
        hash_itr it;
        iterator (Hash_Table* hs) : m_hs(hs), m_index(-1) {}
        iterator (Hash_Table* hs, int index) : m_hs(hs), m_index(index) {}
    public:
        iterator() : m_hs(0), m_index(-1) {}
        iterator(iterator const& itr) : m_hs(itr.m_hs), m_index(itr.m_index) {}

        iterator& operator=(const iterator& old){
            m_hs = old.m_hs;
            m_index = old.m_index;
            return *this;
        }

        const KeyType& operator*() const {return *it;}

        iterator& operator++() { 
            this->next();
            return *this;
        }
        iterator operator++(int) {
            iterator temp(*this);
            this->next();
            return temp;
        }
        iterator & operator--() { 
            this->prev();
            return *this;
        }
        iterator operator--(int) {
            iterator temp(*this);
            this->prev();
            return temp;
        }


        friend bool operator== (const iterator& lft, const iterator& rgt)
        { return lft.m_hs == rgt.m_hs && lft.m_index == rgt.m_index && 
        (lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr); }

        friend bool operator!= (const iterator& lft, const iterator& rgt)
        { return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index || 
        (lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr); }

    private: 
        void next(){
            it++;
            if(it == m_hs->table.end()){
                //i want to go to next vector index where there is a non empty pair.
                for (++m_index; m_index < int(m_hs->table.size()) && m_hs->table[m_index].empty(); ++m_index) {}

                if (m_index != int(m_hs->m_table.size()))
                    it = m_hs->m_table[m_index].begin();
                else m_index = -1;
            }
        }

        void prev(){
            it--;
             if (it != m_hs->m_table[m_index].begin())
	            it -- ;
            else {
                // Otherwise, back down the table until the previous
                // non-empty list in the table is found
                for (--m_index; m_index >= 0 && m_hs->table[m_index].empty(); --m_index) {}
                // Go to the last entry in the list.
                it = m_hs->m_table[m_index].begin();
                hash_itr p = it; ++p;
                for (; p != m_hs->table[m_index].end(); ++p, ++it) {}
            }
        }
    };
    //INSERT
    pair< iterator, bool > insert(const pair<string, int >& p){ 
        const int OCCUPANCY = sizem/table.size();
        if (sizem >= OCCUPANCY*table.size())
            this->resize_table(2*table.size()+1);

        unsigned int hash_pos = hash_function(p.first);

        vector<pair<string,vector<int> > >::iterator itr = find_if(table.begin(), table.end(), compare); //compare may not work
        cout<<itr->first<<std::endl;
       /* if (itr){
            *itr.second.push_back(p.second); //adds position to pos vector
            iterator h_itr(this, hash_pos, p);
            return make_pair(h_itr, false);
        }else{//not found
            if (table[hash_pos]){//A different pair is at this position
                //Linear Probing
                int i = 1;
                while (!table[hash_pos+i]){//find open space
                    i++;
                }
                KeyType temp;
                temp.second.push_back(p.second);
                temp.first = p.first;
                table[hash_pos+i] = temp;
                sizem++;
                iterator h_itr(this, hash_pos, p);
                return make_pair(h_itr,true);
            }else{//No pair already exists
                KeyType temp;
                temp.second.push_back(p.second);
                temp.first = p.first;
                //table.push_back(temp); //can't do this right?  BELOW instead.
                table[hash_pos] = temp;
                sizem++;
                iterator h_itr(this, hash_pos, p);
                return make_pair(h_itr, true);
            }
        }*/
    }
    

    //FIND
    iterator find(string& seq){
        vector<pair<string,vector<int> > >::iterator itr = find(table.begin(), table.end(), compare); //compare may not work
        return itr;
        /*int pos = hash_function(seq);
        table[pos];*/
    }

    void print(){
        for (unsigned int i  = 0 ; i < table.size() ; i++){
            cout<<std::endl;
        }
    }

private:
    vector<KeyType> table;
    //HashFunc hash;
    unsigned int sizem;

    int hash_function(string key){
        int val = 0;
        for (int i = 0; i < key.size(); i++){
            if (key[i] == 'A'){
                val += (2*val)*i;
            }else if (key[i] == 'T'){
                val += (3*val)*i;
            }else if (key[i] == 'C'){
                val += (4*val)*i;
            }else if (key[i] == 'G'){
                val += (5*val)*i;
            }else cerr<<"Not a genome letter"<<std::endl;
        }
        return val % sizem;
    }

    void resize_table(unsigned int new_size){

    }

    bool compare(const KeyType& a){
        return a.first == this.first;
    }
    
};


#endif



/*typedef typename std::list<KeyType>::iterator hash_list_itr;
    class iterator{
    public:
        friend class Hash_Table;   // allows access to private variables
    private:
    // ITERATOR REPRESENTATION
        Hash_Table* m_hs;          
        int m_index;               // current index in the hash table
        hash_list_itr m_list_itr;  // current iterator at the current index

    private:
        // private constructors for use by the Hash_Table only
        iterator(Hash_Table * hs) : m_hs(hs), m_index(-1) {}
        iterator(Hash_Table* hs, int index, hash_list_itr loc) : m_hs(hs), m_index(index), m_list_itr(loc) {}

    public:
    // Ordinary constructors & assignment operator
        iterator() : m_hs(0), m_index(-1)  {}
        iterator(iterator const& itr): m_hs(itr.m_hs), m_index(itr.m_index), m_list_itr(itr.m_list_itr) {}
        iterator&  operator=(const iterator& old) {
            m_hs = old.m_hs;
            m_index = old.m_index; 
            m_list_itr = old.m_list_itr;
            return *this;
        }

    // The dereference operator need only worry about the current
    // list iterator, and does not need to check the current index.
        const KeyType& operator*() const { return *m_list_itr; }

    // The comparison operators must account for the list iterators
    // being unassigned at the end.
        friend bool operator== (const iterator& lft, const iterator& rgt)
        { return lft.m_hs == rgt.m_hs && lft.m_index == rgt.m_index && 
        (lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr); }
        friend bool operator!= (const iterator& lft, const iterator& rgt)
        { return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index || 
        (lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr); }

    // increment and decrement
        iterator& operator++() { 
            this->next();
            return *this;
        }
        iterator operator++(int) {
            iterator temp(*this);
            this->next();
            return temp;
        }
        iterator & operator--() { 
            this->prev();
            return *this;
        }
        iterator operator--(int) {
            iterator temp(*this);
            this->prev();
            return temp;
        }

        private:
        // Find the next entry in the table
            void next() {
                ++ m_list_itr;  // next item in the list

      // If we are at the end of this list
                if (m_list_itr == m_hs->table[m_index].end()) {
                // Find the next non-empty list in the table
                    for (++m_index; m_index < int(m_hs->table.size()) && m_hs->table[m_index].empty(); ++m_index) {}
                    // If one is found, assign the m_list_itr to the start
                    if (m_index != int(m_hs->table.size()))
                        m_list_itr = m_hs->table[m_index].begin();
                    else m_index = -1;
                }
        }

    // Find the previous entry in the table
        void prev() {
        // If we aren't at the start of the current list, just decrement
        // the list iterator
            if (m_list_itr != m_hs->table[m_index].begin())
                m_list_itr -- ;
            else{
            // Otherwise, back down the table until the previous
            // non-empty list in the table is found
                for (--m_index; m_index >= 0 && m_hs->table[m_index].empty(); --m_index) {}
                // Go to the last entry in the list.
                m_list_itr = m_hs->table[m_index].begin();
                hash_list_itr p = m_list_itr; ++p;
                for (; p != m_hs->table[m_index].end(); ++p, ++m_list_itr) {}
            }
        }
    
    };
*/