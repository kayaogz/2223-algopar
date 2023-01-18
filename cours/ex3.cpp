#include <cstdio>
#include <unistd.h>
#include "mpi.h"

int calcul2()
{
  sleep(2);
  return 2;
}
int calcul3()
{
  sleep(3);
  return 3;
}

int calcul4()
{
  sleep(4);
  return 4;
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("Hello %d/%d\n", rank, size);

  int deux, trois, quatre, cinq, neuf;

  if (rank == 0) {
    deux = calcul2();
    MPI_Recv(&trois, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cinq = deux + trois;
    MPI_Send(&cinq, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    trois = calcul3();
    MPI_Send(&trois, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Recv(&cinq, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }


  printf("cinq = %d\n", cinq);

  MPI_Finalize();

  return 0;
}
