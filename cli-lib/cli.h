#ifndef CLI_H
#define CLI_H

// Funções expostas pela CLI-lib

void cli_init();              // Inicializa terminal para leitura instantânea
void cli_reset();             // Reseta terminal ao padrão
int cli_kbhit();              // Retorna 1 se uma tecla foi pressionada
char cli_getch();             // Lê uma tecla sem precisar de ENTER
void cli_clear();             // Limpa a tela

#endif
