#pragma once

#include<set>
#include<exception>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<iostream>

namespace input{
  class transactionDatabase{
  private:
    std::set<int> _items;
    
    std::vector<std::vector<int>> _transactions;

  public:
    transactionDatabase(){}
    ~transactionDatabase(){}

    void addTransaction(std::vector<int> transaction){
      _transactions.push_back(transaction);
      std::copy(transaction.begin(), transaction.end(), _items.end());
    }

    void loadFile(std::string path){
      std::string line;
      try{
	std::ifstream file(path);
	while(getline(file,line)){
	  if(line[0]!='#' || line[0]!= '%' || line[0] != '@'){
	    std::string temp;
	    std::stringstream ss(line);
	    std::vector<std::string> token;
	    while(ss>>temp)
	      token.push_back(temp);
	    addTransaction(token);
	  }
	}
      }
      catch(const std::exception &e){
	std::cerr<<e.what();
      }
    }

    void printDatabase(){
      int count =0;
      for(auto itemSet: _transactions){
	std::cout<<"0"<<count<<": ";
	print(itemSet);
	std::cout<<std::endl;
	count++;
      }
    }
    
    int size(){
      return _transactions.size();
    }

    std::vector<std::vector<int>> getTransactions(){
      return _transactions;
    }

    std::set<int> getItems(){
      return _items;
    }

  private:
    void addTransaction(std::vector<std::string> itemsString){
      std::vector<int> itemSet;
      for(auto attribute : itemsString){
	int item = std::stoi(attribute);
	itemSet.push_back(item);
	_items.insert(item);
      }
      _transactions.push_back(itemSet);
    }

    void print(std::vector<int> itemSet){
      std::string ss;
      for(auto item: itemSet){
	ss.append(std::to_string(item));
	ss.append(" ");
      }
      std::cout<<ss<<std::endl;
    }

  };
}
