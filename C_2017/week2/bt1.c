#include <stdio.h>
#include <stdlib.h>

int search(void* buf, int size, int l, int r, void* item, int (*compare)(void const*, void const*)){
	int i, res;
	if(r < 1) return -1;
	i = (l + r)/2;
	res = compare(item, (char*)buf+(size*i));
	if(res == 0)
		return i;
	else if(res < 0)
		return search(buf, size, l, i-1, item, compare);
	else
		return search(buf, size, i+1, r, item, compare);
}

int int_compare(void const* x, void const* y){
	int m, n;
	m = *((int*)x);
	n = *((int*)y);
	if(m == n) return 0;
	return m > n ? 1 : -1;
}

int main(){
	int i = 0, res = 0;
	int a[100];
	int n = 100, item = 30;
	for(i = 0; i < n; i++) 
		a[i] = rand()%100;
		qsort(a, n, sizeof(int), int_compare);
	for(i=0;i<n;i++)
		printf("%5d",a[i]);
	res = search(a, sizeof(int), 0, n-1, &item, int_compare);
	printf("\n chi so: %d \n",res);
}