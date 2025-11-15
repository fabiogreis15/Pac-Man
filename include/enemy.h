#ifndef ENEMY_H
#define ENEMY_H

typedef enum {
    ENEMY_AND,
    ENEMY_OR,
    ENEMY_NOT,
    ENEMY_IMPLIES
} EnemyType;

typedef struct Enemy {
    int x, y;
    EnemyType type;
    int alive;
    struct Enemy *next;
} Enemy;

Enemy *enemy_create(int x, int y, EnemyType t);
void enemy_free_all(Enemy *head);
void enemy_update_recursive(Enemy **head, int px, int py, int depth);

#endif // ENEMY_H