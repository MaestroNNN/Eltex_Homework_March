/* Написать программу, которая создает файл
с именем output.txt,
записывает в него строку “String from file”,
затем считывает ее из файла
с конца и выводит на экран.*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char arr[] = "String from file";

  int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    printf("errno = %d\n", errno);  // выводит числовое значение
    printf("errno (text) = %s\n",
           strerror(errno));  // выводит текстовое описание ошибки
    return 1;
  }

  ssize_t wr = write(fd, arr, strlen(arr));
  if (wr == -1) {
    printf("errno = %d\n", errno);
    perror("Write error");
    close(fd);
    return 1;
  }

  int pos_cursor = strlen(arr) - 1;  // 16 - 1 = 15
  char ch;

  while (pos_cursor != -1) {  // 16,15 ... 0
    off_t pos = lseek(fd, pos_cursor, SEEK_SET);
    ssize_t rd = read(fd, &ch, 1);
    if (rd == -1) {
      printf("errno = %d\n", errno);
      perror("Read error");
      close(fd);
      return 1;
    }
    // printf("pos = %ld, ch = %c\n", pos, ch);
    pos_cursor--;
    putchar(ch);
  }
  printf("\n");

  close(fd);

  return 0;
}