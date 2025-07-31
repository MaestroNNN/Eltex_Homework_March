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

#include <dlfcn.h>
#include <stdio.h>

#include "calc.h"

int main(void) {
  int choice, a, b;
  int result;
  char sym;

  void *mylibrary = dlopen("libcalc.so", RTLD_LAZY);
  if (mylibrary == NULL) {
    fprintf(stderr, "dlopen error: %s\n", dlerror());
    return 1;
  }

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

    int (*func_ptr)(int, int) = NULL;  // указатель на функцию
    void *lib_myfunc = NULL;

    switch (choice) {
      case 1:
        lib_myfunc = dlsym(mylibrary, "add");
        break;
      case 2:
        lib_myfunc = dlsym(mylibrary, "sub");
        break;
      case 3:
        lib_myfunc = dlsym(mylibrary, "mul");
        break;
      case 4:
        lib_myfunc = dlsym(mylibrary, "divide");
        break;
    }

    if (lib_myfunc == NULL) {
      fprintf(stderr, "dlsym error: %s\n", dlerror());
      break;
    }

    *(void **)(&func_ptr) = lib_myfunc;

    printf("Результат: %d\n", func_ptr(a, b));

    printf("\n");
  }

  dlclose(mylibrary);

  printf("Выход из программы...!\n");

  return 0;
}
