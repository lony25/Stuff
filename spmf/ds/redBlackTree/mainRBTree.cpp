#include<iostream>
#include<string>

#include "redBlackTree.h"

int main()
{
  ds::redBlackTree<int> tree;

  tree.add(1);
  tree.add(2);
  tree.add(5);
  tree.add(6);
  tree.add(7);
  tree.add(9);
  tree.add(3);
  tree.add(4);

  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  return 0;
}
