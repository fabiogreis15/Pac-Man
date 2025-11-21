#include <ncurses.h>
#include "screen.h"

void screen_init() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(0);
}

void screen_clear() {
    clear();
}

void screen_draw_char(int r, int c, char ch) {
    mvaddch(r, c, ch);
}

void screen_draw_str(int r, int c, const char* s) {
    mvprintw(r, c, "%s", s);
}

void screen_refresh() {
    refresh();
}

void screen_end() {
    endwin();
}
