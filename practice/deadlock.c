#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    int process_rank, comm_size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double data = 100;
    int tag = 1;
    if(rank == 0){
        MPI_Ssend( &data, 1, MPI_DOUBLE, 1, tag , MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
    }else{
        MPI_Ssend( &data, 1, MPI_DOUBLE, 1, tag , MPI_COMM_WORLD);
        MPI_Recv(&data, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
    }
    MPI_Finalize();
    return 0;
}