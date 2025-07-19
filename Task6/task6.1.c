/* Программа представляет собой простую реализацию абонентского справочника на
 * языке C с использованием двусвязного списка. Каждая запись в справочнике
 * содержит имя, фамилию и номер телефона абонента. При запуске пользователю
 * отображается текстовое меню, с помощью которого он может добавлять новых
 * абонентов в список, удалять существующих по имени и фамилии, искать абонентов
 * по имени, а также выводить весь список на экран. Добавление новых записей
 * осуществляется в начало списка, что обеспечивает быструю вставку. При
 * удалении запись корректно исключается из списка, связи между узлами
 * пересвязываются, а используемая память освобождается. Реализован поиск по
 * имени, при котором отображаются все совпадающие записи. По завершении работы
 * программы вся выделенная память очищается, предотвращая утечки.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

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
        if (Delete(&head) == 0) {
          count--;
        }
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