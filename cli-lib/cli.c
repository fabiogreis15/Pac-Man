#define _POSIX_C_SOURCE 200809L
#include "cli.h"
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h> // Necessário para getchar()

// Verifica se alguma tecla foi pressionada (não bloqueante)
int cli_kbhit() {
    struct timeval tv = {0, 0}; // Timeout imediato
    fd_set fds;
    
    FD_ZERO(&fds);               // Limpa o conjunto
    FD_SET(STDIN_FILENO, &fds);  // Monitora entrada padrão

    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv); // Retorna >0 se tem tecla
}

// Lê um caractere sem precisar apertar Enter
int cli_getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);     // Salva config atual do terminal

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);   // Desativa buffer e eco

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Aplica config temporária

    ch = getchar();                      // Lê tecla imediatamente

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaura terminal

    return ch;
}

// Espera em milissegundos
void cli_sleep_ms(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;                // Converte ms para segundos
    ts.tv_nsec = (ms % 1000) * 1000000;   // Restante em nanossegundos
    nanosleep(&ts, NULL);                 // Pausa a execução
}