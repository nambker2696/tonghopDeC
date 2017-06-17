#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare(void const* x,void const *y)
{
  int m,n;
  m=*((int*)x);
  n=*((int*)y);
  if(m==n) return 0;
  return m>n?1: -1;
}
int search(void*buf,int size,int l,int r,void *item,int (*compare)(void*,void*))
{
  int i,res;
  if(r<l) return -1;
  i=(l+r)/2;
  res=compare(item,(char*)buf+(size*i));
  if(res==0)
    return i;
  else if(res<0)
    return search(buf,size,l,i-1,item,compare);
  else
    return search(buf,size,i+1,r,item,compare);
}

int main()
{
  int a[100],i,res;
  int n=10,item=5;
  for(i=0;i<n;i++) a[i]=rand()%100;
  qsort(a,n,sizeof(int),compare);
  res=search(a,sizeof(int),0,n-1,&item,compare);
  for(i=0;i<n;i++)
    printf("%-10d",a[i]);
  printf("\n%d\n",res);
  return 0;
}
