// 2. Вывести заданный массив размером N
// в обратном порядке.
// Пример:
// Ввод –> 1 2 3 4 5
// Вывод –> 5 4 3 2 1

#include <stdio.h>

#define N 7

void PrintArray(const int *, int);

int main() {
  int massiv[N];
  int count = 1;
  int i = 0;

  // Ввод символов массива
  do {
    printf("Введите %d-ое число массива\n", count);
    if (scanf("%d", &massiv[i]) == 1) {
      i++;
      count++;
      while ((getchar()) != '\n');
    } else {
      printf("Неправильный ввод\n");
      // fflush(stdin);
      while ((getchar()) != '\n');
    }
  } while (count != (N + 1));
  printf("You writed: ");
  PrintArray(massiv, N);

  // Замена символов массива
  int c = 0;
  for (int i = 0; i < (sizeof(massiv) / sizeof(massiv[0]) / 2 - 0.5); i++) {
    int temp = massiv[i];
    massiv[i] = massiv[N - 1 - i];
    massiv[N - 1 - i] = temp;
    c++;
  }
  printf("New array: ");
  PrintArray(massiv, N);
  printf("\n");
}

// Вывод массива
void PrintArray(const int massiv[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", massiv[i]);
  }
  printf("\n");
}