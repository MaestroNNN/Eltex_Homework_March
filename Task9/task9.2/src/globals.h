#ifndef GLOBALS_H
#define GLOBALS_H

#include <curses.h>
#include <signal.h>

#define LEFT_START_LINE 1
#define LEFT_START_COL 1

extern volatile sig_atomic_t window_too_small;
extern volatile sig_atomic_t resized;
extern WINDOW *up_subwin;
extern WINDOW *left_win;
extern WINDOW *right_win;

#endif