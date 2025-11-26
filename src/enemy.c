#include "../include/enemy.h"
#include <stdlib.h>
#include <math.h>

// Cria um inimigo com posição, tipo e marca como vivo
Enemy *enemy_create(int x, int y, EnemyType t) {
    Enemy *e = malloc(sizeof(Enemy));
    e->x = x; e->y = y; e->type = t; e->alive = 1; e->next = NULL;
    return e;
}

// Libera toda a lista de inimigos
void enemy_free_all(Enemy *head) {
    while (head) {
        Enemy *n = head->next;
        free(head);
        head = n;
    }
}

// Atualiza inimigos recursivamente, um por um
void enemy_update_recursive(Enemy **head, int px, int py, int depth) {
    if (!head || !*head) return;       // Lista vazia
    Enemy *e = *head;

    if (depth > 1000) return;          // Evita recursão profunda demais

    // Movimentação baseada no tipo lógico
    int dx = 0, dy = 0;
    switch (e->type) {
        case ENEMY_AND:
            // Move apenas se distância > 1
            if (abs(e->x - px) + abs(e->y - py) > 1) {
                dx = (e->x < px) - (e->x > px);
                dy = (e->y < py) - (e->y > py);
            }
            break;
        case ENEMY_OR:
            // Move na direção com maior diferença
            if (abs(e->x - px) >= abs(e->y - py)) {
                dx = (e->x < px) - (e->x > px);
            } else {
                dy = (e->y < py) - (e->y > py);
            }
            break;
        case ENEMY_NOT:
            // Se afasta do jogador
            dx = (e->x > px) - (e->x < px);
            dy = (e->y > py) - (e->y < py);
            break;
        case ENEMY_IMPLIES:
            // Alterna entre perseguir e andar aleatório
            if ((e->x + e->y) % 2 == 0) {
                dx = (e->x < px) - (e->x > px);
                dy = (e->y < py) - (e->y > py);
            } else {
                dx = ((rand() % 3) - 1);
                dy = ((rand() % 3) - 1);
            }
            break;
    }

    e->x += dx; e->y += dy;             // Aplica movimento

    // Atualiza o próximo inimigo na lista
    enemy_update_recursive(&e->next, px, py, depth + 1);
}
