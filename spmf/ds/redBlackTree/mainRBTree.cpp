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
  tree.add(500);
  tree.add(501);
  tree.add(100);
  tree.add(101);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;

  std::cout<<"minimum: "<<tree.minimum()<<std::endl;
  std::cout<<"maximum: "<<tree.maximum()<<std::endl;
  tree.remove(7);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  tree.remove(2);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  tree.remove(5);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  tree.add(2);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  tree.remove(999);
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  std::cout<<"pop minimum: "<<tree.popMinimum()<<std::endl;
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  std::cout<<"pop maximum: "<<tree.popMaximum()<<std::endl;
  std::cout<<"All elements: "<<tree.toString()<<" Size of Tree: "<<tree.getSize()<<std::endl;
  
  return 0;
}
