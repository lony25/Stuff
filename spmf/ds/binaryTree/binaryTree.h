#pragma once

namespace ds{
  template <typename T> class binaryTree{
  private:
    int _size = 0;
    Node* _root = nullptr;
    bool _allowSameElementMultipleTimes = true;

  public:
    binaryTree(boolean allowSameElementMultipleTimes){
      _allowSameElementMultipleTimes = allowSameElementMultipleTimes;
    }

    binaryTree(){
    }

    int size(){
      return _size;
    }

    void addElement(T element){
      Node* z = new Node();
      z.key = element;
      
      Node* y = nullptr;
      Node* x = _root;
      
      while(x!=NULL){
	y=x;
	int compare = z->key.compareTo(x->key);
	if(compare<0)
	  x=x->left;
	else{
	  if(compare==0 && !_allowSameElementsMultipleTimes)
	    return;
	  x=x->right;
	}
      }

      z->parent = y;
      if(y==NULL)
	_root=z;
      else if(z->key.compareTo(y->key) < 0)
	y->left = z;
      else
	y->right = z;

      ++_size;
    }

    bool isEmpty(){
      return _root==NULL;
    }

    void remove(T element){
      Node* z = search(_root,element);
      if(z==NULL)
	return;
      performDelete(z);
    }

    T popMinimum(){
      if(_root==NULL)
	return NULL;
      
      Node* x = _root;
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
      if(_root==NULL)
	return NULL;
      return minimum(_root)->key;
    }

    T popMaximum(){
      if(_root==NULL)
	return NULL;
      
      Node x = _root;
      while(x->right!=NULL)
	x = x->right;
      
      T value = x->key;
      performDelete(x);
      return value;
    }

    T maximum(){
      if(_root==NULL)
	return NULL;
      
      returm maximum(_root)->key;
    }

    bool contains(T k){
      return search(_root, k)!=NULL;
    }

    std::string toString(){
      if(_root==NULL)
	return "";
      std::string ss;
      return print(_root,ss);
    }

  private:
    class Node{
      T key = NULL;
      Node* left = NULL;
      Node* right = NULL;
      Node* parent = NULL;

      std::string toString(){
	std::string ss="";
	ss.append(key.toString());
	if(left!=NULL){
	  ss.append(" L= ");
	  ss.append(left->key);
	}
	if(right!=NULL){
	  ss.append(" R= ");
	  ss.append(right->key);
	}
	
	return ss;
      }

      int compareTo(const Node& node){
	if(key>node->key)
	  return 1;
	else if(key<node->key)
	  return -1;
	else 
	  return 0;
      }
    };

    std::string print(const Node* _root, std::string ss){
      if(x!=NULL && x->key !=NULL){
	print(x->left, ss);
	ss.append(x->key);
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
	_root=x;
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
	return minimum(s->right);
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
      Node* x= _root;
      while(x!= NULL){
	if(k.compareTo(x->key) > 0){
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
      Node* x = _root;
      while(x!=NULL){
	if(k.compareTo(x->key) < 0){
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
	if(k.compareTo(x->key) < 0)
	  x = x->left;
	else
	  x = x->right;
      }
      return x;
    }
  };
}
