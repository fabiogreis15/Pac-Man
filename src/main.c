
#include "game.h"
#include <ncurses.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    Game g;
    init_game(&g);
    game_run(&g);

    endwin();
    return 0;
}
