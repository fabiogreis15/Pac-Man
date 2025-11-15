#ifndef MAP_H
#define MAP_H

#include "enemy.h"

typedef enum {
    TILE_WALL = '#',
    TILE_PATH = ' ',
    TILE_ITEM = '.',
    TILE_POWERUP = 'O',
    TILE_PLAYER = 'P'
} TileType;

typedef struct {
    char **grid;
    int width;
    int height;
} Map;

Map *map_create_from_strings(const char **layout, int height);
void map_free(Map *m);
int map_is_walkable(Map *m, int x, int y);
int map_count_remaining_items_recursive(Map *m, int x, int y);

#endif // MAP_H