#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define ARR_SIZE 1000000

typedef union {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} Jval;

// void swap(int *a, int *b)
// {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void exch(int *array, int a, int b)
// {
// 	int temp;
// 	temp = array[a];
// 	array[a] = array[b];
// 	array[b] = temp;
// }

// void sort3ways(int a[], int l, int r) {
// 	if (r <= l) return;
// 	int i = l - 1, j = r;
// 	int p = l - 1, q = r;
// 	while (1)	{
// 		while (a[++i] < a[r]);
// 		while (a[r] < a[--j]) if (j == l) break;
// 		if (i >= j) break;
// 		exch(a, i, j);
// 		if (a[i] == a[r]) exch(a, ++p, i);
// 		if (a[j] == a[r]) exch(a, --q, j);
// 	}
// 	exch(a, i, r);
// 	j = i - 1;
// 	i = i + 1;
// 	for (int k = l ; k <= p; k++) exch(a, k, j--);
// 	for (int k = r - 1; k >= q; k--) exch(a, k, i++);
// 	sort3ways(a, l, j);
// 	sort3ways(a, i, r);
// }

void* memcpy(void* region1, const void* region2, size_t n) {
	const char* first = (const char*) region2;
	const char* last = ((const char*) region2) + n;
	char* result = (char*) region1;
	while (first != last) *result++ = *first++;
	return result;
}

// void gswap(void *a, void *b, size_t s){
//   	void *temp = malloc(s);
// 	memcpy(temp, b, s);
// 	memcpy(b, a, s);
// 	memcpy(a, temp, s);
// 	free(temp);
// }

// void gswap(void *va, void *vb, size_t s)
// {
//   	char t, *a = (char*)va, *b = (char*)vb;
//   	while(s--)
//     t = a[s], a[s] = b[s], b[s] = t;
// }

int int_compare(void *x, void *y) {
	int m, n;
	m = *((int*)x);
	n = *((int*)y); 
	if ( m == n ) return 0;
	return m > n ? 1: -1;
}

// void sort_gen_void(void *a, int size, int l, int r, int (*compare)(void*, void*)){
// 	if (r < l) return;
// 	int i = l-1, j = r;
// 	int p = l-1, q = r;
// 	while(1){
// 		while (compare((char*)a+(++i)*size, (char*)a+r*size) < 0);
// 		while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0) if (j == l) break;
// 		if (i >= j) break;
// 		gswap((char*)a+i*size, (char*)a+j*size, sizeof(int));
// 		if (compare((char*)a+i*size, (char*)a+r*size) == 0) {
// 			p++;
// 			gswap((char*)a+p*size, (char*)a+i*size, sizeof(int));
// 		}
// 		if (compare((char*)a+j*size, (char*)a+r*size) == 0) {
// 			q--;
// 			gswap((char*)a+j*size, (char*)a+q*size, sizeof(int));
// 		}
// 	}
// 	gswap((char*)a+i*size, (char*)a+r*size, sizeof(int));
// 	j = i - 1;
// 	for (int k = l; k < p; k++, j--)
// 	{
// 		gswap((char*)a+k*size, (char*)a+j*size, sizeof(int));
// 	}
// 	i = i + 1;
// 	for (int k = r-1; k > q; k--, i++)
// 	{
// 		gswap((char*)a+i*size, (char*)a+k*size, sizeof(int));
// 	}
// 	sort_gen_void(a, size, l, j, compare);
// 	sort_gen_void(a, size, i, r, compare);
// }

void SwapInArrayG(void * arr, size_t size, int a, int b) {
    void * temp = malloc(size);
    if (size > 0) {
      assert(temp);
      assert(a >= 0 && b >= 0);
      memcpy(temp, (char *)arr + size*a, size);
      memcpy((char *)arr + size*a, (char *)arr + size*b, size);
      memcpy((char *)arr + size*b, temp, size);
    }
    free(temp);  
}

void sort(void* a, size_t size, int l, int r, 
                   int (*compare)(void*, void*)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
		while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
            if (j == l) break;
		if (i >= j) break;
		SwapInArrayG(a, size, i, j);
		if (compare((char*)a+i*size, (char*)a+r*size)==0)
		   SwapInArrayG(a, size, ++p, i);
		if (compare((char*)a+j*size, (char*)a+r*size)==0)
		   SwapInArrayG(a, size, --q, j);
	}
	SwapInArrayG(a, size, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) SwapInArrayG(a, size, k, j--);
	for (int k = r-1; k >= q; k--) SwapInArrayG(a, size, k, i++);
	sort(a, size, l, j, compare);
	sort(a, size, i, r, compare);
}



Jval new_jval_i(int i) { Jval j; j.i = i; return j; }
Jval new_jval_l(long l) { Jval j; j.l = l; return j; }
Jval new_jval_f(float f) { Jval j; j.f = f; return j; }
Jval new_jval_d(double d) { Jval j; j.d = d; return j; }
Jval new_jval_v(void *v) { Jval j; j.v = v; return j; }

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }

int compare_i(Jval* a, Jval* b) {
	if (jval_i(*a) == jval_i(*b)) return 0;
	if (jval_i(*a) < jval_i(*b)) return -1;
	else return 1;
}

void jswap(Jval *a, Jval *b){
	Jval temp = *a;
	*a = *b;
	*b = temp;
}

void sort_gen_jval(Jval a[], int l, int r, int (*compare)(Jval*, Jval*)){
	if (r < l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1) {
		while ((compare(&a[++i], &a[r])) < 0);
		while (compare(&a[r], &a[--j]) < 0) if (j == l) break;
		if (i >= j) break;
		jswap(&a[i], &a[j]);
		if (compare(&a[i], &a[r]) == 0) {
			p++;
			jswap(&a[p], &a[i]);
		}
		if (compare(&a[j], &a[r]) == 0) {
			q--;
			jswap(&a[j], &a[q]);
		}
	}
	jswap(&a[i], &a[r]);
    j = i-1;
    for (int k = l; k < p; k++, j--)
        jswap(&a[k], &a[j]);
    i = i+1;
    for (int k = r-1; k > q; k--, i++)
        jswap(&a[i], &a[k]);
    sort_gen_jval(a, l, j, compare);
    sort_gen_jval(a, i, r, compare);
}

void printarr(int a[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d  ", a[i]);
    printf("\n");
}

int *createArray(int size){
	int *arr;
	arr = (int*)malloc(size * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % size + 1;
	}
	return arr;
}

Jval *create_array_i(int size) {
	Jval *arr = (Jval*)malloc(sizeof(Jval) * size);
	srand(time(NULL));
	for (int i = 0; i < size; i++) arr[i] = new_jval_i(rand() % ARR_SIZE + 1);
	return arr;
}

void printJval_i(Jval a[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d  ", a[i].i);
	printf("\n");	
}

int main()
{
    //int a[ARR_SIZE];
    // int *a;
    // a = createArray(ARR_SIZE);
    time_t start,end;
    start = clock();
    Jval *a = create_array_i(ARR_SIZE);
    //sort_gen_void(a, sizeof(int), 0, ARR_SIZE - 1, int_compare);
    // sort(a, sizeof(int), 0, ARR_SIZE - 1, int_compare);
    sort_gen_jval(a, 0, ARR_SIZE - 1, compare_i);
    end = clock();
    float interval = (float)(end - start)/CLOCKS_PER_SEC;
    printJval_i(a, ARR_SIZE);
    //printarr(a, ARR_SIZE);
    printf("Completed after: %.20fs\n", interval);
    free(a);
    return 0;
}