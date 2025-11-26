#include "../include/map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Map *map_create_from_strings(const char **layout, int height) {
    Map *m = malloc(sizeof(Map));            // aloca struct Map
    m->height = height;                      // define altura
    m->width = strlen(layout[0]);            // largura baseada na 1ª linha
    m->grid = malloc(m->height * sizeof(char*)); // aloca linhas do grid

    for (int i = 0; i < m->height; i++) {
        m->grid[i] = malloc(m->width + 1);   // aloca cada linha
        strncpy(m->grid[i], layout[i], m->width); // copia string do layout
        m->grid[i][m->width] = '\0';         // garante null-terminator
    }
    return m;                                // retorna mapa criado
}

void map_free(Map *m) {
    if (!m) return;                           // evita free em NULL
    for (int i = 0; i < m->height; i++)
        free(m->grid[i]);                     // libera cada linha
    free(m->grid);                             // libera vetor de linhas
    free(m);                                   // libera struct Map
}

int map_is_walkable(Map *m, int x, int y) {
    if (x < 0 || y < 0 || x >= m->width || y >= m->height)
        return 0;                              // fora do mapa → não andável

    char c = m->grid[y][x];                    // pega caractere da célula
    return (c != TILE_WALL);                   // só bloqueia se for parede
}

// Conta itens recursivamente percorrendo o grid linha por linha
int map_count_remaining_items_recursive(Map *m, int x, int y) {
    if (y >= m->height) return 0;              // fim do mapa
    if (x >= m->width)                         // fim da linha → próxima
        return map_count_remaining_items_recursive(m, 0, y + 1);

    int count = (m->grid[y][x] == TILE_ITEM);  // soma 1 se for item
    return count + map_count_remaining_items_recursive(m, x + 1, y); // próximo
}
