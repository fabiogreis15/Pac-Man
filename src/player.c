#include "../include/player.h"
#include <stdlib.h>

void player_init(Player *p, int x, int y) {
    p->x = x;          // posição inicial no eixo X
    p->y = y;          // posição inicial no eixo Y
    p->score = 0;      // inicia pontuação zerada
    p->isAlive = 1;    // jogador começa vivo
    p->powered = 0;    // não começa com power-up ativo
}

void player_move(Player *p, int dx, int dy) {
    p->x += dx;        // atualiza posição horizontal
    p->y += dy;        // atualiza posição vertical
}
