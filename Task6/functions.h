#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
    struct abonent *prev;
    struct abonent *next;
};

int Add(struct abonent **head);
int Delete(struct abonent **origin_head);
void Find(struct abonent *head);
void PrintAll(struct abonent *head, int count);
void ClearMemory(struct abonent **head);
struct abonent* CreateNode(char *new_name, char *new_second_name, char *new_tel);

#endif 
