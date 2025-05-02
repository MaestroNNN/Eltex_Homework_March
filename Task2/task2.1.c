/* 1. Вывести квадратную
матрицу по заданному N.
Пример N = 3:
1 2 3
4 5 6
7 8 9 */

#include <stdio.h>

#define N 3

int main() {
  int number = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", number);
      number++;
    }
    printf("\n");
  }
}
