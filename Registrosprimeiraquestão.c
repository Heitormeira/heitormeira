#include <stdio.h>
#include <string.h>

#define TOTAL_ESTADOS 26

typedef struct {
    char nome[50];
    int veiculos;
    int acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        printf("Digite o nome do estado %d: ", i + 1);
        scanf(" %[^\n]", estados[i].nome);

        printf("Número de veículos: ");
        while (scanf("%d", &estados[i].veiculos) != 1 || estados[i].veiculos < 0) {
            printf("Valor inválido. Digite um número positivo: ");
            while (getchar() != '\n');
        }

        printf("Número de acidentes: ");
        while (scanf("%d", &estados[i].acidentes) != 1 || estados[i].acidentes < 0) {
            printf("Valor inválido. Digite um número positivo: ");
            while (getchar() != '\n');
        }
        printf("\n");
    }
}

void maiorMenorAcidente(Estado estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (int i = 1; i < TOTAL_ESTADOS; i++) {
        if (estados[i].acidentes > estados[*indiceMaior].acidentes)
            *indiceMaior = i;
        if (estados[i].acidentes < estados[*indiceMenor].acidentes)
            *indiceMenor = i;
    }
}

float percentualAcidentes(Estado estado) {
    if (estado.veiculos == 0) return 0;
    return (float)estado.acidentes / estado.veiculos * 100;
}

float mediaAcidentes(Estado estados[]) {
    int soma = 0;
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        soma += estados[i].acidentes;
    }
    return (float)soma / TOTAL_ESTADOS;
}

void estadosAcimaDaMedia(Estado estados[], float media) {
    printf("\nEstados com acidentes acima da média (%.2f):\n", media);
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s: %d acidentes\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[TOTAL_ESTADOS];

    coletarDados(estados);

    int indiceMaior, indiceMenor;
    maiorMenorAcidente(estados, &indiceMaior, &indiceMenor);
    printf("\nMaior número de acidentes: %s (%d)\n", estados[indiceMaior].nome, estados[indiceMaior].acidentes);
    printf("Menor número de acidentes: %s (%d)\n", estados[indiceMenor].nome, estados[indiceMenor].acidentes);

    printf("\nPercentual de veículos envolvidos em acidentes:\n");
    for (int i = 0; i < TOTAL_ESTADOS; i++) {
        printf("%s: %.2f%%\n", estados[i].nome, percentualAcidentes(estados[i]));
    }

    float media = mediaAcidentes(estados);
    printf("\nMédia de acidentes no país: %.2f\n", media);

    estadosAcimaDaMedia(estados, media);

    return 0;
}

}
