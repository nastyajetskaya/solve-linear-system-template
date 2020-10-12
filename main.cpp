#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;
int gauss(double *a,double *b,int n);
double f(int k, int n, int i, int j);
double f(int k, int n, int i, int j)
{
    switch (k)
    {
    case 1:
        return n - max(i, j) + 1;
    case 2:
        return max(i, j);
    case 3:
        return max(i - j, j - i);
    case 4:
        return 1. / (i + j + 1);
    default:
        return -1;
    }
}

int main(int argc, char *argv[])
{
    double *a;
    double *b;
    int n;
    int m;
    int k;
    const int five = 5;
    const int four = 4;

    if ((argc != five) && (argc != four))
    {
        printf("Некорректное число параметров\n");
        return -1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    k = atoi(argv[3]);

    a = (double *)malloc(n * n * sizeof(double));
    b = (double *)malloc(n * sizeof(double));

    if ((a == nullptr) || (b == nullptr))
    {
        free(a);
        free(b);
        return -1;
    }

    if (k != 0) // заполнение массива
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[i * n + j] = f(k, n, i, j);
            }
        }
    }
    else
    {
        FILE *fin;

        fin = fopen(argv[4], "r");
        if (fin == nullptr)
        {
            printf("Файл не открылся :( \n");
            free(a);
            free(b);
            return -1;
        }
        for (int i = 0; i < n * n; i++)
        {
            if ((fscanf(fin, "%lf", &a[i])) != 1)
            {
                printf("Некорректные данные\n");
                fclose(fin);
                free(a);
                free(b);
                return -1;
            }
        }
        fclose(fin);
    }
    // заполнение столбца b
    for (int i = 0; i < n; i++)
    {
        b[i] = 0;

        for (int j = 0; j < (n + 1) / 2; j++)
        {
            b[i] = b[i] + a[i * n + 2 * j];
        }
    }

    //вывод массива а на экран
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf(" %10.3e", a[i * n + j]);
        }
        printf("\n");
    }
    free(a);
    free(b);

    return 0;
}

int gauss(double *a,double *b,int n){

    int i=0,j=0,h,l,temp;
    double k;
    double max;
    int var[n];
    double y[n];
    for (int i = 0; i < h; i++)
    {
        var[i] = i;
    }


    for (i=0;i<n;++i)
    {
        max = a[i*n+i];
        h=-1;
        for (j=i;j<n;++j)
        {
            if (fabs(a[j+n*(i)])>fabs(max))
            {
                h=j;
                max = a[j+n*i];
            }
        }
        if (max < 0.000000000000001){
            printf("Вырожденная матрица\n");
            return -1;
        }
        if(h!=i) //хотим поменять местами h и i столбцы
        {
            for (j=i;j<n;++j)
            {
                k=a[h+n*j];
                a[h+n*j]=a[i+n*j];
                a[i+n*j]=k;
            }
            temp = var[i];
            var[i] = var[h];
            var[h] = temp;
        }

        k=a[i+n*(i)];
        for (j=i+1;j<n;j++)
        {
            for (l=i+1;l<n;l++)
            {
                a[l+n*j]=a[l+n*j]-a[l+n*i]*a[i+n*j]/k;
            }
            b[j]=b[j]-b[i]*a[i+n*j]/k;
        }
    }
    for (j=n-1;j>=0;--j)
    {
        for (i=0;i<j;i++)
        {
            b[i]= b[i]-a[j+n*i]*b[j]/a[j+n*j];
        }

    }
    for (i=0;i<n;i++)
    {
        b[i]=b[i]/a[i+i*n];
    } // "вернем" решения на место 
    for (int i = 0; i < n; i++)
    {
        y[i] = b[i];
    }
    for (int i = 0; i < n; i++)
    {
        b[var[i]] = y[i];
    }


    return 0;
}
