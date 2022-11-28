#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    MPI_Status status;
    MPI_Init(&argc, &argv);
    int rank, num;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    double data = 100;
    int tag = 1;
    if(rank%2 == 0){
        printf("Sending from Rank %d to Rank %d", rank, (rank+1)%num);
        MPI_Send( &data, 1, MPI_DOUBLE, (rank+1)%num, tag , MPI_COMM_WORLD);
        printf("Receving from Rank %d to Rank %d", (rank-1)%num, rank);
        MPI_Recv(&data, 1, MPI_DOUBLE, (rank-1)%num, tag, MPI_COMM_WORLD, &status);
    }else{
        printf("Receving from Rank %d to Rank %d", (rank-1)%num, rank);
        MPI_Recv(&data, 1, MPI_DOUBLE, (rank-1)%num, tag, MPI_COMM_WORLD, &status);
        printf("Sending from Rank %d to Rank %d", rank, (rank+1)%num);
        MPI_Send( &data, 1, MPI_DOUBLE, (rank+1)%num, tag , MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}