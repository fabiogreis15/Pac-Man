#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
    int score;
} Player;

void player_init(Player* p, int startX, int startY);
void player_move(Player* p, char input);

#endif
