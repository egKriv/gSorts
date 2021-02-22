#include <stdio.h>
#include <math.h>


int cmps(double a, double b);
void swap(double* a, double* b);


int comparison_count = 0;
int swap_count = 0;

int main (void)
{
    FILE *fp;
    int i;
    double a, b;
    char name[] = "cmpExamples.txt";
    if ((fp = fopen(name, "r")) == NULL)
    {
        printf("Не удалось открыть файл");
        getchar();
        return 0;
    }
    for(i = 0; i< 5; i++)
    {
        fscanf(fp, "%lf", &a);
        fscanf(fp, "%lf", &b);

        printf("%d\n", cmps(a, b));
    }
    fclose(fp);
    return 0;
}


int cmps(double a, double b)
{
    //note each comparison
    comparison_count++;
    //return if |a|>|b| or |a|=|b| or |a|<|b|.
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
