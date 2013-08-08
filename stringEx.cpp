#include<iostream>
#include<string>
#include<cctype>

int main()
{
  const std::string s = "Keep out";
  //  std::getline(std::cin,s);
  for(auto &c : s){
    c='x';
  }
  std::cout<< s << std::endl;
  return 0;
}
