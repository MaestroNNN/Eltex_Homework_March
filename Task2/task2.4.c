// 4. Заполнить матрицу числами от 1 до N
// Пример:
// 1 2 3 4  5
// 16 17 18 19 6
// 15 24 25 20 7
// 14 23 22 21 8
// 13 12 11 10 9

#include <stdio.h>

#define N 5

int main() {
  int my_array[N][N] = {0};

  int left_up = 1;
  int right_up = N;                      // 5
  int right_down = N + (N - 1);          // 9
  int left_down = right_down + (N - 1);  // 13
  int count = 0;

  for (int i = 0; i < (N - 3); i++) {        // 24-25
    for (int i = 0; i < (N - 3); i++) {      // 22-23
      for (int i = 0; i < (N - 3); i++) {    // 20-21
        for (int i = 0; i < (N - 2); i++) {  // 17-19
          for (int i = 1; i < (N + 1); i++) {
            my_array[0][i - 1] = i;                      // 1-5
            my_array[i][N - 1] = right_up + i;           // 6-9
            my_array[N - 1][i - 1] = left_down - i + 1;  // 10-13

            if (my_array[N - i - 1][0] != 1) {  // 14-16
              my_array[N - i - 1][0] = left_down + i;
            }
          }
          my_array[1][i + 1] = my_array[1][0] + 1 + i;
        }
        my_array[i + 2][N - 2] = my_array[1][N - 2] + i + 1;
      }
      my_array[N - 2][N - i - 3] = my_array[N - 2][N - 2] + i + 1;
    }
    my_array[N - 3][i + 1] = my_array[N - 2][N - 4] + i + 1;
  }

  // print_array
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", my_array[i][j]);
    }
    printf("\n");
  }
}