#include "../include/enemy.h"
#include <stdlib.h>
#include <math.h>

Enemy *enemy_create(int x, int y, EnemyType t) {
    Enemy *e = malloc(sizeof(Enemy));
    e->x = x; e->y = y; e->type = t; e->alive = 1; e->next = NULL;
    return e;
}

void enemy_free_all(Enemy *head) {
    while (head) {
        Enemy *n = head->next;
        free(head);
        head = n;
    }
}

// Simple recursive update: traverse list and update each enemy.
void enemy_update_recursive(Enemy **head, int px, int py, int depth) {
    if (!head || !*head) return;
    Enemy *e = *head;
    // For recursion depth safety, stop if depth large
    if (depth > 1000) return;

    // Behavior based on type
    int dx = 0, dy = 0;
    switch (e->type) {
        case ENEMY_AND:
            // move only if both conditions: distance > 1 AND random parity
            if (abs(e->x - px) + abs(e->y - py) > 1) {
                dx = (e->x < px) - (e->x > px);
                dy = (e->y < py) - (e->y > py);
            }
            break;
        case ENEMY_OR:
            // move if either condition: x diff > y diff OR random
            if (abs(e->x - px) >= abs(e->y - py)) {
                dx = (e->x < px) - (e->x > px);
            } else {
                dy = (e->y < py) - (e->y > py);
            }
            break;
        case ENEMY_NOT:
            // move away from player
            dx = (e->x > px) - (e->x < px);
            dy = (e->y > py) - (e->y < py);
            break;
        case ENEMY_IMPLIES:
            // unpredictable: alternate between chasing and random step
            if ((e->x + e->y) % 2 == 0) {
                dx = (e->x < px) - (e->x > px);
                dy = (e->y < py) - (e->y > py);
            } else {
                dx = ((rand()%3)-1);
                dy = ((rand()%3)-1);
            }
            break;
    }

    e->x += dx; e->y += dy;
    // recursively update rest
    enemy_update_recursive(&e->next, px, py, depth + 1);
}