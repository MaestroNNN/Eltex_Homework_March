#include <curses.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define LEFT_START_LINE 1
#define LEFT_START_COL 1

static WINDOW *up_subwin;
static WINDOW *left_win;
static WINDOW *right_win;

volatile sig_atomic_t window_too_small = 0;

void SigWinch(int signo);
void DrawSubwin(WINDOW *subwin);
void DrawUpSubwin(WINDOW *subwin);
void TitleSubwin(WINDOW *subwin);
void DrawUpDir(WINDOW *subwin);
void Update();
void ReadDir(WINDOW *subwin);

int main(void) {
  // printf("PID: %d\n", getpid());
  // getchar();  // или getchar(); чтобы дождаться нажатия клавиши
  initscr();
  signal(SIGWINCH, SigWinch);
  cbreak();  // откл. блокирующий режим ввода символов
  noecho();  // откл. отображение символов с клавиатуры
  curs_set(1);           // упр видимостью курсора
  keypad(stdscr, TRUE);  // вкл. обработку клавиш
  start_color();
  refresh();

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);

  up_subwin = newwin(1, COLS, 0, 0);
  left_win = newwin(LINES - 1, COLS / 2, 1, 0);
  right_win = newwin(LINES - 1, COLS / 2, 1, COLS / 2);
  Update();  // начальная отрисовка

  ReadDir(left_win);
  ReadDir(right_win);
  int ch;
  int active_panel = 0;

  while (1) {
    if (window_too_small) {
      usleep(200000);  // ждать, пока окно увеличится
      continue;
    }

    ch = getch();
    switch (ch) {
      case KEY_F(10):
        endwin();
        return 0;
      case '\t':
        active_panel = 1 - active_panel;
        if (active_panel == 0) {
          wmove(left_win, 2, 1);
          wrefresh(left_win);
          wrefresh(right_win);
        } else {
          wmove(right_win, 2, 1);
          wrefresh(left_win);
          wrefresh(right_win);
        }
        break;
      default:
        continue;
    }
    Update();
  }

  getch();
  endwin();
  return 0;
}

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

// Обработка изменения размера терминала
void SigWinch(int signo) {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);

  if (size.ws_col < 80 || size.ws_row < 5) {
    window_too_small = 1;
    werase(stdscr);
    mvprintw(0, 0, "The terminal size is too small (< 80x5). Please resize.");
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
}

// Отрисовка основной панели (левая/правая)
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

//   int height, width; // высота, ширина
//   const char *up_title[] = {".n", "Name", "| Size |", "Modify time"};
//   getmaxyx(subwin, height, width);

//   int total_len = 0; // общая длина строки
//   for (int i = 0; i < 4; i++) total_len += strlen(up_title[i]);

//   int spaces = (width - total_len - 2) / 3;
//   int x = LEFT_START_COL;

//   for (int i = 0; i < 4; i++) {
//     mvwprintw(subwin, LEFT_START_LINE, x, "%s", up_title[i]);
//     x += strlen(up_title[i]) + spaces;
//   }
// }

void ReadDir(WINDOW *subwin) {
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
    free(namelist[n]);
  }
  free(namelist);

  closedir(dir);
  wrefresh(subwin);
}
