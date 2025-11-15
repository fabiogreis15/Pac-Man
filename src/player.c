#include "../include/player.h"
#include <stdlib.h>

void player_init(Player *p, int x, int y) {
    p->x = x;
    p->y = y;
    p->score = 0;
    p->isAlive = 1;
    p->powered = 0;
}

void player_move(Player *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}
