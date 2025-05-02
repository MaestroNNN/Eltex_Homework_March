// 3. Заполнить верхний треугольник матрицы а нижний 0.
// Пример:
// 0 0 1
// 0 1 1
// 1 1 1

// 0 0 0 0 1
// 0 0 0 1 1
// 0 0 1 1 1
// 0 1 1 1 1
// 1 1 1 1 1

#include <stdio.h>

#define N 5

int my_array[N][N] = {0};

// Заполняет переданную строку единицами
void SetArray(int line, int count) {
  for (int i = 0; i < count; i++) {
    my_array[line][N - 1 - i] = 1;
  }
}

int main(void) {
  for (int i = 0; i < N; i++) {
    int count = i + 1;
    SetArray(i, count);
  }

  // print_array
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", my_array[i][j]);
    }
    printf("\n");
  }
}
