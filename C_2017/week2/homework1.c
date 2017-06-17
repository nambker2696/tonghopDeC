// Phát triển hàm sắp xếp tổng quát của riêng
// bạn dựa trên giải thuật được đưa ra trong bài
// giảng 1
// Viết lại các chương trình trong bài giảng 1 sử
// dụng hàm sắp xếp tổng quát

// Hướng dẫn

// Để đổi chỗ hai phần tử trong mảng, chúng ta
// cần xây dựng hàm đổi chỗ tổng quát như sau

// void exch (void * buf, int size, int i, int j);



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10000000


// clock_t start,stop;
time_t start,end;
volatile long unsigned t;


void exchx(void *a,int i,int j,int size){
	void *temp=malloc(size);
	memcpy(temp,(char*)a+i*size,size);
	memcpy((char*)a+i*size,(char*)a+size*j,size);
	memcpy((char*)a+size*j,temp,size);
	free(temp);
}

