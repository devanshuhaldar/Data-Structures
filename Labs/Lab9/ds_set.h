// Partial implementation of binary-tree based set class similar to std::set.  
// The iterator increment & decrement operations have been omitted.
#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>

// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL) {}
  TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
  T value;
  TreeNode* left;
  TreeNode* right;
};

template <class T> class ds_set;

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
  // increment & decrement will be discussed in Lecture 19 and Lab 11

private:
  // representation
  TreeNode<T>* ptr_;
};

// -------------------------------------------------------------------
// DS SET CLASS
template <class T>
class ds_set {
public:
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) { 
    root_ = this->copy_tree(old.root_); }
  ~ds_set() { this->destroy_tree(root_);  root_ = NULL; }
  ds_set& operator=(const ds_set<T>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_);
      size_ = old.size_;
    }
    return *this;
  }

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
  void print_as_sideways_tree(std::ostream& ostr) const {
    print_as_sideways_tree(ostr, root_, 0); }

  // ITERATORS
  iterator begin() const { 
    if (!root_) return iterator(NULL);
    TreeNode<T>* p = root_;
    while (p->left) p = p->left;
    return iterator(p);
  }
  iterator end() const { return iterator(NULL); }

  T accumulate(T val){
    TreeNode<T>* p= root_;
    val+= p->value;
    return helper(p,val);
  }

  T helper(TreeNode<T>* p, T val){
    if (p == NULL) return val;
    if (p->left){
      val+=p->left->value;
      return helper(p->left,val);
    }else if (p->right){
      val+=p->right->value;
      return helper(p->right,val);
    }
    return val;
  }

private:
  // REPRESENTATION
  TreeNode<T>* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<T>*  copy_tree(TreeNode<T>* old_node) {
    // Implemented in Lab 10
    if (old_node == NULL){
      return NULL;
    }else{
      TreeNode<T>* new_node = new TreeNode<T>(old_node->value);
      new_node->right = copy_tree(old_node->left);
      new_node->left = copy_tree(old_node->right);
      return new_node;
    }
  }

  void destroy_tree(TreeNode<T>* p) { /* Implemented in Lecture 18 */  }

  iterator find(const T& key_value, TreeNode<T>* p) {
    /*if (!p) return iterator(NULL);
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return iterator(p);*/
    if (!p) return iterator(NULL);

    while (p){
      if (p->value==key_value){
        return iterator(p);
      }else if (p->value > key_value){
        p = p->left;
      }else if (p->value < key_value){
        p = p->right;
      }
    }
    return p;
  }

  std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p) {
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
  
  int erase(T const& key_value, TreeNode<T>* &p) {  /* Implemented in Lecture 19 or 20 */  }

  void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
    if (p) {
      print_in_order(ostr, p->left);
      ostr << p->value << "\n";
      print_in_order(ostr, p->right);
    }
  }

  void print_as_sideways_tree(std::ostream& ostr, const TreeNode<T>* p, int depth) const {
    if (p) {
      print_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << "\n";
      print_as_sideways_tree(ostr, p->left, depth+1);
    }
  }
  
  


};

/*Insertion work 4/6
  if (size_ == 0){ // first insert
		p = new BPlusTreeNode<T>;
		p->keys.push_back(value);
		root_ = p;
		this->size_++;
	//	cout<<"Initial size: "<<this->size_<<std::endl;
	//	cout<<"Initial value: "<<p->keys[0]<<std::endl;
		return pair<BPlusTreeNode<T>*,bool>(p,true);
	}else if (b-1 != p->keys.size()){ // this is wrong
		p->keys.push_back(value);
		this->size_++;
		sort(p->keys.begin(), p->keys.end());
		
	}else if (b-1 == p->keys.size() && p == root_){//root overfloods
		p->keys.push_back(value);
		sort(p->keys.begin(), p->keys.end());
		this->size_++;
		vector<T> temp = p->keys;
		p->keys.clear();
		p->keys.push_back(temp[temp.size()/2]);
		//how to know which children to create?
		vector<T> first;
		vector<T> second; 
		for (int i = 0; i < temp.size()/2; i++){
			first.push_back(temp[i]);
		}
		for (int i = temp.size()/2; i<temp.size(); i++){
			second.push_back(temp[i]);
		}
		BPlusTreeNode<T>* t1 = new BPlusTreeNode<T>;
		BPlusTreeNode<T>* t2 = new BPlusTreeNode<T>;
		p->children.push_back(t1);
		p->children.push_back(t2);
		p->children[0]->keys = first;
		p->children[1]->keys = second;
		//how to know which children to create?
		cout<<"Values"<<std::endl;
		for (int i = 0; i < p->children.size(); i++){
			for (int j = 0; j < p->children[i]->keys.size(); j++){
				cout<<" "<<p->children[i]->keys[j];
			}
		}

	}else if (b-1 == p->keys.size() && p!=root_){// Need to go back to parent. Not root node
		
	}
	return pair<BPlusTreeNode<T>*,bool>(p,false);

}


*/

#endif
