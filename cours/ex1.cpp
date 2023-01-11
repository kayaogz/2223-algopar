#include <cstdio>
#include <omp.h>
#include <unistd.h>

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

int main()
{
  int deux, trois, quatre = -4, cinq, neuf;

  // region sequentiel

#pragma omp parallel default(none) num_threads(3) shared(deux, trois, quatre)
  {
    // region parallele
    
    int thid = omp_get_thread_num();

#pragma omp sections
    {
#pragma omp section
      {
        deux = calcul2();
        printf("deux: th %d\n", thid);
      }
#pragma omp section
      {
        quatre = calcul4();
        printf("quatre: th %d\n", thid);
      }
#pragma omp section
      {
        trois = calcul3();
        printf("trois: th %d\n", thid);
      }
    } // barriere implicite
  } // barriere implicite

  // region sequentiel

  neuf = deux + trois + quatre;

  printf("%d\n", neuf);

  return 0;
}








//#pragma omp parallel num_threads(3) shared(deux, trois, quatre, neuf)
//  {
//    int thid = omp_get_thread_num();
//    int numth = omp_get_num_threads();
//    printf("Hello je suis %d/%d\n", thid, numth);
//
//#pragma omp sections
//    {
//#pragma omp section
//      {
//        trois = calcul3();
//        neuf += trois;
//        printf("Trois est %d\n", trois);
//      }
//#pragma omp section
//      {
//        deux = calcul2();
//        neuf += deux;
//        printf("Deux est %d\n", deux);
//      }
//#pragma omp section
//      {
//        quatre = calcul4();
//        neuf += quatre;
//        printf("Quatre est %d\n", quatre);
//      }
//    }
//    printf("Hello je suis %d/%d\n", thid, numth);
//  }
//  int cinq = deux + trois;
//
//  printf("%d %d %d\n", deux, trois, quatre);
//
//  printf("Neuf est %d\n", neuf);
//
//  return 0;
//}
