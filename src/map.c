#include "../include/map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Map *map_create_from_strings(const char **layout, int height) {
    Map *m = malloc(sizeof(Map));
    m->height = height;
    m->width = strlen(layout[0]);
    m->grid = malloc(m->height * sizeof(char*));
    for (int i = 0; i < m->height; i++) {
        m->grid[i] = malloc(m->width + 1);
        strncpy(m->grid[i], layout[i], m->width);
        m->grid[i][m->width] = '\0';
    }
    return m;
}

void map_free(Map *m) {
    if (!m) return;
    for (int i = 0; i < m->height; i++) free(m->grid[i]);
    free(m->grid);
    free(m);
}

int map_is_walkable(Map *m, int x, int y) {
    if (x < 0 || y < 0 || x >= m->width || y >= m->height) return 0;
    char c = m->grid[y][x];
    return (c != TILE_WALL);
}

// recursive item counter: walks grid row-major but prevents double counting by bounds only
int map_count_remaining_items_recursive(Map *m, int x, int y) {
    if (y >= m->height) return 0;
    if (x >= m->width) return map_count_remaining_items_recursive(m, 0, y+1);
    int count = (m->grid[y][x] == TILE_ITEM);
    return count + map_count_remaining_items_recursive(m, x+1, y);
}