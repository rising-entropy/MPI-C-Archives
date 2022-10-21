#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int process_Rank, size_Of_Comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Comm);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    // Get the group of processes in MPI_COMM_WORLD
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    
    printf("Process Rank -  %d of %d and Group - %d\n", process_Rank, size_Of_Comm, world_group.id);

    MPI_Finalize();
    return 0;
}