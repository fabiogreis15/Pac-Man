#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
    int lives;
    int score;
} Player;

void init_player(Player *p, int start_x, int start_y);
void move_player(Player *p, char direction);

#endif
