#include <locale.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "draw.h"
#include "globals.h"
#include "move_cursor.h"
#include "read_dir.h"
#include "signall.h"

#define LEFT_START_LINE 1
#define LEFT_START_COL 1

int main(void) {
  setlocale(LC_ALL, "");  // Включение поддержки Unicode
  initscr();
  signal(SIGWINCH, SigWinch);
  cbreak();
  noecho();
  curs_set(1);
  keypad(stdscr, TRUE);
  start_color();
  refresh();

  // Проверка начального размера терминала
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  if (size.ws_col < 80 || size.ws_row < 12) {
    window_too_small = 1;
    werase(stdscr);
    mvprintw(0, 0, "The terminal size is too small (< 80x12). Please resize.");
    refresh();
    sleep(5);
    endwin();
    return 1;
  }

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);  // Цвет выделения

  up_subwin = newwin(1, COLS, 0, 0);
  left_win = newwin(LINES - 1, COLS / 2, 1, 0);
  right_win = newwin(LINES - 1, COLS / 2, 1, COLS / 2);

  Update();
  int count_lines = ReadDir(left_win);  // Инициализация количества строк
  ReadDir(right_win);

  MoveCursor(left_win, right_win,
             count_lines);  // Передача управления в цикл курсора

  endwin();
  return 0;
}
