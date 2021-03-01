#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


void bubblesort(double* a, int m); // sorts a in non-growing order
void heap_sort(double* a, int m); // sorts a in non-growing order
void heapify(double* a, int ind, int n);
void create_heap(double* a, int n);
int isorted(double *a, double *b, int n); // check if a is sorted and equal to b as set
int cmps(const void * val1, const void * val2); // compares a and b. return 1 if b should be before a, -1 if a before b, else 0
int rev_cmps(const void * val1, const void * val2); // compares a and b. return -1 if b should be before a, 1 if a before b, else 0
int cmp(const void * val1, const void * val2); // cmps and increase counter
void swap(double* a, double* b); // swap data in a and b
double* gen_arr(int n, int type); // generate array of n doubles. type defines order: 1 - sorted, 2 - reverse sorted, 3 - unsorted
double fRand(void); // generate random double
void print_arr(int n, double* a); // prints array of n doubles
double* copy_arr(int n, double* a); // create copy of a


int comparison_count = 0;
int swap_count = 0;


int main (void)
{
    long int t;
    double *a, *b, *c, *d;
    int sizes[1] = {10}, types[4]={1, 2, 3, 3}, i, j;
    srand(time(&t));
    for (i=0; i<1; i++)
    {
        for(j=0; j<4; j++)
        {
            a = gen_arr(sizes[i], types[j]);
            print_arr(sizes[i], a);
            printf("array of %d values over %d type is sorted:%d\n", sizes[i], types[j], isorted(a, a, sizes[i]));
            //
            b = copy_arr(sizes[i], a);
            qsort(b, sizes[i], sizeof(double), cmp);
            print_arr(sizes[i], b);
            printf("array of %d values over %d type is sorted after qsort:%d\n", sizes[i], types[j], isorted(b, a, sizes[i]));
            printf("counters are %d %d\n", comparison_count, swap_count);
            comparison_count = 0; swap_count = 0;
            //
            c = copy_arr(sizes[i], a);
            bubblesort(c, sizes[i]);
            print_arr(sizes[i], c);
            printf("array of %d values over %d type is sorted after bubblesort:%d\n", sizes[i], types[j], isorted(c, a, sizes[i]));
            printf("counters are %d %d\n", comparison_count, swap_count);
            comparison_count = 0; swap_count = 0;
            //
            d = copy_arr(sizes[i], a);
            heap_sort(d, sizes[i]);
            print_arr(sizes[i], d);
            printf("array of %d values over %d type is sorted after heapsort:%d\n", sizes[i], types[j], isorted(d, a, sizes[i]));
            printf("counters are %d %d\n", comparison_count, swap_count);
            comparison_count = 0; swap_count = 0;
            //
            free(a);
            free(b);
            free(c);
            free(d);
            printf("***\n");
        }
    }
    printf("counts are %d %d", comparison_count, swap_count);
    return 0;
}

void bubblesort(double* a, int m)
{
    int i=0, j=m-1;
    for (; j>0; j--)
        for(i=0; i<j; i++)
            if(cmp(&a[i], &a[i+1])>0)
                swap(&a[i], &a[i+1]);
}

void heapify(double* a, int i, int n)
{
    int mx=i, l = i*2+1, r = i*2 + 2;
    if (l<n && cmp(a+l, a+i) == 1)
        mx = l;
    if (r<n && cmp(a+r, a+mx) == 1)
        mx = r;
    if (mx != i)
    {
        swap(a+i, a+mx);
        heapify(a, mx, n);
    }
}

void create_heap(double* a, int n)
{
    int i;
    for (i=n/2-1; i>=0; i--)
        heapify(a, i, n);
    printf("---heap created: ");
    print_arr(n, a);
}

void heap_sort(double* a, int n)
{
    int i;
    create_heap(a, n);
    for (i=n-1; i>=0; i--)
    {
        swap(a, a+i);
        heapify(a, 0, i);
    }
}

int isorted(double *a, double *b, int n)
{
    int i, j=0, neg = 0, pos = 0, cont = comparison_count;
    for (i=0; i<n-1; i++)
    {
        if(cmps(&a[i], &a[i+1]) == 1)
            return 0;
        if(cmps(&a[i], &a[i+1]) <= 0) // counting in group of equal absolute values
        {
            if(a[i] < 0)
                neg++;
            else
                pos++;
        }
        if(cmps(&a[i], &a[i+1]) == -1) // if group changed, checking if in b same numbers
        {
            for(j=0; j<n; j++)
                if (cmps(&a[i], &b[j]) == 0)
                {
                    if (b[j] < 0)
                        neg--;
                    else
                        pos--;
                }
            comparison_count = cont;
            if((pos!=0) || (neg!=0))
                return 0;
        }
    }
    if(a[i] < 0) //checking for last group
       neg++;
    else
       pos++;
    for(j=0; j<n; j++)
    {
        if (cmps(&a[i], &b[j]) == 0)
        {
            if (b[j] < 0)
                neg--;
            else
                pos--;
        }
    }
    if((pos!=0) || (neg!=0))
        return 0;
    return 1;
}

int cmps(const void * val1, const void * val2)
{
    double a = *(double*) val1;
    double b = *(double*) val2;
    if (fabs(a) > fabs(b))
        return -1;
    if (fabs(a) < fabs(b))
        return 1;
    return 0;
}

int rev_cmps(const void * val1, const void * val2)
{
    return -cmps(val1, val2);
}

int cmp(const void * val1, const void * val2)
{
    comparison_count++;
    return cmps(val1, val2);
}

void swap(double *a, double *b)
{
    double x = a[0];
    swap_count++;
    a[0] = b[0];
    b[0] = x;
    return;
}

double* gen_arr(int n, int type)
{
    int i, cont = comparison_count;
    double* a = (double*)malloc(n*sizeof(double));
    for (i = 0; i < n; i++) // generate array
        a[i] = fRand();
    //sort if needed
    if(type == 2)
        qsort(a, n, sizeof(double), rev_cmps);
    if (type == 1)
        qsort(a, n, sizeof(double), cmp);
    comparison_count = cont;
    return a;
    if (a!=NULL)
        free(a); // just in case
    return NULL;
}

double fRand(void)
{
    //create 8 random bytes of double
    char c[8] = {rand()%256, rand()%256, rand()%256, rand()%256,
                rand()%256, rand()%256, rand()%256, rand()%256};
    double *f = (double*)c;
    return *f;
}

void print_arr(int n, double* a)
{
    int i;
    for (i=0; i<n; i++)
        printf("%e ", a[i]); // exponential output is more comfortable
    printf("\n");
}

double* copy_arr(int n, double* a)
{
    int i; double *b = (double*)malloc(n*sizeof(double));
    for (i=0; i<n; i++)
    {
        b[i] = a[i];
    }
    return b;
}
