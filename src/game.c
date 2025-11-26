#include "game.h"
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>

// 🎧 INCLUSÕES PARA ÁUDIO VIA SDL_mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/* Macro para detectar paredes no mapa */
#define WALL(ch)  ((ch)==L'║' || (ch)==L'═' || (ch)==L'╔' || (ch)==L'╗' || \
                   (ch)==L'╚' || (ch)==L'╝' || (ch)==L'╬')

/* Inicializa jogo (mapa, áudio, posições) */
void init_game(Game* g) {
    g->score = 0;
    g->game_over = 0;
    g->ghost_move_counter = 0;
    g->music = NULL; // Música começa nula
    
    // --- Inicialização do áudio ---
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "ERRO: SDL Audio: %s\n", SDL_GetError());
    } else {
        int flags = MIX_INIT_MP3;
        if (!(Mix_Init(flags) & flags)) {
            fprintf(stderr, "AVISO: mixer sem suporte MP3: %s\n", Mix_GetError());
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 8192) < 0) {
            fprintf(stderr, "ERRO áudio: %s\n", Mix_GetError());
        } else {
            g->music = Mix_LoadMUS("gorillaz.mp3"); // Carrega música
            if (!g->music)
                fprintf(stderr, "AVISO: música não carregou: %s\n", Mix_GetError());
        }
    }
    // ----------------------------------

    /* Copia layout estático do labirinto */
    const wchar_t *template[MAP_HEIGHT] = {
        L"╔═════════════════════════════════════════╗",
        L"║     ║   ●   ║   ●   ║     ║  ●     ║ ║",
        L"║     ║   ══║     ═╝   ║  ║════       ║",
        L"║   ●           ●         ●           ║",
        L"║  ══╗     ═══════╬══════     ═══     ║",
        L"║    ║     ║             ║           ● ║",
        L"║  ══║ ══   ║   ═══   ║  ══  ║      ║   ║",
        L"║    ║  ●   ║   ●    ║     ║      ║  ║",
        L"║  ══╬══════╬═════════╬══════╬═══      ║",
        L"║     ●         ●             ●     ●   ║",
        L"║  ══        ═════════════════    ═══   ║",
        L"║  ●   ║      ║   ●           ●  ║       ║",
        L"║═══║  ══  ║   ═══   ║  ══  ║   ═══     ║",
        L"║    ║  ●   ║   ●    ║     ║      ║   ║",
        L"║  ═══╬══════╬═════════╬══════╬═══   ║   ║",
        L"║ ●           ●             ●        ║",
        L"║  ═══   ●   ═══════╬════════   ═══   ║",
        L"║ ●           ║       ●             ║",
        L"║     ║  ══  ║       ══    ║  ══  ║   ●  ║",
        L"║ ●   ║    ║   ●     ║      ║    ●     ║",
        L"╚═════════════════════════════════════════╝"
    };

    for (int i = 0; i < MAP_HEIGHT; i++) {
        wcsncpy(g->map[i], template[i], MAP_WIDTH);
        g->map[i][MAP_WIDTH] = L'\0';  // Garantir término da string
    }

    /* Posições iniciais */
    g->pacman.x = 2;  g->pacman.y = 2;

    g->ghosts[0].x = MAP_WIDTH - 4;  g->ghosts[0].y = 2;
    g->ghosts[1].x = MAP_WIDTH - 4;  g->ghosts[1].y = MAP_HEIGHT - 3;
    g->ghosts[2].x = 2;              g->ghosts[2].y = MAP_HEIGHT - 3;
    g->ghosts[3].x = MAP_WIDTH / 2;  g->ghosts[3].y = MAP_HEIGHT / 2;

    srand((unsigned)time(NULL));
}

/* Desenha mapa, Pac-Man, fantasmas e score */
void draw_game(Game* g) {
    clear();

    for (int y = 0; y < MAP_HEIGHT; y++)
        mvaddwstr(y, 0, g->map[y]);

    mvaddwstr(g->pacman.y, g->pacman.x, L"😄");

    for (int i = 0; i < MAX_GHOSTS; i++)
        mvaddwstr(g->ghosts[i].y, g->ghosts[i].x, L"👻");

    mvprintw(MAP_HEIGHT, 0, "Score: %d", g->score);
    refresh();
}

/* Move o Pac-Man caso o alvo não seja parede */
void move_pacman(Game* g, int dx, int dy) {
    int nx = g->pacman.x + dx;
    int ny = g->pacman.y + dy;

    if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT) return;

    wchar_t target = g->map[ny][nx];

    if (!WALL(target)) {
        g->pacman.x = nx;
        g->pacman.y = ny;

        if (target == L'●') {  // Coleta ponto
            g->map[ny][nx] = L' ';
            g->score += 10;
        }
    }
}

/* Fantasmas perseguem Pac-Man a cada 6 ciclos */
void move_ghosts(Game* g) {
    g->ghost_move_counter++;
    if (g->ghost_move_counter % 6 != 0) return;

    for (int i = 0; i < MAX_GHOSTS; i++) {
        int dx = 0, dy = 0;

        // Aproxima na horizontal
        if (g->ghosts[i].x < g->pacman.x) dx = 1;
        else if (g->ghosts[i].x > g->pacman.x) dx = -1;

        // Aproxima na vertical
        if (g->ghosts[i].y < g->pacman.y) dy = 1;
        else if (g->ghosts[i].y > g->pacman.y) dy = -1;

        int nx = g->ghosts[i].x + dx;
        int ny = g->ghosts[i].y + dy;

        if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT) {
            if (!WALL(g->map[ny][nx])) {
                g->ghosts[i].x = nx;
                g->ghosts[i].y = ny;
            }
        }

        // Colisão com Pac-Man
        if (g->ghosts[i].x == g->pacman.x && g->ghosts[i].y == g->pacman.y)
            g->game_over = 1;
    }
}

/* Loop principal do jogo */
void game_run(Game* g) {

    // Toca música em loop
    if (g->music && !Mix_PlayingMusic())
        Mix_PlayMusic(g->music, -1);

    nodelay(stdscr, TRUE);
    int ch;

    while (!g->game_over) {
        ch = getch();

        // Input do jogador
        switch (ch) {
            case KEY_UP:    move_pacman(g, 0, -1); break;
            case KEY_DOWN:  move_pacman(g, 0, 1);  break;
            case KEY_LEFT:  move_pacman(g, -1, 0); break;
            case KEY_RIGHT: move_pacman(g, 1, 0);  break;
            case 'q': g->game_over = 1; break; // Sai do jogo
        }

        move_ghosts(g); // Atualiza inimigos
        draw_game(g);   // Renderiza
        napms(90);      // Pequeno delay
    }

    // --- Libera sistema de áudio ---
    if (g->music) {
        Mix_HaltMusic();
        Mix_FreeMusic(g->music);
        g->music = NULL;
    }
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    // ------------------------------

    // Tela de Game Over
    clear();
    mvprintw(MAP_HEIGHT/2, (MAP_WIDTH/2) - 5, "GAME OVER!");
    mvprintw(MAP_HEIGHT/2 + 1, (MAP_WIDTH/2) - 8, "Final Score: %d", g->score);
    refresh();
    nodelay(stdscr, FALSE);
    getch();
}
