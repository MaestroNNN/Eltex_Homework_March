/*Реализовать файловый менеджер на подобии mc (рисунок 1),
с  функционалом навигации по папкам и двумя панелями
(переключение между панелями через Tab).
Использовать для графики библиотеку ncurses.*/

#include <curses.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define LEFT_START_LINE 1
#define LEFT_START_COL 1

void SigWinch(int signo);
void DrawSubwin(WINDOW *subwin);
void DrawUpSubwin(WINDOW *subwin);

int main(void) {
  initscr();
  signal(SIGWINCH, SigWinch);
  cbreak();  // откл. блокирующий режим ввода символов
  //  noecho(); // откл. отображение символов с клавиатуры
  curs_set(1);  // упр видимостью курсора
  // printw("Current size of terminal is: %d lines x %d cols\n", LINES, COLS);
  scrollok(stdscr, FALSE);  // запрещает прокрутку
  start_color();
  refresh();

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);

  while (1) {
    WINDOW *up_subwin = subwin(stdscr, 1, COLS, 0, 0);
    WINDOW *left_win = newwin(LINES - 1, COLS / 2, 1, 0);
    WINDOW *right_win = newwin(LINES - 1, COLS / 2, 1, COLS / 2);
    DrawSubwin(left_win);
    DrawSubwin(right_win);
    DrawUpSubwin(up_subwin);
    delwin(up_subwin);
    delwin(left_win);
    delwin(right_win);
  }

  getch();
  // delwin(left_win);
  // delwin(right_win);
  endwin();
  return 0;
}

void SigWinch(int signo) {
  // Сообщаем ncurses о изменении размера терминал
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  if (size.ws_col < 80) {
    clear();
    refresh();
    printf("Увеличьте ширину окна\n");
  } else {
    resizeterm(size.ws_row, size.ws_col);
  }
  // clear();
  // refresh();
}

void DrawSubwin(WINDOW *subwin) {
  wattron(subwin, COLOR_PAIR(1));
  wbkgd(subwin, COLOR_PAIR(1));
  box(subwin, '|', '-');

  int height, width;  // высота, ширина
  const char *up_title[] = {".n", "Name", "| Size |",
                            "Modify time"};  // верхний заголовок подокна
  int total_len = 0;  // общая длина строки

  for (int i = 0; i < 4; i++) {
    total_len += strlen(up_title[i]);
  }
  getmaxyx(subwin, height, width);  // получаем ширину окна

  int spaces = (width - total_len - 2) / 2;  // длина пробелов

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

  wrefresh(subwin);
}

void DrawUpSubwin(WINDOW *subwin) {
  wattron(subwin, COLOR_PAIR(2));
  wbkgd(subwin, COLOR_PAIR(2));
  wprintw(subwin, "  Left    File    Command    Options    Right");
  wrefresh(subwin);
}