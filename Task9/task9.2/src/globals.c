#include "globals.h"

WINDOW *up_subwin;
WINDOW *left_win;
WINDOW *right_win;

volatile sig_atomic_t window_too_small = 0;
volatile sig_atomic_t resized = 0;  // Флаг изменения размера