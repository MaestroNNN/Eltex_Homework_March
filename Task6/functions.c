#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int Delete(struct abonent **origin_head) {
  if (*origin_head == NULL) {
    printf("The list is empty\n");
    return 1;
  }

  char input[30];
  char name[10], surname[10];

  printf("Enter the name and second_name who will delete:\n");
  fgets(input, sizeof(input), stdin);

  if (sscanf(input, "%9s %9s", name, surname) != 2) {
    printf("You wrote without spaces\n");
    return 1;
  }

  struct abonent *current = *origin_head;

  while (current != NULL) {
    if (strcmp(current->name, name) == 0 &&
        strcmp(current->second_name, surname) == 0) {
      // Удаляем первый
      if (current->prev == NULL)
        *origin_head = current->next;
      else
        current->prev->next = current->next;

      if (current->next) current->next->prev = current->prev;

      free(current);
      printf("The abonent is deleted.\n");
      return 0;
    }

    current = current->next;
  }

  printf("The abonent is not find.\n");
  return 1;
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
      printf("name=%s\tsecond_name=%s\ttel=%s\n", head->name, head->second_name,
             head->tel);
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