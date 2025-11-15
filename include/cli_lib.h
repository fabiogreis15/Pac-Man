#ifndef CLI_LIB_H
#define CLI_LIB_H

#include <stdint.h>

void cli_init();
void cli_shutdown();
int cli_getch_nonblocking(); // -1 if none
void cli_clear();
void cli_draw_text(int x, int y, const char *s);
void cli_draw_char(int x, int y, char c);
void cli_refresh();
void cli_sleep_ms(int ms);

#endif // CLI_LIB_H