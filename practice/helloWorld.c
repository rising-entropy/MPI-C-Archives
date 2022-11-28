#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    int process_rank, comm_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    printf("%d / %d", process_rank, comm_size);
    MPI_Finalize();
    return 0;
}