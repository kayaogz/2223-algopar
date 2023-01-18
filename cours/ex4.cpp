#include <cstdio>
#include <unistd.h>
#include <vector>
#include "mpi.h"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int N;
  std::vector<int> tab;

  if (rank == 0) {
    N = 16;
    tab.resize(N); for (int i = 0; i < N; i++) { tab[i] = 3; }

    MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&tab[N / 2], N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
    for (int i = 0; i < N / 2; i++) { tab[i] = tab[i] + i; }
    MPI_Recv(&tab[N / 2], N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  } else if (rank == 1) {
    MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("rank:%d, N:%d\n", rank, N);
    tab.resize(N / 2);
    MPI_Recv(&tab[0], N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for (int i = 0; i < N / 2; i++) { tab[i] = tab[i] + N / 2 + i; }
    MPI_Send(&tab[0], N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  if (rank == 0) {
    for (int i = 0; i < N; i++) {
      printf("%d ", tab[i]);
    }
    printf("\n");
  }

  MPI_Finalize();

  return 0;
}
