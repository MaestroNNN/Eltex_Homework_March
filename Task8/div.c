#include <stdio.h>

int divide(int a, int b) {
  if (b == 0) {
    printf("Ошибка: Деление на ноль!\n");
    return 0;
  }
  return a / b;
}