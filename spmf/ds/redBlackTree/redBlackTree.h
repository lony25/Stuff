#pragma once

#include<string>
#include<iostream>

#ifndef NULL
#define NULL nullptr
#endif

namespace ds
{

  #define BLACK true
  #define RED false
  template<typename T>
  class redBlackTree
    {
    private:
      struct Node;
      const Node* _sentinel;
      int _size=0;
      Node* _root;
      
      bool _allowSameElementsMultipleTimes = true;
      
    public:
      redBlackTree(bool allowSameElementsMultipleTimes)
	{
	 this-> _allowSameElementsMultipleTimes = allowSameElementsMultipleTimes;
	}

      redBlackTree(){}
      ~redBlackTree(){}

      int getSize()
      {
	return _size;
      }
      
      bool isEmpty()
      {
	return this->_root==NULL;
      }

      void add(T element)
      {
	Node* z = new Node(element);
	Node* y = NULL;
	Node* x = this->_root;

	while(x!= NULL)
	  {
	    y = x;
	    if(z->key < x->key)
	      x = x->left;
	    else if(z->key==x->key && !this->_allowSameElementsMultipleTimes)
	      return;
	    else
	      x = x->right;
	  }

	z->parent = y;
	if(y==NULL)
	  this->_root = z;
	else if(z->key < y->key)
	  y->left = z;
	else
	  y->right = z;

	this->_size++;

	z->left = NULL;
	z->right = NULL;
	z->color = RED;
	insertFixup(z);
      }

      void remove(T element)
      {
	Node* z = search(this->_root, element);
	if(z==NULL)
	  return;
	performDelete(z);
      }

      T lower(const T& k)
      {
	Node* result = lowerNode(k);
	if(result==NULL)
	  return NULL;
	else
	  return result->key;
	
      }
      
      T higher(const T& k)
      {
	Node* result = higherNode(k);
	if(result==NULL)
	  return NULL;
	else
	  return result->key;
      }

      T popMinimum ()
      {
	if(this->_root==NULL)
	  return NULL;
	Node* x = this->_root;
	while(x->left != NULL)
	  x = x->left;
	T value = x->key;
	performDelete(x);
	return value;
      }

      T popMaximum()
      {
	if(this->_root==NULL)
	  return NULL;
	Node* x = this->_root;
	while(x->right != NULL)
	  x = x->right;
	T value = x->key;
	performDelete(x);
	return value;
      }

      T minimum()
      {
	if(this->_root == NULL)
	  return NULL;
	return minimum(this->_root)->key;
      }

      T maximum()
      {
	if(this->_root == NULL)
	  return NULL;
	return maximum(this->_root)->key;
      }

      bool hasNode(const T& k)
      {
	return search(this->_root, k) != NULL;
      }

      std::string toString()
	{
	  if(this->_root==NULL)
	    return "";
	  std::string ss;
	  return print(this->_root, ss);
	}

    private:
      struct Node
      {
	T key ;
	bool color;
	Node* left ;
	Node* right;
	Node* parent;
	
      Node(T element):key(element)
	{
	  this->left = NULL;
	  this->right = NULL;
	  this->parent = NULL;
	  this->color = BLACK;
	}
	Node()
	  {
	    key = NULL;
	    this->left = NULL;
	    this->right = NULL;
	    this->parent = NULL;
	    this->color = BLACK;
	  }
	~Node(){}
	
	std::string toString()
	  {
	    using std::to_string;
	    return to_string(key);
	  }
      };
      
      void leftRotate(Node* x)
      {
	Node* y = x->right;
	x->right = y->left;
	if(y->left!=NULL)
	  y->left->parent = x;

	y->parent = x->parent;
	
	if(x->parent==NULL)
	  this->_root = y;
	else if(x->parent->left && x == x->parent->left)
	  x->parent->left = y;
	else
	  x->parent->right = y;
	y->left = x;
	x->parent = y;
      }

      void rightRotate(Node* x)
      {
	Node* y = x->left;
	x->left = y->right;
	
	if(y->right != NULL)
	  y->right->parent = x;
	
	y->parent = x->parent;

	if(x->parent == NULL)
	  this->_root = y;
	else if(x->parent->right && x == x->parent->right)
	  x->parent->right = y;
	else
	  x->parent->left = y;

	y->right = x;
	x->parent = y;
      }

      void insertFixup(Node* z)
      {
	while(z->parent && z->parent->color == RED)
	  {
	    if(z->parent == z->parent->parent->left)
	      {
		Node* y = z->parent->parent->right;
		if(y && y->color == RED)
		  {
		    z->parent->color = BLACK;
		    y->color = BLACK;
		    z->parent->parent->color = RED;
		    z = z->parent->parent;
		  }
		else
		  {
		    if(z->parent->right && z == z->parent->right)
		      {
			z = z->parent;
			leftRotate(z);
		      }
		    z->parent->color = BLACK;
		    if(z->parent->parent)
		      {
			z->parent->parent->color = RED;
			rightRotate(z->parent->parent);
		      }
		  }
	      }
	    else
	      {
		Node* y;
		if(z->parent->parent)
		  y = z->parent->parent->left;
		if(y && y->color == RED)
		  {
		    z->parent->color = BLACK;
		    y->color = BLACK;
		    z->parent->parent->color = RED;
		    z = z->parent->parent;
		  }
		else
		  {
		    if(z->parent->left && z==z->parent->left)
		      {
			z = z->parent;
			rightRotate(z);
		      }
		    
		    z->parent->color = BLACK;
		    if(z->parent->parent)
		      {
			z->parent->parent->color = RED;
			leftRotate(z->parent->parent);
		      }
		  }
	      }
	  }
	this->_root->color = BLACK;
      }
      
