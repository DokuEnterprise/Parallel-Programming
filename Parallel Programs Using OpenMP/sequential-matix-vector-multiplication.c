#include <stdio.h>
#include <stdlib.h>
#include <omp.h>   // This is the OpenMP API

void mxv(int m, int n, double * restrict a,
    double * restrict b, double * restrict c);

int main(int argc, char *argv[])
{
    double *a,*b,*c;
    int i, j, m, n;
    printf("Please give m and n: ");
    scanf("%d %d",&m,&n);

    // Allocation of Variables
    if ( (a=(double *)malloc(m*sizeof(double))) == NULL)
        perror("memory allocation for a");
    if ( (b=(double *)malloc(m*n*sizeof(double))) == NULL )
        perror("memory allocation for b");
    if ( (c=(double *)malloc(n*sizeof(double))) == NULL )
        perror("memory allocation for c");
    
    // Initilization of matrix B and vector C
    printf("Initializing matrix B and vector c\n");

    //Vector
    #pragma omp parallel for(defualt)
        for (j=0; j<n; j++)
            c[j] = 2.0;
    //Matrix

    for (i=0; i<m; i++)
        #pragma omp parallel for(defualt)
            for (j=0; j<n; j++)
                b[i*n+j] = i;

    printf("Executing mxv function for m = %d n = %d\n",m,n);
    (void) mxv(m, n, a, b, c);

    free(a);free(b);free(c);
    return(0);
}

void mxv(int m, int n, double * restrict a,
    double * restrict b, double * restrict c)
{
    /* 
    PRE-CONDITION: Takes in the dimensions

    POST CONDITION: The last loop computes the
    dotproduct of row i of matrix b with vector c.
    The result is stored in element i of vector a.*/

    /* Default parallel loop with shared variables 
    and thread private variables i and j. Uncomment to activate*/

    #pragma omp parallel for(defualt) shared(a, b, c, n, m) \
        private(i, j)
        int i, j;
        for (i=0; i<m; i++)
        {
            a[i] = 0.0;
            for (j=0; j<n; j++)
                a[i] += b[i*n+j]*c[j];
        }
}

