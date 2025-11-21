#include <ncurses.h>
#include "keyboard.h"

void keyboard_init() {
    // Inicializado no screen_init
}

int keyboard_getkey_nonblock() {
    return getch();
}

void keyboard_end() {
    // Finalizado no screen_end
}
