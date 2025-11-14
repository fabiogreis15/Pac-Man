#include "player.h"

void player_init(Player* p, int startX, int startY) {
    p->x = startX;
    p->y = startY;
    p->score = 0;
}

void player_move(Player* p, char input) {
    switch (input) {
        case 'w': p->y--; break;
        case 's': p->y++; break;
        case 'a': p->x--; break;
        case 'd': p->x++; break;
        default: break;
    }
}

