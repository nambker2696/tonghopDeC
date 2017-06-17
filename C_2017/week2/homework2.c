// Viết lại hàm tìm kiếm và sắp xếp tổng quát sử
// dụng Jval, như sau:

// void sort_gen ( Jval a[], int l, int r, int
// (*compare)(Jval*, Jval*) );
// int search_gen ( Jval a[], int l, int r, Jval item, int
// (*compare)(Jval*, Jval*) );



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef union {
int i;
long l;
float f;
double d;
void *v;
char *s;
char c;
} Jval;


/// Ham Khoi tao	
Jval new_jval_i(int i) {
  Jval j;
  j.i = i;
  return j;
}
  
Jval new_jval_l(long l) {
  Jval j;
  j.l = l;
  return j;
}
  
Jval new_jval_f(float f) {
  Jval j;
  j.f = f;
  return j;
}
  
Jval new_jval_d(double d) {
  Jval j;
  j.d = d;
  return j;
}
Jval new_jval_v(void *v) {
  Jval j;
  j.v = v;
  return j;
}
Jval new_jval_s(char *s) {
  Jval j;
  j.s = s;
  return j;
}
  
Jval new_jval_c(char c) {
  Jval j;
  j.c = c;
  return j;
}

// Ham Truy cap
int jval_i(Jval j) {
  return j.i;
}

float jval_f(Jval j) {
  return j.f;
}

double jval_d(Jval j) {
  return j.d;
}



#define MAX 9
int intArray[MAX] = {4,6,3,2,1,9,7,8,5};

// Quick sort

void exchx(Jval a[],int i,int j,int size){
	void *temp=malloc(size);
	memcpy(temp,(char*)a+i*size,size);
	memcpy((char*)a+i*size,(char*)a+size*j,size);
	memcpy((char*)a+size*j,temp,size);
	free(temp);
}

void qsort_2_gen(Jval a[],int left,int right,int size,int(*compare)(Jval*, Jval*)){
	int i=left,j=right;
	if(left>=right)
		return;
	void *tmp=malloc(size);
	memcpy(tmp,(char*)a+((left+right)/2)*size,size);
	while(i<=j)
	{
		while(compare((char*)a+(i)*size,tmp)<0)
			i++;
		while(compare((char*)a+(j)*size,tmp)>0)
		{
			if(j==left)
				break;
			j--;
		}
		if(i<=j)
		{
			exchx(a,i,j,size);
			i++;
			j--;
		}
	}
	free(tmp);
	qsort_2_ways(a,left,j,size,compare);
	qsort_2_ways(a,i,right,size,compare);
}

void sort_gen ( Jval a[], int l, int r, int
(*compare)(Jval*, Jval*) );


void sort_gen ( Jval a[], int l, int r, int
(*compare)(Jval*, Jval*) );

// Void main

int main(){
   printf("Input Array: ");
   display();
   printline(50);
   quickSort(0,MAX-1);
   printf("Output Array: ");
   display();
   printline(50);
}