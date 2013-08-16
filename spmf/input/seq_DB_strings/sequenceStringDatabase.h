#pragma once

#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<string>
#include<exception>
#include<iostream>

#include "sequenceString.h"

namespace input{
  class sequenceStringDatabase{
  private:
    std::vector<sequenceString> _sequences;

  public:
    sequenceStringDatabase(){}
    ~sequenceStringDatabase(){}

    void loadFile(std::string path){
      std::string line;
      try{
	std::ifstream file(path);
	while(std::getline(file, line)){
	  if(line[0]!='#' || line[0]!= '%' || line[0] != '@'){
	    std::string temp;
	    std::stringstream ss(line);
	    std::vector<std::string> token;
	    while(ss>>temp)
	      token.push_back(temp);
	    addSequence(token);
	  }
	}
      }
      catch(const std::exception &e){
	std::cerr<<e.what();
      }
    }

    void addSequence(std::vector<std::string> tokens){
      sequenceString seq{_sequences.size()};
      std::vector<std::string> itemSet;
      
      for(auto item: tokens){
	if(item[0] =='<'){}
	else if(item =="-1"){
	  sort(itemSet.begin(), itemSet.end());
	  seq.addItemSet(itemSet);
	  itemSet.clear();
	}
	else if(item=="-2")
	  _sequences.push_back(seq);
	else
	  itemSet.push_back(item);
      }
    }

    void addSeequence(sequenceString seq){
      _sequences.push_back(seq);
    }
    
    void printDatabase(){
      for(auto seq: _sequences){
	std::cout<<seq.getId()<<": ";
	seq.print();
	std::cout<<std::endl;
      }
    }

    void printDatabaseStats(){
      std::cout<<"Number of sequences: "<<_sequences.size();
      long size=0;
      for(auto seq: _sequences)
	size+= seq.size();
      double meansize = ((float) size)/((float)_sequences.size());
      std::cout<<"Average sequence size: "<<meansize<<std::endl;
    }

    std::string toString(){
      std::string ss="";
      for (auto seq: _sequences){
	ss.append(std::to_string(seq.getId()));
	ss.append(": ");
	ss.append(seq.toString());
	ss.append("\n");
      }
      return ss;
    }
  };
}
