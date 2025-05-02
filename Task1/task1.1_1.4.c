#include <stdio.h>

// Печатает введенное положительное число в двоичном формате.
int PrintPositive(void) {
  int number;

  printf("Введите положительное число\n");

  if ((scanf("%d", &number) == 1) && (number > 0) && (number <= 255)) {
    unsigned char byte_number = (unsigned char)number;

    printf("Вы ввели в десятичном %d = в двоичном ", byte_number);
    for (int i = sizeof(byte_number) * 8 - 1; i >= 0; i--) {
      printf("%d", (byte_number >> i) & 0b00000001);
    }
    printf("\n");
  } else {
    printf("Вы ввели мусор2\n");
  }

  return 0;
}

// Печатает введенное отрицательное число в двоичном формате.
int PrintNegative(void) {
  int number;

  printf("Введите отрицательное число\n");

  if ((scanf("%d", &number) == 1) && (number < 0) && (number >= -128)) {
    char byte_number = (char)number;

    printf("Вы ввели в десятичном %d = в двоичном ", byte_number);
    for (int i = sizeof(byte_number) * 8 - 1; i >= 0; i--) {
      printf("%d", (byte_number >> i) & 0b00000001);
    }
    printf("\n");
  } else {
    printf("Вы ввели мусор3\n");
  }

  return 0;
}

// Считает количество единичных битов в введенном положительном числе.
int SearchBit(void) {
  int number;

  printf("Введите положительное число\n");

  if ((scanf("%d", &number) == 1) && (number > 0) && (number <= 255)) {
    unsigned char byte_number = (unsigned char)number;
    char count = 0;

    printf("Вы ввели в десятичном %d = в двоичном ", byte_number);
    for (int i = sizeof(byte_number) * 8 - 1; i >= 0; i--) {
      printf("%d", (byte_number >> i) & 0b00000001);
    }

    for (int i = 0; i < 8; i++) {
      if (byte_number % 2 == 1) {
        count++;
      }
      byte_number /= 2;
    }

    printf("\nКоличество единиц = %d", count);
    printf("\n");
  } else {
    printf("Вы ввели мусор4\n");
  }

  return 0;
}

// Заменяет третий байт числа на введенное значение.
int ChangeByte(void) {
  int number;
  unsigned int byte;

  printf("Введите два полож. числа через пробел");

  if ((scanf("%d %d", &number, &byte) == 2) && (byte > 0) && (byte <= 255)) {
    unsigned char new_byte = (unsigned char)byte;

    printf("Первое число в десятичном %d = в двоичном ", number);
    for (int i = sizeof(number) * 8 - 1; i >= 0; i--) {
      printf("%d", (number >> i) & 0b00000001);
    }

    printf("\nВторое число в десятичном %d = в двоичном ", new_byte);
    for (int i = sizeof(new_byte) * 8 - 1; i >= 0; i--) {
      printf("%d", (new_byte >> i) & 0b00000001);
    }

    int new_number = (number & 0xFF00FFFF) | (byte << 16);

    printf("\nНовое число в десятичном %d = в двоичном ", new_number);
    for (int i = sizeof(new_number) * 8 - 1; i >= 0; i--) {
      printf("%d", (new_number >> i) & 0b00000001);
    }
    printf("\n");
  } else {
    printf("Вы ввели мусор5\n");
  }

  return 0;
}

// Точка входа в программу. Управляет выбором пользователя.
int main() {
  printf(
      "Выберите программу из списка\n"
      "1 - вывод положительного\n"
      "2 - вывод отрицательного\n"
      "3 - найти количество единиц\n"
      "4 - поменять третий байт\n");

  unsigned int count = 0;
  unsigned int choice;

  while (count != 1) {
    if (scanf("%u", &choice) == 1) {
      switch (choice) {
        case 1:
          PrintPositive();
          count++;
          break;
        case 2:
          PrintNegative();
          count++;
          break;
        case 3:
          SearchBit();
          count++;
          break;
        case 4:
          ChangeByte();
          count++;
          break;
        default:
          printf("Неверный выбор, выберите еще раз\n");
          break;
      }
    } else {
      // Очистка буфера ввода, если введен неверный символ
      while (getchar() != '\n');  // Считываем символы до новой строки
      printf("Вы ввели мусор\n");
    }
  }

  return 0;
}
