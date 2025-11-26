#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RANK 5     // número máximo de jogadores no ranking
#define NAME_LEN 50    // tamanho máximo do nome

// Estrutura simples para armazenar nome e pontuação
typedef struct {
    char name[NAME_LEN];
    int score;
} Player;

void update_ranking(int score) {
    Player players[MAX_RANK + 1]; // +1 para incluir o jogador atual antes de ordenar
    int count = 0;

    // Lê ranking existente do arquivo (se existir)
    FILE *file = fopen("ranking.txt", "r");
    if (file) {
        while (fscanf(file, "%s %d", players[count].name, &players[count].score) != EOF 
               && count < MAX_RANK) {
            count++; // incrementa quantidade lida
        }
        fclose(file);
    }

    // Solicita o nome do jogador atual
    char player_name[NAME_LEN];
    printf("Game Over! Sua pontuacao: %d\n", score);
    printf("Digite seu nome: ");
    scanf("%s", player_name);

    // Adiciona o novo jogador ao vetor
    strcpy(players[count].name, player_name);
    players[count].score = score;
    count++;

    // Ordena ranking do maior para o menor usando bubble sort simples
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];          // troca posição
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Abre arquivo para reescrever ranking
    file = fopen("ranking.txt", "w");
    if (!file) {
        perror("Erro ao abrir ranking.txt"); // mensagem de erro automática
        return;
    }

    // Mantém apenas top 5
    int top = count < MAX_RANK ? count : MAX_RANK;
    printf("\n=== Ranking Top %d ===\n", top);

    // Salva no arquivo e mostra na tela
    for (int i = 0; i < top; i++) {
        fprintf(file, "%s %d\n", players[i].name, players[i].score); // salva no arquivo
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score); // exibe ranking
    }

    fclose(file); // fecha o arquivo
}
