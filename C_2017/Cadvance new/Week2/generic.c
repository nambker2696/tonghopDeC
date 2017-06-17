#include <stdio.h>

void exch (void * buf, int size, int i, int j){
	int temp;
	temp = (char*)buf+i*size;
	(char*)buf+i*size = (char*)buf+j*size;
	(char*)buf+j*size = temp;
}

int int_compare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x);
	n = *((int*)y); 
	if ( m == n ) return 0;
	//return m > n ? 1: -1;
        if(m>n) return 1;
        if(m<n) return -1;
}

void sort(void* a, int size, int l, int r, 
                   int (*compare)(void*, void*)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
		while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
            if (j == l) break;
		if (i >= j) break;
		exch(a, size, i, j);
		if (compare((char*)a+i*size, (char*)a+r*size)==0)
		   exch(a, size, ++p, i);
		if (compare((char*)a+j*size, (char*)a+r*size)==0)
		   exch(a, size, --q, j);
	}
	exch(a, size, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a, size, k, j--);
	for (int k = r-1; k >= q; k--) exch(a, size, k, i++);
	sort(a, size, l, j, compare);
	sort(a, size, i, r, compare);
}

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}







