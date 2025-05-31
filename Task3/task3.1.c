// Поменять в целом положительном числе (типа int) значение третьего
// байта на введенное пользователем число (изначальное число также
// вводится с клавиатуры) через указатель (не применяя битовые
// операции).

#include <stdio.h>

int main() {
  int number;
  printf("Введите 1-oe положительное число\n");
  if (((scanf("%d", &number) == 1) && (number > 0)) == 0) {
    printf("Неправильный ввод\n");
    return 1;
  }

  int byte;
  printf("Введите 2-oe положительное число\n");
  if (((scanf("%d", &byte) == 1) && (byte > 0) && (byte < 255)) == 0) {
    printf("Неправильный ввод\n");
    return 1;
  }
  printf("You writed first = %#x, second = %#x \n", number, byte);

  unsigned char char_byte = (unsigned char)byte;
  char *ptr = &number;
  ptr++;
  ptr++;
  *ptr = char_byte;
  printf("NEW first = %#x, second = %#x \n", number, byte);
  return 0;
}