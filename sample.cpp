#include<iostream>
#include<string>
#include<functional>
#include<algorithm>

static inline std::string &ltrim(std::string &s)
{
  s.erase(s.begin(),std::find_if(s.begin(),s.end(),std::not1(std::ptr_fun<int,int>(std::isspace))));
  return s;
}

static inline std::string &rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(),s.rend(),std::not1(std::ptr_fun<int,int>(std::isspace))).base(),s.end());
  return s;
}

static inline std::string &trim(std::string &&s)
{
  return ltrim(rtrim(s));
  
}

int main()
{
  std::string test = "10:20";
  size_t pos = test.find(":");
  std::string v1 = trim(std::move(test.substr(0,pos)));
  std::cout << v1<<std::endl;
  return 0;
}
