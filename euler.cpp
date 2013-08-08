#include<iostream>
#include<string>
#include<cstdio>
#include<sstream>
#include<fstream>
#include<vector>

using namespace std;

unsigned long long binomial(int n)
{
  vector<int> temp;
  vector<int>::iterator it;
  unsigned long long prod = 1;
  for(int i=1;i<=n;++i){
    prod = prod*(n+i);
    if(prod%i==0)
      prod=prod/i;
    else
      temp.push_back(i);
  }
  for(it=temp.begin();it!=temp.end();++it)
    prod=prod/(*it);
  return prod;
}

int main()
{
  /*  string input[100];
  ifstream infile("input.txt");
  int i=0;
  while(infile>>input[i])
    ++i;
  string answer="";
  int temp;
  int k=0;
  for(i=49;i>=0;--i){
    std::stringstream ss;
    for(int j=0;j<100;++j)
      {
	k=k+((int)input[j][i]-'0');
      }
    temp = k%10;
    k=k/10;
    /*    ss<<temp;
    tmp=ss.str();
    cout<<ss.str()<<endl;
    if(i<10&&i>0)
      answer=std::to_string(temp)+answer;
    //    ss.str("");
  }
  k*=10;
  k+=temp;
  answer = std::to_string(k) + answer;
  cout << answer<<endl;*/

  /*
    one - 3*9*10+3*100  = 573
    two - 3*9*10+3*100  = 570
    three - 5*9*10+5*100= 950
    four - 4*9*10+4*100 = 760
    five - 4*9*10+4*100 = 760
    six - 3*9*10+3*100  = 570
    seven - 5*9*10+5*100= 950
    eight - 5*9*10+5*100= 950
    nine - 4*9*10+4*100 = 760
    ten - 3*10      =  30
    eleven - 6*10   =  60
    twelve - 6*10   =  60
    thirteen - 8*10 =  80
    fourteen - 8*10 =  80
    fifteen - 7*10  =  70
    sixteen - 7*10  =  70
    seventeen - 9*10=  90
    eighteen - 8*10 =  80
    nineteen - 8*10 =  80
    twenty - 6*100  = 600
    thirty - 5*100  = 500
    forty - 5*100   = 500
    fifty - 5*100   = 500
    sixty - 5*100   = 500
    seventy - 7*100 = 700
    eighty - 6*100  = 600
    ninety - 6*100  = 600
    hundred - 7*900 =6300
    and - 3*891     =2673
    thousand - 8*1  =   8
             total  =2
   */

  for(int i=1;i<=1000;++i)
    {
      if(i<
    }

  cout << binomial(n)<<endl;
  return 0;
}
