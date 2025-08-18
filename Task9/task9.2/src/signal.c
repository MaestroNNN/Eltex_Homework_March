#include <sys/ioctl.h>
#include <unistd.h>

#include "draw.h"
#include "globals.h"
#include "read_dir.h"
#include "signall.h"

void SigWinch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);

  if (size.ws_col < 80 || size.ws_row < 12) {
    window_too_small = 1;
    werase(stdscr);
    mvprintw(0, 0, "The terminal size is too small (< 80x12). Please resize.");
    refresh();
    return;
  }

  window_too_small = 0;
  resizeterm(size.ws_row, size.ws_col);

  wresize(up_subwin, 1, COLS);
  wresize(left_win, LINES - 1, COLS / 2);
  wresize(right_win, LINES - 1, COLS / 2);
  mvwin(right_win, 1, COLS / 2);

  Update();
  int count_lines = ReadDir(left_win);  // Обновляем количество строк
  ReadDir(right_win);
  resized = 1;  // Устанавливаем флаг для перерисовки курсора
}