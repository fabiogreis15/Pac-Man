#include "cli.h"
#include <conio.h>
#include <stdio.h>

void cli_init() {
    
}

void cli_reset() {
    
}

int cli_kbhit() {
    return _kbhit();  // verifica se uma tecla está pronta
}

char cli_getch() {
    return _getch();  // lê tecla sem precisar de ENTER
}

void cli_clear() {
    // Limpa console ANSI
    printf("\033[2J\033[H");
}
