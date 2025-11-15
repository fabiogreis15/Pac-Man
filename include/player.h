#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x, y;
    int score;
    int isAlive;
    int powered; // remaining ticks of power-up
} Player;

void player_init(Player *p, int x, int y);
void player_move(Player *p, int dx, int dy);

#endif // PLAYER_H