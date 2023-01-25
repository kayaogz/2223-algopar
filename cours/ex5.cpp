#include <cstdio>
#include <immintrin.h>

int main(int argc, char **argv)
{
  float tab[17] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

//  for (int i = 0; i < 8; i++) {
//    tab[i] = tab[i] + 3 * tab[i];
//  }

  __m256 vec, vectrois;
  vectrois = _mm256_set1_ps(3.0f);
  vec = _mm256_loadu_ps(&tab[0]);
//  vec = _mm256_add_ps(vec, _mm256_mul_ps(vectrois, vec));
  vec = _mm256_fmadd_ps(vectrois, vec, vec); // _mm256_fmadd_ps(x, y, z) -> _mm256_add_ps(z, mm256_mul_ps(x, y))
  _mm256_storeu_ps(&tab[0], vec);
  vec = _mm256_loadu_ps(&tab[8]);
//  vec = _mm256_add_ps(vec, _mm256_mul_ps(vectrois, vec));
  vec = _mm256_fmadd_ps(vectrois, vec, vec);
  _mm256_storeu_ps(&tab[8], vec);
  for (int i = 16; i < 17; i++) { tab[i] = tab[i] + 3 * tab[i]; }


  for (int i = 0; i < 17; i++) {
    printf("%.f ", tab[i]);
  }
  printf("\n");


  return 0;
}
