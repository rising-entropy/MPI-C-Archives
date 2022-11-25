#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// size of matrix
#define N 1000

void fillMatrix(int *m[N][N]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            m[i][j] = i+j;
        }
    }
}

void fillVector(int *m[N]){
    for(int i=0; i<n; i++){
        m[i] = i;
    }
}

int main(){
    int np, rank, numworkers, rows, i, j, k;

    // a*b = c
    int a[N][N], b[N], c[N];
    fillMatrix(&a);
    fillVector(&b);
    MPI_Status status;



}