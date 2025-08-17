#include "read_dir.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int ReadDir(WINDOW *subwin) {
  DIR *dir = opendir(".");
  if (dir == NULL) {
    perror("opendir error");
    exit(EXIT_FAILURE);
  }

  struct dirent **namelist;

  int n = scandir(".", &namelist, NULL, alphasort);
  if (n == -1) {
    perror("scandir");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; ++i) {
    mvwprintw(subwin, i + 1, 3, "%s", namelist[i]->d_name);
    free(namelist[i]);
  }
  free(namelist);

  closedir(dir);
  wrefresh(subwin);

  return n;
}