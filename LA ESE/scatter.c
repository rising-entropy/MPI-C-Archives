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

    const int recvsize = 10;
    
    int *sendbuf, recvbuf[recvsize];
    int sendsize = world_size*recvsize;
    sendbuf = (int*)malloc(sendsize*sizeof(int));
    for(int i=0; i<recvsize; i++){
        recvbuf[i] = i;
    }

    if(world_rank == 0){
        MPI_Scatter(sendbuf, recvsize, MPI_INT, recvbuf, recvsize, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        MPI_Gather(sendbuf, sendsize, MPI_INT, recvbuf, sendsize, MPI_INT, 0, MPI_COMM_WORLD);
        printf("%d %d", recvbuf[0], recvbuf[1]);
    }

    MPI_Finalize();
}
