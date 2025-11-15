#include "../include/game.h"
#include "../include/cli_lib.h"
#include "../include/enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Map *map = NULL;
static Player player;
static Enemy *enemies = NULL;
static int ticks = 0;

// Small hardcoded map for demo
static const char *layout[] = {
    "#####################",
    "#.......#...#.......#",
    "#.###.#.#.#.#.#.###.#",
    "#O# #.#.#.#.#.#.# #O#",
    "#.# #.#.....#.#.# #.#",
    "#.###.#####.#####.###",
    "#...................#",
    "#####################"
};

void spawn_enemies() {
    enemies = enemy_create(10, 3, ENEMY_AND);
    enemies->next = enemy_create(5, 5, ENEMY_OR);
    enemies->next->next = enemy_create(15, 4, ENEMY_NOT);
}

void draw_map_and_entities() {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            cli_draw_char(x, y, map->grid[y][x]);
        }
    }
    // draw enemies
    Enemy *e = enemies;
    while (e) {
        if (e->alive) cli_draw_char(e->x, e->y, 'G');
        e = e->next;
    }
    // draw player
    cli_draw_char(player.x, player.y, 'P');
}

void process_input_and_move(int key) {
    int dx = 0, dy = 0;
    if (key == 'w' || key == 'W') dy = -1;
    if (key == 's' || key == 'S') dy = 1;
    if (key == 'a' || key == 'A') dx = -1;
    if (key == 'd' || key == 'D') dx = 1;
    int nx = player.x + dx, ny = player.y + dy;
    if (dx || dy) {
        if (map_is_walkable(map, nx, ny)) {
            char tile = map->grid[ny][nx];
            if (tile == TILE_ITEM) { player.score++; map->grid[ny][nx] = TILE_PATH; }
            if (tile == TILE_POWERUP) { player.powered = 50; map->grid[ny][nx] = TILE_PATH; }
            player_move(&player, dx, dy);
        }
    }
}

Enemy *check_enemy_collision() {
    Enemy *e = enemies;
    while (e) {
        if (e->alive && e->x == player.x && e->y == player.y) return e;
        e = e->next;
    }
    return NULL;
}

void game_init() {
    map = map_create_from_strings(layout, sizeof(layout)/sizeof(layout[0]));
    player_init(&player, 1, 1);
    spawn_enemies();
}

void game_run() {
    cli_init();
    while (player.isAlive) {
        cli_clear();
        draw_map_and_entities();
        // HUD
        char hud[80];
        snprintf(hud, sizeof(hud), "Score: %d  Items left: %d  Power: %d  Ticks: %d",
                 player.score,
                 map_count_remaining_items_recursive(map, 0, 0),
                 player.powered,
                 ticks);
        cli_draw_text(0, map->height+1, hud);
        cli_refresh();

        int key = cli_getch_nonblocking();
        if (key == 'q' || key == 'Q') { player.isAlive = 0; break; }
        process_input_and_move(key);

        // update enemies recursively (simple)
        enemy_update_recursive(&enemies, player.x, player.y, 0);

        // check collisions
        Enemy *col = check_enemy_collision();
        if (col) {
            if (player.powered > 0) {
                col->alive = 0;
                player.score += 10;
            } else {
                player.isAlive = 0;
            }
        }

        if (player.powered > 0) player.powered--;

        if (map_count_remaining_items_recursive(map, 0, 0) == 0) {
            // win
            cli_clear();
            cli_draw_text(2,2, "*** Parabens! Você coletou todos os itens! Vitória! ***");
            cli_refresh();
            cli_sleep_ms(2000);
            break;
        }

        ticks++;
        cli_sleep_ms(120);
    }

    // game over screen if player dead
    if (!player.isAlive) {
        cli_clear();
        cli_draw_text(2,2, "*** Game Over ***");
    }
}   // <-- ESTA CHAVE FINAL ESTAVA FALTANDO!
