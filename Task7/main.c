/* Задание на статические библиотеки
Реализовать программу калькулятор с функционалом над целыми числами:
сложение, вычитание, умножение, деление. При запуске программы на экране
появляется текстовое меню:
1) Сложение
2) Вычитание
3) Умножение
4) Деление
5) Выход
Далее пользователь вводит номер пункта меню, вводит параметры и на экран
выводится результат выбранной операции. Затем пользователь возвращается в
меню пока не выберет пункт 5.
За отрисовку меню и логику калькулятора отвечает модуль main.c. Функционал
вынесен в статическую библиотеку libcalc.a (каждая операция в отдельном
модуле (add.c, sub.c, mul.c, div.c)). */

#include <stdio.h>

#include "calc.h"

int main(void) {
  int choice, a, b, result;
  char sym;
  while (1) {
    printf("=== Калькулятор ===\n");
    printf("1) Сложение\n");
    printf("2) Вычитание\n");
    printf("3) Умножение\n");
    printf("4) Деление\n");
    printf("5) Выход\n");
    printf("Выберите пункт меню: ");
    if (scanf("%d%c", &choice, &sym) != 2) {
      printf("Ошибка ввода\n");
      break;
    }
    if (sym != ' ' && sym != '\n') {
      printf("Ошибка ввода\n");
      break;
    }

    if (choice == 5) break;

    if (choice < 1 || choice > 5) {
      printf("Некорректный пункт меню!\n");
      continue;
    }
    printf("Введите два целых числа: ");
    if (scanf("%d%d", &a, &b) != 2) {
      printf("Ошибка ввода чисел!\n");
      break;
    }

    switch (choice) {
      case 1:
        result = add(a, b);
        printf("Результат: %d\n", result);
        break;
      case 2:
        result = sub(a, b);
        printf("Результат: %d\n", result);
        break;
      case 3:
        result = mul(a, b);
        printf("Результат: %d\n", result);
        break;
      case 4:
        result = divide(a, b);
        printf("Результат: %d\n", result);
        break;
    }
    printf("\n");
  }

  printf("Выход из программы...!\n");
  return 0;
}
