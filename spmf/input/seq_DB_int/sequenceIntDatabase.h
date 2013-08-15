#pragma once

#include<limits>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<exception>

#include "sequenceInt.h"

namespace input{
  class sequenceIntDatabase{
  public:
    int minItem = std::numeric_limits<int>::max();
    int maxItem = 0;
  private:
    std::vector<sequenceInt> sequences;

  public:
    sequenceIntDatabase(){}
    ~sequenceIntDatabase(){}
    
    void loadFile(std::string path){
      std::string line;
      try{
	std::ifstream file(path);
	while(std::getline(file,line)){
	  if(line.chatAt(0)!='#' || line.charAt(0)!= '%' || line.charAt(0) != '@'){
	    std::string temp;
	    stringstream ss(line);
	    std::vector<std::string> token;
	    while(ss>>temp)
	      token.push_back(temp);
	    addSequence(token);
	  }
	}
      }
      catch(const std::exception &e){
	std::cerr << e.what();
      }
    }

    void addSequence(std::vector<std::string> tokens){
      sequenceInt seq = new sequenceInt();
      std::vector<int> itemSet;
      for(auto token: tokens){
	if(token.charAt(0)=='<'){}
	else if(token.compare("-1")) {
	  seq.addItemSet(itemSet);
	  itemSet.clear();
	}
	else if(token.compare("-2"))
	  sequences.push_back(seq);
	else{
	  int item = std::stoi(token);
	  if(item>=maxItem)
	    maxItem = item;
	  if(item<minItem)
	    minItem = item;
	  itemSet.push_back(item);
	}
      }
    }

    void addSequence(sequenceInt seq){
      sequences.push_back(seq);
    }
    
    void print(){
      for(int i=0;i<sequences.size();++i){
	std::cout<<count<<": ";
	sequences.getItemSet(i).printItemSet();
	std::endl;
      }
    }

    void printDatabaseStats(){
      std::cout<<"Number of sequences: "<<sequences.size()<<std::endl;
      std::cout<<"Min Item: "<<minItem<<std::endl;
      std::cout<<"Max Item: "<<maxItem<<std::endl;
      
      long size =0;
      for(auto seq:sequences)
	size+= seq.size();
      
      double meanSize =  ((float)size)/((float)sequences.size());
      
      std::cout<<"Mean size: "<<meanSize<<std::endl;
    }
    
    std::string toString(){
      std::string ss ="";
      for(int i=0;i<sequences.size();++i){
	ss.append(to_string(i));
	ss.append(": ");
	ss.append(sequences.getItemSet(i).toString());
	ss.append("\n");
      }
      
      return ss;
    }

    int size(){
      return sequences.size();
    }

    std::vector<sequenceInt> getSequence(){
      return sequences;
    }

  };
}
