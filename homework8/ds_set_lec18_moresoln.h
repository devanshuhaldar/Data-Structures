// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL)/*, parent(NULL)*/ {}
  TreeNode(const T& init) : value(init), left(NULL), right(NULL)/*, parent(NULL)*/ {}
  T value;
  TreeNode* left;
  TreeNode* right;
  // one way to allow implementation of iterator increment & decrement
  // TreeNode* parent;
};

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
public:
  tree_iterator() : ptr_(NULL) {}
  tree_iterator(TreeNode<T>* p) : ptr_(p) {}
  tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
  ~tree_iterator() {}
  tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const T& operator*() const { return ptr_->value; }
  // comparions operators are straightforward
  bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
  // increment & decrement operators
  tree_iterator<T> & operator++() { /* discussed & implemented in Lecture 18 */
    // if i have right subtree, find left most element of those
    if (ptr_->right_ != NULL) {
      ptr_ = ptr_->right_;
      while (ptr_->left != NULL) {
        ptr_ = ptr_->left_;
      }
    } else {
      //TreeNode<T> *tmp = ptr_;
      // Keep going up as long as I'm my parent's right child
      //while (tmp->value < value ) {
      while (ptr_->parent_->right == ptr_) 
        ptr_ = ptr_->parent_;
      }
      // Go up one more time
      ptr_ = ptr->parent;
    }




    return *this;
  }
  tree_iterator<T> operator++(int) {  tree_iterator<T> temp(*this);  ++(*this);  return temp;  }
  tree_iterator<T> & operator--() { /* implementation omitted */ }
  tree_iterator<T> operator--(int) {  tree_iterator<T> temp(*this);  --(*this);  return temp;  }

private:
  // representation
  TreeNode<T>* ptr_;
};

// -------------------------------------------------------------------
// DS_SET CLASS
template <class T>
class ds_set {
public:
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) { root_ = this->copy_tree(old.root_,NULL); }
  ~ds_set() { this->destroy_tree(root_); }
  ds_set& operator=(const ds_set<T>& old) { /* implementation omitted */ }

  typedef tree_iterator<T> iterator;

  int size() const { return size_; }
  bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(const T& key_value) { return find(key_value, root_); }
  std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_); }
  int erase(T const& key_value) { return erase(key_value, root_); }

  // OUTPUT & PRINTING
  friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
    s.print_in_order(ostr, s.root_);
    return ostr;
  }
 
  // ITERATORS
  iterator begin() const { 
    if (!root_) return iterator(NULL);
    TreeNode<T>* p = root_;
    while (p->left) p = p->left;
    return iterator(p);
  }
  iterator end() const { return iterator(NULL); }

private:
  // REPRESENTATION
  TreeNode<T>* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<T>*  copy_tree(TreeNode<T>* old_root) { /* Implemented in Lab 9 */ }

  void destroy_tree(TreeNode<T>* p) {
    if (!p) return;
    destroy_tree(p->left);
    destroy_tree(p->right);
    delete p;
  }

  void destroy_tree(TreeNode<T>* & p) {
     // Implemented in Lecture 19
    if (!p) {
      p = NULL;
      size = 0;
      return;
    }

    destroy_tree(p->left);
	TreeNode<T>* tmp = p->right;
    delete p;
    destroy_tree(tmp);
  }
  

    if ( p != NULL) {
      delete p->left;
      delete p->right;
      p->left = NULL;
      p->right = NULL;
    }
  
  }
  

  iterator find(const T& key_value, TreeNode<T>* p) {  /* Implemented in Lecture 17 */  }

  std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p) {
    // NOTE: will need revision to support & maintain parent pointers
    if (!p) {
      p = new TreeNode<T>(key_value);
      this->size_++;
      return std::pair<iterator,bool>(iterator(p), true);
    }
    else if (key_value < p->value)
      return insert(key_value, p->left);
    else if (key_value > p->value)
      return insert(key_value, p->right);
    else
      return std::pair<iterator,bool>(iterator(p), false);
  }
  
  int erase(T const& key_value, TreeNode<T>* &p) { /* Implemented in Lecture 19 */ }

  void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
    if (p) {
      print_in_order(ostr, p->left);
      ostr << p->value << "\n";
      print_in_order(ostr, p->right);
    }
  }
};





