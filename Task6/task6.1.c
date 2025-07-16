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
#include <stdlib.h>
#include <string.h>

struct abonent {
  char name[10];
  char second_name[10];
  char tel[10];
  struct abonent *prev;
  struct abonent *next;
};

struct abonent *CreateNode(char *new_name, char *new_second_name,
                           char *new_tel) {
  struct abonent *new_node = (struct abonent *)malloc(sizeof(struct abonent));

  if (new_node == NULL) {
    perror("Error of memory");
    exit(EXIT_FAILURE);
  }

  strcpy(new_node->name, new_name);
  strcpy(new_node->second_name, new_second_name);
  strcpy(new_node->tel, new_tel);

  return new_node;
}
// будем добавлять абонентов в начало списка, чтобы сложность алгоритма была
// О(1)
int Add(struct abonent **head) {
  char abonent[30];
  char new_name[10];
  char new_second_name[10];
  char new_tel[10];

  printf("Enter name and second_name, and telephone: \n");

  fgets(abonent, sizeof(abonent), stdin);
  // while( getchar() != '\n') {}

  if (sscanf(abonent, "%9s %9s %9s", new_name, new_second_name, new_tel) != 3) {
    printf("You wrote without spaces\n");
    return 1;
  }

  struct abonent *new_node = CreateNode(new_name, new_second_name, new_tel);

  // если это первый элемент списка
  if (*head == NULL) {
    new_node->prev = NULL;
    new_node->next = NULL;

    *head = new_node;  // указатель на структуру стал равен первому элементу
                       // теперь можно обращаться как head->next, head->prev
  } else {  // если не первый элемент списка
    new_node->prev = NULL;
    new_node->next = *head;
    (*head)->prev = new_node;

    *head = new_node;
  }

  return 0;
}

int Delete(struct abonent **head) {
  char abonent[30];
  char new_name[10];
  char new_second_name[10];
  char new_tel[10];

  printf("Enter name and second_name, and telephone: \n");

  fgets(abonent, sizeof(abonent), stdin);
  // while( getchar() != '\n') {}

  if (sscanf(abonent, "%9s %9s %9s", new_name, new_second_name, new_tel) != 3) {
    printf("You wrote without spaces\n");
    return 1;
  }

  while (head != NULL) {
    if (strcmp(head->name, find_name) == 0) {
      printf("name[%d]=%s\tsecond_name[%d]=%s\ttel[%d]=%s\n", head->name,
             head->second_name, head->tel);
    }
    head = head->next;
  }
}

void Find(struct abonent *head) {
  if (head == NULL) {
    printf("The list is empty\n");
    return;
  }

  char find_name[10];
  printf("Enter the name:\n");
  scanf("%9s", find_name);
  while (getchar() != '\n');

  while (head != NULL) {
    if (strcmp(head->name, find_name) == 0) {
      printf("name[%d]=%s\tsecond_name[%d]=%s\ttel[%d]=%s\n", head->name,
             head->second_name, head->tel);
    }
    head = head->next;
  }
}

void PrintAll(struct abonent *head, int count) {
  if (head == NULL) {
    printf("The list is empty\n");
    return;
  }

  while (head != NULL) {
    printf("name[%d]=%s\tsecond_name[%d]=%s\ttel[%d]=%s\n", count, head->name,
           count, head->second_name, count, head->tel);
    count--;
    head = head->next;
  }
}

void ClearMemory(struct abonent **head) {
  if (*head == NULL) {
    return;
  }

  while ((*head)->next != NULL) {
    *head = (*head)->next;
    free((*head)->prev);
  }
  free(*head);
  *head = NULL;
}

int main(void) {
  char menu = 0;
  int count = 0;                // кол-во абонентов
  struct abonent *head = NULL;  // указатель на первый элемент
  struct abonent *tail = NULL;  // указатель на последний элемент

  while (menu != '5') {
    printf(
        "\t\tEnter number of list:\n"
        "\t\t1-Add abonent;\n"
        "\t\t2-Delete abonent;\n"
        "\t\t3-Find abonent;\n"
        "\t\t4-Print all abonents;\n"
        "\t\t5-Exit\n");

    menu = getchar();
    while (getchar() != '\n');
    switch (menu) {
      case '1':
        if (Add(&head) == 0) {
          count++;
        }
        break;
      case '2':
        Delete();
        count--;
        break;
      case '3':
        Find(head);
        break;
      case '4':
        PrintAll(head, count);
        break;
      case '5':
        printf("Exit of programm...\n");
        ClearMemory(&head);
        return 0;
        break;
      default:
        printf("Wrong switch, please repeat\n");
        break;
    }
  }

  return 0;
}
