#pragma once

#include<string>

#ifndef NULL
#define NULL nullptr
#endif

namespace ds{
  template <typename T> class binaryTree{
  private:
    struct Node;
    int _size = 0;
    Node* _root = nullptr;
    bool _allowSameElementMultipleTimes = true;

  public:
    binaryTree(bool allowSameElementMultipleTimes){
      _allowSameElementMultipleTimes = allowSameElementMultipleTimes;
    }

    binaryTree(){
    }

    int size(){
      return this->_size;
    }

    void addElement(T element){
      Node* z = new Node(element);
      //      z.key = element;
      
      Node* y = nullptr;
      Node* x = this->_root;
      
      while(x!=NULL){
	y=x;
	if(z->key < x->key)
	  x=x->left;
	else{
	  if(z->key == x->key && !this->_allowSameElementMultipleTimes)
	    return;
	  x=x->right;
	}
      }

      z->parent = y;
      if(y==NULL)
	this->_root=z;
      else if(z->key < y->key)
	y->left = z;
      else
	y->right = z;

      ++_size;
    }

    bool isEmpty(){
      return this->_root==NULL;
    }

    void remove(T element){
      Node* z = search(this->_root,element);
      if(z==NULL)
	return;
      performDelete(z);
    }

    T popMinimum(){
      if(this->_root==NULL)
	return NULL;
      
      Node* x = this->_root;
      while(x->left!=NULL)
	x=x->left;

      T value = x->key;
      performDelete(x);
      return value;
    }

    T lower(T k){
      Node* result = lowerNode(k);
      if(result ==NULL)
	return NULL;
      else
	return result->key;
    }

    T higher(T k){
      Node* result = higherNode(k);
      if(result==NULL)
	return NULL;
      else
	return result->key;
    }

    T minimum(){
      if(this->_root==NULL)
	return NULL;
      return minimum(this->_root)->key;
    }

    T popMaximum(){
      if(this->_root==NULL)
	return NULL;
      
      Node x = this->_root;
      while(x->right!=NULL)
	x = x->right;
      
      T value = x->key;
      performDelete(x);
      return value;
    }

    T maximum(){
      if(this->_root==NULL)
	return NULL;
      
      return maximum(this->_root)->key;
    }

    bool contains(T k){
      return search(this->_root, k)!=NULL;
    }

    std::string toString(){
      if(this->_root==NULL)
	return "";
      std::string ss;
      return print(this->_root,ss);
    }

  private:
    struct Node{
      T key;
      Node* left;
      Node* right;
      Node* parent;

    Node(T element):key(element){
	this->left=NULL;
	this->right=NULL;
	this->parent=NULL;
      }
      Node(){
	key=NULL;
	this->left=NULL;
	this->right=NULL;
	this->parent=NULL;
      }

      std::string toString(){
	using std::to_string;
	return to_string(key);
      }
    };

    std::string print( Node* x, std::string& ss){
      if(x!=NULL ){
	print(x->left, ss);
	ss.append(x->toString());
	ss.append(" ");
	print(x->right, ss);
      }
      return ss;
    }

    void performDelete(Node* z){
      Node* y;
      if(z->left == NULL || z->right ==NULL)
	y=z;
      else
	y = successor(z);

      Node* x;
      if(y->left != NULL)
	x = y->left;
      else
	x = y->right;
      if(x!=NULL)
	x->parent = y->parent;

      if(y->parent!=NULL)
	this->_root=x;
      else if(y == y->parent->left)
	y->parent->left = x;
      else
	y->parent->right = x;

      if (y!= z)
	z->key = y->key;
      
      --_size;
    }

    Node* successor(Node* & x){
      if(x->right!=NULL)
	return minimum(x->right);
      Node* y = x->parent;
      while(y!=NULL && x==y->right){
	x= y;
	y=y->parent;
      }
      
      return y;
    }

    Node* predecessor(Node* & x){
      if(x->left != NULL)
	return maximum(x->left);
      
      Node* y = x->parent;
      while(y!=NULL && x==y->left){
	x = y;
	y = y->parent;
      }
      
      return y;
    }

    Node* lowerNode(T k){
      Node* x= this->_root;
      while(x!= NULL){
	if(k > x->key){
	  if(x->right!=NULL)
	    x=x->right;
	  else
	    return x;
	}
	else {
	  if(x->left != NULL)
	    x=x->left;
	  else{
	    Node* current = x;
	    while(current->parent!=NULL
		  && current->parent->left == current)
	      current = current->parent;
	    return current->parent;
	  }
	}
      }
      
      return NULL;
    }

    Node* higherNode(T k){
      Node* x = this->_root;
      while(x!=NULL){
	if(k < x->key){
	  if(x->left != NULL)
	    x = x->left;
	  else
	    return x;
	}
	else{
	  if(x->right != NULL)
	    x = x->right;
	  else{
	    Node* current = x;
	    while(current->parent != NULL &&
		  current->parent->right == current)
	      current = current->parent;
	    return current->parent;
	  }
	}
      }
      return NULL;
    }

    Node* minimum(Node* & x){
      while(x->left != NULL){
	x = x->left;
      }
      return x;
    }

    Node* maximum(Node* &x){
      while(x->right != NULL)
	x = x->right;
      return x;
    }

    Node* search(Node* &x, T k){
      while(x!= NULL && k!= x->key){
	if(k < x->key)
	  x = x->left;
	else
	  x = x->right;
      }
      return x;
    }
  };
}
