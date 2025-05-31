/*
Написать программу абонентский справочник. Список абонентов
представляет собой статический массив (100 элементов) из структур
следующего в вида:
struct abonent {
char name[10];
char second_name[10];
char tel[10];
};
При запуске на экран выводится текстовое меню:
1) Добавить абонента
2) Удалить абонента
3) Поиск абонентов по имени
4) Вывод всех записей
5) Выход
и пользователю предлагается ввести пункт меня с клавиатуры. Добавление
абонента в массив реализуется простым заполнением свободной структуры,
при выходе за 100 абонентов уведомить пользователя о переполнении
справочника и не позволять больше добавлять абонентов. При удалении
структура заполняется нулями. При поиске пользователь вводит с клавиатуры
имя абонентов и на экран выводится список всех абонентов с таким же именем.
Программа продолжает выполняться пока пользователь не введет пункт 5. */

#include <stdio.h>
#include <string.h>

struct abonent {
  char name[10];
  char second_name[10];
  char tel[10];
};

struct abonent array[100] = {0};

int Add(void) {
  char abonent[30];
  char new_name[10];
  char new_second_name[10];
  char new_tel[10];
  printf("Enter name and second_name, and telephone: \n");
  if (fgets(abonent, sizeof(abonent), stdin) != NULL) {
    // Если в строке нет символа новой строки — значит строка длиннее 29 символов
    if (strchr(abonent, '\n') == NULL) {
        // Очистка остатка строки из stdin
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    int count = sscanf(abonent, "%9s %9s %9s", new_name, new_second_name, new_tel);
    if (count != 3) {
      printf("You wrote without spaces\n");
      return -1;
    }
  }
  else {
    printf("Error reading input\n");
    return 1;
  }
  int i = 0;
  while (i < 100) {
    if (array[i].name[0] == '\0') {
      strcpy(array[i].name, new_name);
      strcpy(array[i].second_name, new_second_name);
      strcpy(array[i].tel, new_tel);
      printf("The abonent is added\n");
      return 0;
    }
    else {
      i++;
    }
    }
  if (i == 100) {
    printf("The array is full.\n");
    return 1;
  }
}

int Delete(void) {
  char abonent[20];
  char new_name[10];
  char new_second_name[10];
  printf("Enter the name and second_name:\n");
  scanf("%20[^\n]", abonent);
  while (getchar() != '\n');
  int count = sscanf(abonent, "%9s %9s", new_name, new_second_name);
  if (count != 2) {
    printf("Wrong input\n");
    return -1;
  }

  int i = 0;
  while (i < 100) {
    if ((strcmp(array[i].name, new_name) == 0) && (strcmp(array[i].second_name, new_second_name) == 0)) {
      memset(array[i].name, 0, sizeof(array[i].name));
      memset(array[i].second_name, 0, sizeof(array[i].second_name));
      memset(array[i].tel, 0, sizeof(array[i].tel));
      printf("The abonent is deleted\n");
      return 0;
    }
    else {
      i++;
    }
  }
  printf("The abonent is not found\n");
  return -1;
}

int Find(void) {
  char find_name[10];
  printf("Enter the name:\n");
  scanf("%9s", find_name);
  while (getchar() != '\n');

  int i = 0;
  int count = 0;
  while(i < 100) {
    if (strcmp(array[i].name, find_name) == 0) {
      printf("The name %s is found on %d position\n", array[i].name, i);
      count++;
      i++;
    }
    else {
      i++;
    }
  }
  if (count == 0) {
    printf("The name is not found\n");
  }
  return -1;
}

void PrintAll(void) {
  int i = 0;
  while (i < 100) {
    printf("name[%d]=%s\t"
          "second_name[%d]=%s\t"
          "tel[%d]=%s\n",
          i, array[i].name, i, array[i].second_name, i, array[i].tel);
    i++;
  }
}

int main(void) {
  
  char menu = 0;
  while (menu != '5') {
    printf("\t\tEnter number of list:\n"
        "\t\t1-Add abonent;\n"
        "\t\t2-Delete abonent;\n"
        "\t\t3-Find abonent;\n"
        "\t\t4-Print all abonents;\n"
        "\t\t5-Exit\n");

    menu = getchar();
    while (getchar() != '\n');
    switch (menu) {
      case '1': 
        Add();
        //printf("1\n");
        break;
      case '2':
        Delete();
        //printf("2\n");
        break;
      case '3':
        Find();
        //printf("3\n");
        break;
      case '4':
        PrintAll();
        //printf("4\n");
        break;
      case '5':
        printf("Exit of programm...\n");
        return 0; //what is return 0 or 1?
        break;
      default:
        printf("Wrong switch, please repeat\n");
        break;
    } 
  }
}