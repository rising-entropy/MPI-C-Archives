// 2019BTECS00058 Devang K

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    MPI_Init( int* argc , char*** argv);
    printf("Hello World!\n");
    MPI_Finalize();
}
