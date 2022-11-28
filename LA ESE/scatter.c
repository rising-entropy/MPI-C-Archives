// 2019BTECS00058 Devang K

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    // Get the rank and size in the original communicator
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Finalize();
}
