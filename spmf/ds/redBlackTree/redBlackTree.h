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
      const Node* sentinel;
      int size=0;
      Node* _root;
      
      bool _allowSameElementsMultipleTimes = true;
      
    public:
      redBlackTree(bool allowSameElementsMultipleTimes)
	{
	 this-> _allowSameElementsMultipleTimes = allowSameElementsMultipleTimes;
	}

      redBlackTree(){}
      ~redBlackTree(){}

      int size()
      {
	return size;
      }
      
      bool isEmpty()
      {
	return this->_root==NULL;
      }

    private:
      void leftRotate(Node* x)
      {
	
      }
      
    };
}
