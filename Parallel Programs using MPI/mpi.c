#include <mpi.h>
#include <stdio.h>
#include <math.h>
#define MAXSIZE 1000

void main(int argc, char **argv){
    int myid, numprocs;
    int data[MAXSIZE], i, x, low, high, myresult, result;
    char fn[255];
    char *fp;

    // Let's do some initilization

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if(myid == 0){
        data[0] = 0;
    }
    // Let's brodcast from root to all other processes
    MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Add my portion of data
    x = MAXSIZE/numprocs;
    low = myid * x;
    high = low + x;
    for(i = low; i < high; i++){
        myresult += data[i];
    }
    printf("I got %d from %d\n", myresult, myid);

    // Compute global sum: combine values using MPI_Reduce
    MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    if(myid == 0){ printf("The sum is %d\n", result);}
    MPI_Finalize();
}