BPlusTreeNode<T>* find(const T& value, BPlusTreeNode<T>* p, const int b){
	if (!p) return NULL;
	
	if (p->children.size() == 0){//is leaf
		return p;
	}else if(p->children.size() != 0){
		unsigned int pos;
		if (p->keys.size() == 1){
			if (value < p->keys[0]){
				pos = 0;
			}else{
				pos = 1;
			}
		}else {
			for (unsigned int i = 0; i<p->keys.size()-1; i++){
				if (value< p->keys[i]){
					pos = i;
					break;
				}else if (value > p->keys[i] && value < p->keys[i+1]){
					pos = i+1;
					break;
				}else if (value > p->keys[i+1]){
					pos=i+2;
					break;
				}
			}
		}
		find(value,p->children[pos],b);
	}




  
/*pair<BPlusTreeNode<T>*,bool> insert(const T& value, BPlusTreeNode<T>*& p, const int b){ //make as a pair
	if (size_ == 0){ //create root node.
		cout<<"1) "<<value<<std::endl;
		p = new BPlusTreeNode<T>;
		size_++;
		p->keys.push_back(value);
		root_ = p;
		return pair<BPlusTreeNode<T>*, bool>(p,true);
	}else if (p->children.size() == 0){//not children
		cout<<"2) "<<value<<std::endl;
		if (int(p->keys.size()) <= b-2){//not overflowing
			cout<<"hi "<<value<<std::endl;
			p->keys.push_back(value);
			sort(p->keys.begin(), p->keys.end());
			size_++;
		}else{//overflowed.
			//split function
			cout<<"bye "<<value<<std::endl;
			p->keys.push_back(value);
			size_++;
			sort(p->keys.begin(), p->keys.end());
			overflow(p,b);
		}
	}else if (p->children.size() != 0){//there are children
		cout<<"3) "<<value<<std::endl;
		unsigned int pos;
		if (p->keys.size() == 1){
			cout<<"VALUE "<<value<<std::endl;
			if (value < p->keys[0]){
				pos=0;
			}else{
				pos = 1;
			}
		}else{
			for (unsigned int i = 0; i<p->keys.size()-1; i++){
				if (value< p->keys[i]){
					pos = i;
					break;
				}else if (value > p->keys[i] && value < p->keys[i+1]){
					pos = i+1;
					break;
				}else if (value > p->keys[i+1]){
					pos=i+2;
					break;
				}
			}
		}

		if (int(p->children[pos]->keys.size()) <= b-2){//Not overflowed.
			p->children[pos]->keys.push_back(value);
			sort(p->children[pos]->keys.begin(), p->children[pos]->keys.end());
			size_++;
		}else{//overflow.
			size_++;
			p->children[pos]->keys.push_back(value);
			sort(p->children[pos]->keys.begin(), p->children[pos]->keys.end());
			overflow(p->children[pos],b);
		}

	}else pair<BPlusTreeNode<T>*, bool>(p,true);
	return pair<BPlusTreeNode<T>*, bool>(p,true);
}*/











/*
	if (!p) return NULL;
	// if null and value not inside return null
	for (unsigned int i = 0; i < p->keys.size(); i++){
		if (value == p->keys[i])
			return p;
	}
	if (p == root_ && root_->children.size() == 0){//if its the root.
		return p;
	}
	if (value < p->keys[0]){
		if (p->children.size()>0)
			find(value, p->children[0],b);
		else return p;
	} else if (value > p->keys[0] && value < p->keys[b-2]){
		if (p->children.size()>0){
			for (int i = 1; i < b-2; i++){
				find(value, p->children[i],b);
			}
		}
	}else if (value > p->keys[b-2]){
		if (p->children.size() > 0)
			find(value, p->children[p->children.size()-1], b);
		else return p;
	}else 
		return p;
	return NULL;
*/


	/*
	if (!p) return NULL;
	if (root_ != NULL){
		if (p->is_leaf()){
			return p;
		}
		for (unsigned int i; i < p->keys.size(); i++){
			if (value == p->keys[i]){
				return p;
			}
		}
		int pos ;
		if (p->keys.size() == 1){
			cout<<"VALUE "<<value<<std::endl;
			if (value < p->keys[0]){
				pos=0;
			}else{
				pos = 1;
			}
		}else{
			for (unsigned int i = 0; i<p->keys.size()-1; i++){
				if (value< p->keys[i]){
					pos = i;
					break;
				}else if (value > p->keys[i] && value < p->keys[i+1]){
					pos = i+1;
					break;
				}else if (value > p->keys[i+1]){
					pos=i+2;
					break;
				}
			}
		}
		find(value,p->children[pos],b);
		
	}else return NULL;
	return NULL;*/
	
}

  /*if (p) {
    for (unsigned int i = 0; i < p->keys.size(); i++) { //p->size
      cout << p->keys[i] << " ";
    }
    cout << "\n";
    if (p->is_leaf() == false) {
		
		int size = p->children.size() - p->children.size()/2;
		for (unsigned int i = p->children.size()-1; i <= size; i--)
			print_sideways(ostr,p->children[i],depth);
			
      //	for (unsigned int i = size; i > 0; i--) {
        //	print_sideways(ostr,p->children[i],depth);
      //	}

    }
  }*/






  FIND 
  /*if (p) {
    for (unsigned int i = 0; i < p->keys.size(); i++) { //p->size
      cout << p->keys[i] << " ";
    }
    cout << "\n";
    if (p->is_leaf() == false) {
		
		int size = p->children.size() - p->children.size()/2;
		for (unsigned int i = p->children.size()-1; i <= size; i--)
			print_sideways(ostr,p->children[i],depth);
			
      //	for (unsigned int i = size; i > 0; i--) {
        //	print_sideways(ostr,p->children[i],depth);
      //	}

    }
  }*/