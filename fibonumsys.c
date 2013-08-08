#include<stdio.h>
#include<string.h>

void printSol(int* sol,int size)
{
  int i;
  for(i=0;i<=size;++i)
    printf("%d",sol[i]);
  printf("\n");
}

void SumOfSubset(int* sol, int depth,int* array,int size, int num)
{
  if(depth<0)
    return;
  if(num==0)
    printSol(sol,size);
  else{
    if(array[depth] <= num){
      sol[depth]=1;
      SumOfSubset(sol,depth-1,array,size,num-array[depth]);
      sol[depth]=0;
    }
    SumOfSubset(sol,depth-1,array,size,num);
  }
}

int main()
{
  int input=11;
  int i;
  int a=0,b=1,c=0;
  int *w;
  for(i=0;c<input;++i)
    {
      w[i]=b;
      c = a+b;
      a=b;
      b=c;
    }
  int sol[i];
  memset(sol,0,sizeof(sol));
  SumOfSubset(sol,i-1,w,i-1,input);
  return 0;
}
