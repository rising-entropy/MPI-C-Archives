/*
 * There are some simplifications here. The main one is that matrices B and C 
 * are fully allocated everywhere, even though only a portion of them is 
 * used by each processor (except for processor 0)
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2048			/* Size of matrices */

long A[SIZE][SIZE], B[SIZE], C[SIZE];

void fill_matrix(long m[SIZE][SIZE])
{
  static long n=1;
  long i, j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      m[i][j] = n++;
}

void fill_vector(long m[SIZE])
{
  static long n=1;
  long i;
  for (i=0; i<SIZE; i++)
    m[i] = n++;
}

void print_matrix(long m[SIZE][SIZE])
{
  long i, j = 0;
  for (i=0; i<SIZE; i++) {
    printf("\n\t| ");
    for (j=0; j<SIZE; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
  long myrank, P, from, to, i, j, k;
  long tag = 666;		/* any value will do */
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);	/* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &P); /* number of processors */

  /* Just to use the simple variants of MPI_Gather and MPI_Scatter we */
  /* impose that SIZE is divisible by P. By using the vector versions, */
  /* (MPI_Gatherv and MPI_Scatterv) it is easy to drop this restriction. */

  if (SIZE%P!=0) {
    if (myrank==0) printf("Matrix size not divisible by number of processors\n");
    MPI_Finalize();
    exit(-1);
  }

  from = myrank * SIZE/P;
  to = (myrank+1) * SIZE/P;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  if (myrank==0) {
    fill_matrix(A);
    fill_vector(B);
  }

  double start = MPI_Wtime();

  MPI_Bcast (B, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (A, SIZE*SIZE/P, MPI_INT, A[from], SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);

  printf("computing slice %ld (from row %ld to %ld)\n", myrank, from, to-1);
  for (i=from; i<to; i++) {
    long temp = 0;
    for (j=0; j<SIZE; j++) {
        temp += A[i][j]*B[j]; 
    }
    C[i] = temp;
  }
    
  MPI_Gather (C, SIZE/P, MPI_INT, C, SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
  if (myrank==0) {
    double finish = MPI_Wtime();

    // printf("\n\n");
    // print_matrix(A);
    // printf("\n\n\t       * \n");
    // print_matrix(B);
    // printf("\n\n\t       = \n");
    // print_matrix(C);
    // printf("\n\n");

    printf("Exection Time: %f\n", finish - start);
  }

  MPI_Finalize();
  return 0;
}