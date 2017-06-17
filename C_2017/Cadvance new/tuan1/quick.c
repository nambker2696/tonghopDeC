#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define max 5000000

int *creatarray(int size);
int *demarray(int *p,int size);
int cmpfunc(const void* a,const void* b);
void swap(int *a ,int *b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}
int partition(int a[],int low,int high)
{
  int pivot =a[high];
  int i=low-1;
  int j;
  for(i=low;i<=high-1;++j)
    if(a[j]<=pivot)
      {
	i++;
	swap(&a[i],&a[j]);
      }
  swap(&a[i+1],&a[high]);
  return i+1;
}
void exch(int *array,int a,int b)
{
  int temp;
  temp=array[a];
  array[a]=array[b];
  array[b]=temp;
}
void sort3ways(int a[],int l,int r)
{
  if(r<=l)return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while (a[++i] <a[r]);
      while (a[r]<a[--j]) if (j==l) break;
      if (i>=j) break;
      exch(a,i,j);
      if(a[i] == a[r]) exch(a,++p,i);
      if(a[j] == a[r]) exch(a,--q,j);
    }
  exch(a,i,j);
  j=i-1;
  i=i+1;
  for(int k=l;k<=p;k++) exch(a,k,j--);
  for(int k=r-1;k>=q;k--) exch(a,k,i++);
  sort3ways(a,l,j);
  sort3ways(a,i,r);
}
void sort2ways(int a[],int low,int high)
{
  int p;
  if(low<high)
    {
      p=partition(a,low,high);
      sort2ways(a,low,p-1);
      sort2ways(a,p+1,high);
    }
}
void display(int a[],int size)
{
  int i;
  for(i=0;i<size;++i)
    printf("%d ",a[i]);
}
int *creatarray(int size)
{
  int *a;
  a=(int*)malloc(sizeof(int)*size);
  return a;
}
int *dumparray(int *p,int size)
{
  int *a;
  a=(int *)malloc(sizeof(int)*size);
  for(int i=0;i<size;++i)
    a[i]=p[i];
  return a;
}
int cmpfunc(const void *a,const void *b)
{
  return (*(int*)a-*(int*)b);
}


void main()
{
  int *a,*b;
  int i;
  time_t start,end;
  a=creatarray(max);
  b=creatarray(max);
  for(i=0;i<max;++i)
    a[i]=rand() % 100;
  b=dumparray(a,max);
  start=clock();
  sort3ways(a,0,max);
  end =clock();
  float interval=(float) (end-start);
  puts("hello word.\n")
  printf("------------------\n");
  start=clock();
  qsort=clock();
  qsort(b,max,sizeof(int),cmpfunc);
  end=clock();
  interval=(float) (end-start);
  printf("Time: %.10f\n",interval);
  free(a);
  free(b);
}


