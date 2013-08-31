#include<iostream>
#include<vector>

class dataEntry{
 public:
  double* pattern;
  double* target;

 dataEntry(double* p, double* t): pattern(p),target(t){}
  
  ~dataEntry(){
    delete[] pattern;
    delete[] target;
  }
};
