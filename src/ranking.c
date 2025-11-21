#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RANK 5
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Player;

void update_ranking(int score) {
    Player players[MAX_RANK + 1]; // +1 para novo jogador
    int count = 0;

    // Lê ranking existente
    FILE *file = fopen("ranking.txt", "r");
    if (file) {
        while (fscanf(file, "%s %d", players[count].name, &players[count].score) != EOF && count < MAX_RANK) {
            count++;
        }
        fclose(file);
    }

    // Solicita nome do jogador
    char player_name[NAME_LEN];
    printf("Game Over! Sua pontuacao: %d\n", score);
    printf("Digite seu nome: ");
    scanf("%s", player_name);

    // Adiciona novo jogador
    strcpy(players[count].name, player_name);
    players[count].score = score;
    count++;

    // Ordena do maior para o menor (bubble sort simples)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Escreve top 5 no arquivo
    file = fopen("ranking.txt", "w");
    if (!file) {
        perror("Erro ao abrir ranking.txt");
        return;
    }

    int top = count < MAX_RANK ? count : MAX_RANK;
    printf("\n=== Ranking Top %d ===\n", top);
    for (int i = 0; i < top; i++) {
        fprintf(file, "%s %d\n", players[i].name, players[i].score);
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }

    fclose(file);
}
