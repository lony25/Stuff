#pragma once

#define NULL nullptr

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
	Node* z{element};
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

    private:
      void leftRotate(Node* x)
      {
	Node* y = x->right;
	x->right = y->left;
	if(y->left!=NULL)
	  y->left->parent = x;
	
	y->parent = x->parent;
	
	if(x->parent!=NULL)
	  this->_root = y;
	else if(x == x->parent->left)
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
	else if(x == x->parent->right)
	  x->parent->right = y;
	else
	  x->parent->left = y;

	y->right = x;
	x->parent = y;
      }

      void insertFixup(Node* z)
      {
	while(z->parent->color == RED)
	  {
	    if(z->parent == z->parent->parent->left)
	      {
		Node* y = z->parent->parent->right;
		if(y->color == RED)
		  {
		    z->parent->color = BLACK;
		    y->color = BLACK;
		    z->parent->parent->color = RED;
		    z = z->parent->parent;
		  }
		else
		  {
		    if(z == z->parent->right)
		      {
			z = z->parent;
			leftRotate(z);
		      }
		    z->parent->color = BLACK;
		    z->parent->parent->color = RED;
		    rightRotate(z->parent->parent);
		  }
	      }
	    else
	      {
		Node* y = z->parent->parent->left;
		if(y->color == RED)
		  {
		    z->parent->color = BLACK;
		    y->color = BLACK;
		    z->parent->parent->color = RED;
		    z = z->parent->parent;
		  }
		else
		  {
		    if(z==z->parent->left)
		      {
			z = z->parent;
			rightRotate(z);
		      }
		    
		    z->parent->color = BLACK;
		    z->parent->parent->color = RED;
		    leftRotate(z->parent->parent);
		  }
	      }
	  }
	this->root->color = BLACK;
      }
      
      void transplant(Node* u, Node* v)
      {
	if(u->parent==NULL)
	  this->_root = v;
	else if(u==u->parent->left)
	  u->parent->left = v;
	else
	  u->parent->right = v;
      }

      void performDelete(Node* z)
      {
	Node* x;
	Node* y = z;
	bool yOriginalColor = y->color;
	if(z->left == NULL)
	  {
	    x = z->right;
	    transplant(z, z->right);
	  }
	else if(z->right ==NULL)
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

      
    };
}
