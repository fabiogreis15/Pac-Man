#include <stdio.h>
#include "cli.h"
#include "player.h"

int main() {
    Player p;
    player_init(&p, 10, 10);

    cli_init();

    while (1) {
        cli_clear();

        printf("Use WASD para mover. Pressione 'q' para sair.\n\n");

        // desenhar jogador em um grid básico 20x20
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                if (x == p.x && y == p.y)
                    printf("@");
                else
                    printf(".");
            }
            printf("\n");
        }

        // leitura não-bloqueante
        if (cli_kbhit()) {
            char c = cli_getch();
            if (c == 'q') break;
            player_move(&p, c);
        }
    }

    cli_reset();
    return 0;
}
