#include "draw.h"

#include <stdlib.h>
#include <string.h>

#include "globals.h"

// Отрисовка содержимого окон
void Update() {
  werase(up_subwin);
  werase(left_win);
  werase(right_win);

  DrawUpSubwin(up_subwin);
  DrawSubwin(left_win);
  DrawSubwin(right_win);

  wrefresh(up_subwin);
  wrefresh(left_win);
  wrefresh(right_win);
}

// Отрисовка панели (левая/правая)
void DrawSubwin(WINDOW *subwin) {
  wbkgd(subwin, COLOR_PAIR(1));
  box(subwin, 0, 0);

  DrawUpDir(subwin);
  TitleSubwin(subwin);
}

// Верхняя строка меню
void DrawUpSubwin(WINDOW *subwin) {
  wbkgd(subwin, COLOR_PAIR(2));
  mvwprintw(subwin, 0, 0, "  Left    File    Command    Options    Right");
}

// Путь к текущей директории
void DrawUpDir(WINDOW *subwin) {
  char up_dir[1024];
  char *home = getenv("HOME");

  if (getcwd(up_dir, sizeof(up_dir)) == NULL) {
    perror("getcwd error");
    exit(EXIT_FAILURE);
  }

  if (home && strncmp(up_dir, home, strlen(home)) == 0) {
    mvwprintw(subwin, 0, 1, "~%s", up_dir + strlen(home));
  } else {
    mvwprintw(subwin, 0, 1, "%s", up_dir);
  }
}

// Заголовки колонок (".n", "Name", "Size", "Modify time")
void TitleSubwin(WINDOW *subwin) {
  int height, width;
  const char *up_title[] = {".n", "Name", "| Size |",
                            "Modify time"};  // верхний заголовок подокна
  int total_len = 0;

  for (int i = 0; i < 4; i++) total_len += strlen(up_title[i]);
  getmaxyx(subwin, height, width);

  int spaces = (width - total_len - 2) / 2;

  mvwprintw(subwin, LEFT_START_LINE, LEFT_START_COL, "%s",
            up_title[0]);                                     // .n
  int begin_1_spaces = LEFT_START_COL + strlen(up_title[0]);  // 1 + .n

  for (int i = 0; i < spaces; i++) {
    mvwprintw(subwin, LEFT_START_LINE, begin_1_spaces, " ");
  }

  int begin_Name = begin_1_spaces + spaces;  // 1 +.n + spaces
  mvwprintw(subwin, LEFT_START_LINE, begin_Name, "%s", up_title[1]);

  int begin_2_spaces =
      begin_Name + strlen(up_title[1]);  // 1 + .n + spaces + Name
  for (int i = 0; i < spaces; i++) {
    mvwprintw(subwin, LEFT_START_LINE, begin_2_spaces, " ");
  }

  int begin_Size = begin_2_spaces + spaces;  // 1 + .n + spaces + Name + spaces
  mvwprintw(subwin, LEFT_START_LINE, begin_Size, "%s", up_title[2]);

  int begin_Modify =
      begin_Size +
      strlen(up_title[2]);  // 1 + .n + spaces + Name + spaces + Size
  mvwprintw(subwin, LEFT_START_LINE, begin_Modify, "%s", up_title[3]);
}