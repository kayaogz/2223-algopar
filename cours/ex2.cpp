#include <cstdio>
#include <omp.h>
#include <unistd.h>
#include <vector>

int main()
{
  std::vector<int> A(100, 0);  // A[i] = i
  int k = 0;



#pragma omp parallel default(none) shared(A, k) num_threads(8)
  {
    int thid = omp_get_thread_num();
    int numth = omp_get_num_threads();
    int klocal = 0;

#pragma omp for 
    for (int i = 0; i < 100; i++)
    {
      A[i] = i;
      klocal = klocal + 1;
      printf("i=%d, thid=%d\n", i, thid);
    } // barriere implicite
#pragma omp critical
      {
        k = k + klocal; // Un seul thread a la fois, les autres attendent a l'entree
      }

//#pragma omp for 
//    for (int i = 0; i < 100; i++)
//    {
//      A[i] = i;
//      k = k + 1
//      printf("i=%d, thid=%d\n", i, thid);
//    } // barriere implicite


//#pragma omp sections
//    {
//#pragma omp section
//      {
//        for (int i = 0; i < 25; i++)
//        {
//          A[i] = i;
//        }
//      }
//#pragma omp section
//      {
//        for (int i = 25; i < 50; i++)
//        {
//          A[i] = i;
//        }
//      }
//#pragma omp section
//      {
//        for (int i = 50; i < 75; i++)
//        {
//          A[i] = i;
//        }
//      }
//#pragma omp section
//      {
//        for (int i = 75; i < 100; i++)
//        {
//          A[i] = i;
//        }
//      }
//    }

  }

  printf("k = %d\n", k);


  return 0;
}





//#pragma omp parallel num_threads(2) default(none) shared(k, A)
//  {
//    int thid = omp_get_thread_num();
//    int numth = omp_get_num_threads();
//    printf("Hello je suis %d/%d\n", thid, numth);
//#pragma omp for reduction(+:k)
//    for (int i = 0; i < 100000; i++) {
//      A[i] = i;
//      k++;
//    }
//  }
//
//  printf("%d\n", k);
//
//  return 0;
//}
