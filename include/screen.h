#ifndef SCREEN_H
#define SCREEN_H

void screen_init();
void screen_clear();
void screen_draw_char(int r, int c, char ch);
void screen_draw_str(int r, int c, const char* s);
void screen_refresh();
void screen_end();

#endif
