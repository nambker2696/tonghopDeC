#include <stdio.h>
#include <stdlib.h>



// Sử dụng hàm qsort để sắp xếp mảng theo thứ
// tự tăng dần/giảm dần
//  Viết lại Bài 1 để so sánh hiệu quả giải thuật

float values[] = { 8.8, 5.6, 10.0, 2, 2.5 };

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main()
{
   int n;

   printf("Before sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) 
   {
      printf("%.1f ", values[n]);
   }

   qsort(values, 5, sizeof(float), cmpfunc);

   printf("\nAfter sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) 
   {   
      printf("<% class="1">   </%>f ", values[n]);
   }
  
   printf("\n");
   return(0);
}