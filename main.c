#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int cmps(double a, double b); // compares a and b. return -1 if b should be before a, 1 if a before b, 0 if no matterr
void swap(double* a, double* b); // swap data in a and b
double* gen_arr(int n, int type); // generate array of n doubles. type defines order: 1 - sorted, 2 - reverse sorted, 3 - unsorted
void print_arr(int n, double* a); // prints array of n doubles
double fRand(void); // generate random double
int comparison_count = 0;
int swap_count = 0;

int main (void)
{
    int n = 10;
    srand(2);
    double *a = gen_arr(n, 3);
    print_arr(n, a);
    free(a);
    return 0;
}


int cmps(double a, double b)
{
    comparison_count++;
    if (abs(a) > abs(b))
        return 1;
    if (abs(a) == abs(b))
        return 0;
    return -1;
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
    int i;
    double* a = (double*)malloc(n*sizeof(double));
    for (i = 0; i < n; i++) // generate array
    {
        a[i] = fRand();
    }
    //sort if needed
    if(type == 3)
    {
        return a;
    }
    // here should be two ways more
    free(a); // just in case
    return NULL;
}
void print_arr(int n, double* a)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("%e ", a[i]); // exponential output is more comfortable
    }
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
