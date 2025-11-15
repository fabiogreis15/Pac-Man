#include "../include/cli_lib.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>

static struct termios oldt;

void cli_init() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void cli_shutdown() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int cli_getch_nonblocking() {
    unsigned char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    if (n <= 0) return -1;
    return (int)c;
}

void cli_clear() {
    printf("\x1b[3J"); // limpa inclusive o scrollback!
    printf("\x1b[2J"); // clear normal
    printf("\x1b[H");  // cursor home
    fflush(stdout);
}

void cli_draw_text(int x, int y, const char *s) {
    printf("\x1b[%d;%dH%s", y+1, x+1, s);
}

void cli_draw_char(int x, int y, char c) {
    printf("\x1b[%d;%dH%c", y+1, x+1, c);
}

void cli_refresh() {
    fflush(stdout);
}

void cli_sleep_ms(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}