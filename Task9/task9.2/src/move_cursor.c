#include "move_cursor.h"

#include <stdio.h>
#include <unistd.h>

#include "globals.h"

void MoveCursor(WINDOW *left_win, WINDOW *right_win, int count_lines) {
  int ch;
  int active_panel = 1;  // 1=правая панель активна, 0=левая
  int move_line = 2;  // Начинаем с первой строки файлов
  int h, w;

  // Начальная инициализация выделения
  if (active_panel == 0) {
    getmaxyx(left_win, h, w);
    mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
    wrefresh(left_win);
  } else {
    getmaxyx(right_win, h, w);
    mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
    wrefresh(right_win);
  }

  while (1) {
    if (window_too_small) {
      usleep(200000);
      continue;
    }

    // Обработка изменения размера
    if (resized) {
      resized = 0;
      if (move_line > count_lines) {
        move_line = count_lines;
      }
      if (active_panel == 0) {
        getmaxyx(left_win, h, w);
        mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
        wrefresh(left_win);
      } else {
        getmaxyx(right_win, h, w);
        mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
        wrefresh(right_win);
      }
    }

    ch = getch();
    switch (ch) {
      case KEY_F(10):
        endwin();
        return;
      case '\t':  // Переключение панелей
        active_panel = 1 - active_panel;
        if (active_panel == 0) {
          getmaxyx(right_win, h, w);
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          wrefresh(right_win);

          getmaxyx(left_win, h, w);
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(left_win);
        } else {
          getmaxyx(left_win, h, w);
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          wrefresh(left_win);

          getmaxyx(right_win, h, w);
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(right_win);
        }
        break;
      case KEY_UP:
        if (active_panel == 0 && move_line > 2) {
          getmaxyx(left_win, h, w);
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          move_line--;
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(left_win);
        } else if (active_panel == 1 && move_line > 2) {
          getmaxyx(right_win, h, w);
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          move_line--;
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(right_win);
        }
        break;
      case KEY_DOWN:
        if (active_panel == 0 && move_line < count_lines) {
          getmaxyx(left_win, h, w);
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          move_line++;
          mvwchgat(left_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(left_win);
        } else if (active_panel == 1 && move_line < count_lines) {
          getmaxyx(right_win, h, w);
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 1, NULL);
          move_line++;
          mvwchgat(right_win, move_line, 2, w - 5, A_NORMAL, 3, NULL);
          wrefresh(right_win);
        }
        break;
      default:
        break;
    }
  }
}