/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <algorithm>
#include <utility>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,size_t low,size_t high);
	vector<T> keys;
	vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,size_t low,size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree{
public:
BPlusTree() : root_(NULL), size_(0) {}
BPlusTree(const BPlusTree<T>& old) : size_(old.size_),b_(old.b_) {root_ = this->copy_tree(old.root_);} //need to create copy tree
BPlusTree(const int b) : size_(0), b_(b), root_(NULL){} // what do i set b to?
~BPlusTree() {this->destroy_tree(root_); } //destructor
BPlusTree& operator=(const BPlusTree<T>& old) { //copy constructor using = operator
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_);
      size_ = old.size_;
    }
    return *this;
  }

int size() const {return size_;} //returns size of tree
BPlusTreeNode<T>* find(const T& key_value) { return find(key_value, root_, b_); } //finds node of value and returns pointer to node
pair<BPlusTreeNode<T>*, bool> insert(const T& key_value) {return new_insert(key_value, root_, b_);} //Inserts value
void print_sideways(ofstream& ostr) { //prints tree sideways
	print_sideways(ostr, root_, 0);
}
void print_BFS(ofstream& ostr){ //prints breadth first 
	print_BFS(ostr, root_);
}
private:
int size_;
int b_;
BPlusTreeNode<T>* root_;

//copies tree
BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root){	
	if (old_root == NULL){//if null return null
		return NULL;
	} else {
		BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>; //create new node for new copied tree and copy values
		for (unsigned int i = 0; i < old_root->keys.size(); i++){
			new_node->keys.push_back(old_root->keys[i]);
		}
		if (old_root -> children.size() != 0){//not a  leaf.
			for (unsigned int i = 0 ; i<old_root->children.size(); i++){ 
				new_node->children.push_back(copy_tree(old_root->children[i])); // call function if there are children to go to
			}
		}else{//if leaf go back to parent. and go to another child.
			copy_tree(old_root->parent);
		}
		return new_node;
	}
}

//Destroys tree
void destroy_tree(BPlusTreeNode<T>* p){
	if (p != NULL){
		if (p->children.size() == 0){
			delete p;
		}
		else{ 
			for (unsigned int i = 0; i < p->children.size(); i++){
				destroy_tree(p->children[i]);
			}
			delete p;
		}
	}
}

//insert function
pair<BPlusTreeNode<T>*,bool> new_insert(const T& value, BPlusTreeNode<T>* p, const int b){ //value, pointer to node, degree value b
	if (size_ == 0){//if nothing
		size_++;
		p = new BPlusTreeNode<T>;
		p->keys.push_back(value);
		root_ = p;
		return pair<BPlusTreeNode<T>*,bool>(root_,true);
	}else{
		BPlusTreeNode<T>* node = find(value,root_,b); //find where value supposed to be
		node->keys.push_back(value);
		sort(node->keys.begin(), node->keys.end());
		size_++;
		if (int(node->keys.size()) >= b){//overflowed
			overflow(node,b);
		}
	}
	return pair<BPlusTreeNode<T>*,bool>(p,false);
}

//helper sorting function to sort the children.
static bool compare( BPlusTreeNode<T>*& a,  BPlusTreeNode<T>*& b){ // I need the static otherwise this sorting doesn't work. I reserached online. Stack overflow explained the use of this to me. 
	return a->keys[0] < b->keys[0]; 
}

//Basically split function. All complicated cases go here.
void overflow( BPlusTreeNode<T>* p, const int b){ //all splits go on here
	
	if (int(p -> keys.size()) >= b){ //if overflowed should always be true but just in case
		if (p == root_){ // if root
			if (root_->children.size() == 0){//root with no children 
				BPlusTreeNode<T>* first = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* second = new BPlusTreeNode<T>;
				first->parent = root_;
				second->parent = root_; // create two nodes, set the parents, and copy the data
				for (unsigned int i = 0; i < p->keys.size()/2; i++) //copy left side of vector
					first->keys.push_back(p->keys[i]);

				for (unsigned int j = p->keys.size()/2; j < p->keys.size(); j++)//copy right side of vector
					second->keys.push_back(p->keys[j]);
				
				p->keys.clear();
				p->keys.push_back(second->keys[0]);  // From my understanding just makes it first value in second vector. MIGHT BE WRONG
				sort(p->keys.begin(), p->keys.end());
				root_->children.push_back(first); //add these two nodes to children of root node.
				root_->children.push_back(second);

			}else if (int(root_->children.size()) < b){//already has children but not filled.
				cout<<"ERROR: CASE SHOULDN'T EXIST"<<std::endl;;		 
				//This case should not exist. I just had it here for debugging. Might aswell keep it.
			}else if (int(root_ ->children.size()) > b){//too many children
				BPlusTreeNode<T>* first = new BPlusTreeNode<T>;
				BPlusTreeNode<T>* second = new BPlusTreeNode<T>; //overflown children along with node. 
				first->parent = root_;//create two new nodes, set parents, and copy data
				second->parent = root_;
				for (unsigned int i = 0; i < root_->children.size()/2; i++){ //sets first half children for first node
					first->children.push_back(root_->children[i]);
					root_->children[i]->parent = first;
				}

				for (unsigned int k = root_->children.size()/2; k < root_->children.size(); k++){//sets second half children for second node
					second->children.push_back(root_->children[k]);
					root_->children[k]->parent = second;
				}
				
				//first->keys.push_back(first->children[first->children.size()-1]->keys[0]);  Same as below
				BPlusTreeNode<T>* last_child = first->children[first->children.size()-1];
				T val = last_child->keys[0];
				first->keys.push_back(val);
				//gets the last child for both nodes and pushes back to first and second node (arranging the data)
				BPlusTreeNode<T>* last_child2 = second ->children[second->children.size()-1];
				T val2 = last_child2->keys[0];
				second->keys.push_back(val2);

				//Now resetting root node. Copy, clear, and place back in
				vector<T> copy;
				for (unsigned int i = (root_->keys.size()/2) ;  i< root_->keys.size()-1; i++)
					copy.push_back(root_->keys[i]);
				root_->keys.clear();
				for (unsigned int j = 0; j<copy.size(); j++)
					root_->keys.push_back(copy[j]);
				//resetting children
				sort(root_->keys.begin(), root_->keys.end());
				root_->children.clear();
				root_->children.push_back(first); //make sure everything is sorted. then cleared. then place two new nodes created.
				root_->children.push_back(second);
			}		
		}else{ //not a root node
			BPlusTreeNode<T>* new_node = new BPlusTreeNode<T>;
			new_node->parent = p->parent;
			for (unsigned int x = 0; x< p->keys.size()/2; x++)
				new_node->keys.push_back(p->keys[x]);
			p->parent->children.push_back(new_node);
			//create one new node, add values and set parent
			vector<T> temp;
			for (unsigned int i = p->keys.size()/2; i<p->keys.size(); i++)
				temp.push_back(p->keys[i]);

			p->keys.clear();
			for (unsigned int j = 0; j < temp.size(); j++)
				p->keys.push_back(temp[j]);
			//reput in values for root node. Will most likely take in first value of second node.
			p->parent->keys.push_back(p->keys[0]);
			sort(p->parent->keys.begin(), p->parent->keys.end());
			sort(p->parent->children.begin(), p->parent->children.end(), compare); 
			
			overflow(p->parent, b);
		}
	}
}


