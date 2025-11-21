#ifndef GAME_H
#define GAME_H

#include <wchar.h>

#define MAP_WIDTH  41
#define MAP_HEIGHT 21
#define MAX_GHOSTS 4

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position pacman;
    Position ghosts[MAX_GHOSTS];
    int score;
    int game_over;
    int ghost_move_counter;
    wchar_t map[MAP_HEIGHT][MAP_WIDTH + 1]; // +1 para '\0'
} Game;

void init_game(Game *g);
void draw_game(Game *g);
void move_pacman(Game *g, int dx, int dy);
void move_ghosts(Game *g);
void game_run(Game *g);

#endif
