#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix_t {
  float **data;
  float mult;
  int size;
};

struct Matrix_t *matrix_create(int size) {
  int i;
  struct Matrix_t *a = malloc(sizeof(struct Matrix_t));
  if (a == NULL)
    abort();
  a->size = size;
  a->mult = 1.0;
  a->data = malloc(size * sizeof(float *));
  if (a == NULL)
    abort();
  for (i = 0; i < size; ++i) {
    a->data[i] = malloc(size * sizeof(float));
    if (a->data[i] == NULL)
      abort();
  }
  return a;
}

void matrix_destroy(struct Matrix_t *a) {
  int i;
  for (i = 0; i < a->size; ++i)
    free(a->data[i]);
  free(a->data);
  free(a);
} 

float *matrix_getptr(struct Matrix_t *a, int i, int j) {
  return &(a->data[i][j]);
}

float matrix_read(struct Matrix_t *a, int i, int j) {
  return a->data[i][j];
}

void matrix_write(struct Matrix_t *a, int i, int j, float x) {
  a->data[i][j] = x;
}

int matrix_getelnumber(struct Matrix_t *a, int i, int j) {
  return a->size * i + j;
}

int matrix_getelrow(struct Matrix_t *a, int n) {
  return n / a->size;
}

int matrix_getelcol(struct Matrix_t *a, int n) {
  return n % a->size;
}

void matrix_print(struct Matrix_t *a) {
  int i, j;
  printf("%f\n", a->mult);
  for (i = 0; i < a->size; ++i) {
    for (j = 0; j < a->size; ++j)
      printf("%f ", matrix_read(a, i, j));
    printf("\n");
  }
  printf("\n");
}

void matrix_swaprows(struct Matrix_t *a, int i, int j) {
  float *rowj = a->data[j];
  if (i == j)
    return;
  a->mult *= -1;
  a->data[j] = a->data[i];
  a->data[i] = rowj;
} // depends on the realization of struct Matrix_t

void matrix_swapcols(struct Matrix_t *a, int i, int j) {
  int it;
  float elj;
  if (i == j)
    return;
  a->mult *= -1;
  for (it = 0; it < a->size; ++it) {
    elj = matrix_read(a, it, j);
    matrix_write(a, it, j, matrix_read(a, it, i));
    matrix_write(a, it, i, elj);
  }
}

void matrix_addrowtorow(struct Matrix_t *a, int i, int j, float k) {
  int it;
  for (it = 0; it < a->size; ++it)
    matrix_write(a, i, it, matrix_read(a, i, it) + matrix_read(a, j, it) * k);
}

int matrix_pivotnumber(struct Matrix_t *a, int start) {
  int i, j, nmax;
  float max;
  nmax = matrix_getelnumber(a, start, start);
  max = fabsf(matrix_read(a, start, start));
  for (i = start; i < a->size; ++i)
    for (j = start; j < a->size; ++j)
      if (fabsf(matrix_read(a, i, j)) > max) {
        max = fabsf(matrix_read(a, i, j));
        nmax =  matrix_getelnumber(a, i, j);
      }
  return nmax;
}

int matrix_converttodiagonal(struct Matrix_t *a) {
  int i, j, n;
  //matrix_print(a);
  for (i = 0; i < a->size; ++i) {
    n = matrix_pivotnumber(a, i);
    matrix_swaprows(a, i, matrix_getelrow(a, n));
    matrix_swapcols(a, i, matrix_getelcol(a, n));
    if (matrix_read(a, i, i) == 0)
      return 0;
    //matrix_print(a);
    for (j = i + 1; j < a->size; ++j)
      matrix_addrowtorow(a, j, i, - matrix_read(a, j, i) / matrix_read(a, i, i));
    //matrix_print(a);
  }
  return 1;
} 

float matrix_determinant(struct Matrix_t *a) {
  int i;
  float det;
  if (matrix_converttodiagonal(a) == 0)
    return 0;
  det = a->mult;
  for (i = 0; i < a->size; ++i)
      det *= matrix_read(a, i, i);
  return det;
}

struct Matrix_t *matrix_input() {
  int k, i, size;
  struct Matrix_t *a;
  k = scanf("%d", &size);
  if (k != 1)
    abort();
  a = matrix_create(size);
  for (i = 0; i < size * size; ++i)
    k += scanf("%f", matrix_getptr(a, i / size, i % size));
  if (k != size * size + 1)
    abort();
  return a;
}

int main() {
  struct Matrix_t *a;
  a = matrix_input();
  printf("%ld\n", lroundf(matrix_determinant(a)));
  matrix_destroy(a);
  return 0;
}