//finds value or node value is supposed to be in
BPlusTreeNode<T>* find(const T& value, BPlusTreeNode<T>* p, const int b){
	if (!p) return NULL; //return null 
	
	if (p->children.size() == 0){//is leaf
		return p;
	}else /*if(p->children.size() != 0)*/{
		unsigned int pos = 0;
		if (p->keys.size() == 1){//corner case of where only 1 value
			if (value < p->keys[0]){
				pos = 0;
			}else{
				pos = 1;
			}
		}else {//more than one value.
 			for (unsigned int i = 0; i< (p->keys.size()-1); i++){
				if (value < p->keys[i]){
					pos = i;
					break;
				}else if (value >= p->keys[i] && value < p->keys[i+1]){
					pos = i+1;
					break;
				}else if (value >= p->keys[i+1]){
					pos=i+2;
					break;
				}
			}
		}//everything above just found the position for the value to go to. Used for children vector
		return find(value,p->children[pos],b);
	}
	
}

//prints sideways
void print_sideways(ofstream& ostr, BPlusTreeNode<T>* p, int depth) {
  if (p) {
		int size = (p->children.size()/2);
		if (size > 0){
			int i = 0;
			while (i <= size-1){ //for loop was giving seg faults could not understand why so switched to while loop with exact same restraints and it worked.
				print_sideways(ostr, p->children[i], depth+1);
				i++;
			}//top part of printing.
		}
		
		for (int i=0; i<depth; ++i) ostr << "\t";
		for (unsigned int i = 0; i < p->keys.size(); i ++){
			if (p->keys.size()-1 == i)
				ostr << p->keys[i]<<"";
			else ostr<<p->keys[i]<<",";
		}
		ostr<<"\n";
		for (unsigned int i = size; i < p->children.size(); i++)
			print_sideways(ostr, p->children[i], depth+1);//bottom part of printing

    }else{
		ostr<<"Tree is empty."<<std::endl;
	}
}


//Prints using BFS
void print_BFS(ofstream& ostr, BPlusTreeNode<T>* p){
	//done iteratively
	if (p){
		vector<BPlusTreeNode<T>*> v; 
		for (unsigned int i = 0; i < root_->keys.size(); i++){ 
			if (p->keys.size()-1 == i)
				ostr<<root_->keys[i]<<std::endl;
			else ostr<<p->keys[i]<<",";
		}
		for(unsigned int i = 0; i < root_->children.size(); i++){
			v.push_back(root_->children[i]);
		}// v should contain all children of root node
		while (v.size() != 0){
			for (unsigned int i =0; i < v.size(); i++){
				for (unsigned int j = 0 ; j< v[i]->keys.size(); j++){
					if (v[i]->keys.size()-1 == j){
						if(i!=v.size()-1) ostr<<v[i]->keys[j]<<"\t";
						else ostr<<v[i]->keys[j];
					}else ostr<<v[i]->keys[j]<<",";
				}
			}//couts all values in the children.
			
			vector<BPlusTreeNode<T>*> temp;//temporary vector that takes in all children for next function call
			for (unsigned int i = 0; i < v.size(); i++){
					for (unsigned int j = 0; j < v[i]->children.size(); j++){
						temp.push_back(v[i]->children[j]);
					}
				
			}
			v = temp;//set v to contain all the children of the node to go and print next function call
			ostr<<std::endl;
		}
	}else ostr<<"Tree is empty."<<std::endl;	
}

};


#endif
