#pragma once

#include<vector>
#include<string>
#include<map>
#include<set>

namespace input{
  class sequenceString{
  private:
    std::vector<std::vector<std::string>> _itemSets;
    int _id;

  public:
  sequenceString(int i): _id(i) {}
    ~sequenceString(){}

    void addItemSet(std::vector<std::string> && itemSet){
      _itemSets.push_back(std::move(itemSet));
    }

    void print(){std::cout<<toString();}

    std::string toString(){
      std::string ss="";
      
      for(auto itemSet: _itemSets){
	ss.append("(");
	for(auto item: itemSet){
	  ss.append(item);
	  ss.append(" ");
	}
	ss.append(")");
      }
      return ss.append("    ");
    }

    int getId(){
      return _id;
    }
    
    std::vector<std::vector<std::string>> getItemSets(){
      return _itemSets;
    }

    std::vector<std::string> getItemSet(int index){
      if(index>=0 && index<_itemSets.size())
	return _itemSets.at(i);
    }

    int size(){return _itemSets.size();}
    
    sequenceString cloneSequenceMinusItems(std::map<std::string, std::set<int>> mapSeqId, double relativeMinSup){
      sequenceString seq;
      for(auto itemSet: _itemSets){
	std::vector<std::string> newItemSet = cloneItemSetMinusItems(itemSet, mapSeqId, relativeMinSup);
	if(newItemSet.size()!=0)
	  seq.addItemSet(newItemSet);
      }
    }


    std::vector<std::string> cloneItemSetMinusItems(std::vector<std::string> itemSet, std::map<std::string, std::set<int>> mapSeqId, double relativeMinSup){
      std::vector<std::string> newItemSet;
      for(auto item: itemSet){
	mapT::iterator it = mapSeqId.find(item);
	if(it!= mapSeqId.end() && it->second.size() >= relativeMinSup)
	  newItemSet.push_back(item);
      }
      return newItemSet;
    }
  };
}
