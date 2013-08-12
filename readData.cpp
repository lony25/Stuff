#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<math.h>

enum {NONE, STATIC, GROWING, WINDOWING};

class dataSet{
public:
  vector<dataEntry*> trainingSet;
  vector<dataEntry*> generalizationSet;
  vector<dataEntry*> validationSet;

  dataSet(){}
  ~dataSet(){
    trainingSet.clear();
    generalizationSet.clear();
    validationSet.clear();
  }

  void clear(){
    trainingSet.clear();
    generalizationSet.clear();
    validationSet.clear();
  }  
};


class readData{
  
};
