#include <stdio.h>
#include <string.h>

int main() {
    char stroka[30];
    char podstroka[10];

    printf("Enter the stroka: ");
    scanf("%29[^\n]", stroka);
    while ((getchar()) != '\n');
    if (strlen(stroka) == 0) {
        printf("Wrong stroka");
        return 1;
    }

    printf("Enter the podstroka: ");
    scanf("%9[^\n]", podstroka);
    while ((getchar()) != '\n');
    if (strlen(podstroka) == 0) {
        printf("Wrong podstroka\n");
        return 1;
    }

    char *ptr_stroka = stroka;
    while (*ptr_stroka != '\0') {
        char *check_stroka = ptr_stroka;
        char *ptr_podstroka = podstroka;

        while ((*check_stroka == *ptr_podstroka) && (*ptr_podstroka != '\0')) {
            check_stroka++;
            ptr_podstroka++;
        }

        if (*ptr_podstroka == '\0') {
            printf("Substring found at address: %p\n", (void*)ptr_stroka);
            // printf("Pointer points to: %s\n", ptr_stroka); // Чтобы увидеть содержимое
            return 0;
        }

        ptr_stroka++;
    }

    printf("Substring not found. Result pointer: NULL\n");
    return 0;
}