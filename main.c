#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


int cmps(const void * val1, const void * val2); // compares a and b. return 1 if b should be before a, -1 if a before b, else 0
int rev_cmps(const void * val1, const void * val2);
void swap(double* a, double* b); // swap data in a and b
double* gen_arr(int n, int type); // generate array of n doubles. type defines order: 1 - sorted, 2 - reverse sorted, 3 - unsorted
void print_arr(int n, double* a); // prints array of n doubles
double fRand(void); // generate random double
int isorted(double *a, double *b, int n); // check if a is sorted and equal to b as set
//double* copy_arr(int n, double* a); // create copy of a
int comparison_count = 0;
int swap_count = 0;


int main (void)
{
    long long int t;
    double *a;
    int sizes[1] = {10}, types[4]={1, 2, 3, 3}, i, j;
    srand(time(&t));
    for (i=0; i<1; i++)
    {
        for(j=0; j<4; j++)
        {
            a = gen_arr(sizes[i], types[j]);
            print_arr(sizes[i], a);
            printf("array of %d values over %d type is sorted:%d\n", sizes[i], j, isorted(a, a, sizes[i]));
            free(a);
        }
    }
    printf("counts are %d %d", comparison_count, swap_count);
    return 0;
}


int cmps(const void * val1, const void * val2)
{
    comparison_count++;
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
        qsort(a, n, sizeof(double), cmps);
    comparison_count = cont;
    return a;
    // here should be two ways more
    free(a); // just in case
    return NULL;
}
void print_arr(int n, double* a)
{
    int i;
    for (i=0; i<n; i++)
        printf("%e ", a[i]); // exponential output is more comfortable
    printf("\n");
}
/*void bubblesort(double* a, int m)
{
    int i=0, j=m-1;
    for (; j>0; j--)
    {
        for(i=0; i<j; i++)
        {
            if(cmp(a[i], a[i+1])<0)
            {
                swap(a[i], a[i+1]);
            }
        }
    }
}*/
double fRand(void)
{
    //create 8 random bytes of double
    char c[8] = {rand()%256, rand()%256, rand()%256, rand()%256,
                rand()%256, rand()%256, rand()%256, rand()%256};
    double *f = (double*)c;
    return *f;
}

int isorted(double *a, double *b, int n)
{
    int i, j=0, neg = 0, pos = 0, cont = comparison_count;
    for (i=0; i<n-1; i++)
    {
        comparison_count--;
        if(cmps(&a[i], &a[i+1]) == 1)
            return 0;
        comparison_count--;
        if(cmps(&a[i], &a[i+1]) <= 0) // counting in group of equal absolute values
        {
            if(a[i] < 0)
                neg++;
            else
                pos++;
        }
        comparison_count--;
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
        comparison_count--;
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