      void transplant(Node* u, Node* v)
      {
	if(u->parent==NULL)
	  this->_root = v;
	else if(u==u->parent->left)
	  u->parent->left = v;
	else
	  u->parent->right = v;
	if(v)
	  v->parent = u->parent;
      }

      void performDelete(Node* z)
      {
	Node* x;
	Node* y = z;
	bool yOriginalColor = y->color;
	if(!z->left && !z->right)
	  {
	    if(z->parent->color==RED)
	      z->parent->color=BLACK;
	    else
	      z->parent->color=RED;
	    transplant(z,NULL);
	    z=NULL;
	    this->_size--;
	    return;
	  }
	
	if(z->left == NULL )
	  {
	    x = z->right;
	    transplant(z, z->right);
	  }
	else if(z->right ==NULL )
	  {
	    x = z->left;
	    transplant(z, z->left);
	  }
	else
	  {
	    y = minimum(z->right);
	    yOriginalColor = y->color;
	    x = y->right;
	    if(y->parent == z)
	      x->parent = y;
	    else
	      {
		transplant(y, y->right);
		y->right = z->right;
		y->right->parent = y;
	      }
	    transplant(z,y);
	    y->left = z->left;
	    y->left->parent = y;
	    y->color = z->color;
	  }
	if(yOriginalColor == BLACK)
	  deleteFixup(x);
	
	this->_size--;
      }

      void deleteFixup(Node* x)
      {
	while(x!= this->_root && x->color==BLACK)
	  {
	    if(x==x->parent->right)
	      {
		Node* w = x->parent->right;
		if(w->color == RED)
		  {
		    w->color = BLACK;
		    x->parent->color = RED;
		    leftRotate(x->parent);
		    w = x->parent->right;
		  }
		
		if(w->color == BLACK && w->right->color == BLACK)
		  {
		    w->color = RED;
		    x = x->parent;
		  }
		else
		  {
		    if(w->right->color== BLACK)
		      {
			w->left->color = BLACK;
			w->color = RED;
			rightRotate(w);
			w = x->parent->right;
		      }
		    
		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->right->color = BLACK;
		    leftRotate(x->parent);
		    x = this->_root;
		  }
	      }
	    else
	      {
		Node* w = x->parent->left;
		if(w->color== RED)
		  {
		    w->color = BLACK;
		    x->parent->color = RED;
		    rightRotate(x->parent);
		    w = x->parent->left;
		  }

		if(w->right->color==BLACK && w->left->color == BLACK)
		  {
		    w->color = RED;
		    x = x->parent;
		  }
		else
		  {
		    if(w->left->color == BLACK)
		      {
			w->right->color = BLACK;
			w->color = RED;
			leftRotate(w);
			w = x->parent->left;
		      }

		    w->color = x->parent->color;
		    x->parent->color = BLACK;
		    w->left->color = BLACK;
		    rightRotate(x->parent);
		    x = this->_root;
		  }
	      }
	  }
	x->color = BLACK;
      }

      Node* successor(Node* x)
      {
	if(x->right != NULL)
	  return minimum(x->right);
	
	Node* y = x->parent;
	while(y!= NULL && x==y->right)
	  {
	    x= y;
	    y= y->parent;
	  }
	return y;
      }

      Node* predecessor(Node* x)
      {
	if(x->left != NULL)
	  return maximum(x->left);
	
	Node* y = x->parent;
	while(y!= NULL && x== y->left)
	  {
	    x = y;
	    y = y->parent;
	  }
	return y;
      }

      Node* lowerNode(const T& k)
      {
	Node* x = this->_root;
	while(x!= NULL)
	  {
	    if(k > x->key)
	      if(x->right!=NULL)
		x = x->right;
	      else
		return x;
	    else
	      if(x->left!=NULL)
		x=x->left;
	      else
		{
		  Node* current = x;
		  while(current->parent != NULL 
			&& current->parent->left = current)
		    current=current->parent;
		  return current->parent;
		}
	  }
	return NULL;
      }

      Node* higherNode(const T& k)
      {
	Node* x = this->_root;
	while(x!=NULL)
	  {
	    if( k < x->key)
	      if(x->left!=NULL)
		x=x->left;
	      else
		return x;
	    else
	      if(x->right != NULL)
		x = x->right;
	      else
		{
		  Node* current = x;
		  while(current->parent != NULL &&
			current->parent->right == current)
		    current = current->parent;
		  return current->parent;
		}
	  }
	return NULL;
      }
      
      Node* minimum(Node* x)
      {
	while(x->left != NULL )
	  x = x->left;
	return x;
      }
      
      Node* maximum(Node* x)
      {
	while(x->right != NULL )
	  x = x->right;
	return x;
      }

      Node* search(Node* x, const T& k)
      {
	while(x!= NULL && k!= x->key)
	  if(k < x->key)
	    x = x->left;
	  else
	    x = x->right;
	
	return x;
      }
      
      std::string print(Node* x, std::string& ss)
	{
	  if(x!=NULL)
	    {
	      print(x->left, ss);
	      ss.append(x->toString());
	      ss.append(" ");
	      print(x->right, ss);
	    }
	  return ss;
	}
    };
}
