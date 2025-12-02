#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

void atacar(Territorio *mapa, int at, int df) {
    int dadoAt = rand() % 6 + 1;
    int dadoDf = rand() % 6 + 1;

    printf("\nDado do atacante: %d\n", dadoAt);
    printf("Dado do defensor: %d\n", dadoDf);

    if (dadoAt >= dadoDf) {
        printf("Atacante vence! Defensor perde 1 tropa.\n");
        mapa[df].tropas--;

        if (mapa[df].tropas <= 0) {
            printf("O território '%s' foi conquistado!\n", mapa[df].nome);
            strcpy(mapa[df].cor, mapa[at].cor);
            mapa[df].tropas = 1;
        }

    } else {
        printf("Defensor vence! Nada muda.\n");
    }
}

void mostrarMapa(Territorio *mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i+1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

int main() {
    srand(time(NULL));

    Territorio *mapa = calloc(5, sizeof(Territorio));

    printf("=== Cadastro dos Territórios ===\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i+1);

        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // resolve o bug do ENTER
    }

    int at, df;

    while (1) {
        mostrarMapa(mapa);

        printf("\nEscolha o território atacante (1-5), 0 para sair: ");
        scanf("%d", &at);
        getchar(); // limpa o ENTER

        if (at == 0) break;

        printf("Escolha o defensor (1-5): ");
        scanf("%d", &df);
        getchar();

        atacar(mapa, at-1, df-1);
    }

    free(mapa);
    return 0;
}