#pragma once

#include<vector>
#include<iostream>
#include<string>
#include<sstream>

namespace input{
  class sequenceInt{
  private:
    std::vector<std::vector<int>> itemSets;
    
  public:
    sequenceInt(){}
    ~sequenceInt(){}
    
    void addItemSet(std::vector<int> itemSet){
      itemSets.push_back(std::move(itemSet));
    }
    
    std::vector<std::vector<int>> getItemSets(){
      return itemSets;
    }

    void printItemSet(){
      std::cout << toString();
    }

    std::string toString(){
      std::string ss ="";
      for(auto itemSet : itemSets){
	ss.append("(");
	for(auto item : itemSet){
	  ss.append(std::to_string(item));
	  ss.append(" ");
	}
	ss.append(")");
      }
      return ss.append("    ");
    }
    
    std::vector<std::vector<int>> getItems(){
      return itemSets;
    }
    
    std::vector<int> getItemSet(int index){
      return itemSets[index];
    }
    
    
    int getSize(){
      return itemSets.size();
    }
  };
}

