#ifndef DRAW_H
#define DRAW_H

#include <curses.h>

void DrawSubwin(WINDOW *subwin);
void DrawUpSubwin(WINDOW *subwin);
void TitleSubwin(WINDOW *subwin);
void DrawUpDir(WINDOW *subwin);
void Update();

#endif