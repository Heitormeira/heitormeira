#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_ESTADOS 26
#define MAX_TAM_NOME_ESTADO 50

struct Estado {
    char nome[MAX_TAM_NOME_ESTADO];
    long num_veiculos;
    int num_acidentes;
};

void coletar_dados_estados(struct Estado estados[]) {
    printf("Coletando dados para %d estados brasileiros:\n", NUM_ESTADOS);
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\n--- Estado %d ---\n", i + 1);
        printf("Digite o nome do estado: ");
        scanf("%s", estados[i].nome);

        printf("Digite o numero de veiculos em 2007: ");
        scanf("%ld", &estados[i].num_veiculos);

        printf("Digite o numero de acidentes de transito em 2007: ");
        scanf("%d", &estados[i].num_acidentes);
    }
    printf("\nColeta de dados concluida.\n");
}

void encontrar_min_max_acidentes(const struct Estado estados[], int *idx_max_acidentes, int *idx_min_acidentes) {
    if (NUM_ESTADOS == 0) {
        *idx_max_acidentes = -1;
        *idx_min_acidentes = -1;
        return;
    }

    *idx_max_acidentes = 0;
    *idx_min_acidentes = 0;

    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > estados[*idx_max_acidentes].num_acidentes) {
            *idx_max_acidentes = i;
        }
        if (estados[i].num_acidentes < estados[*idx_min_acidentes].num_acidentes) {
            *idx_min_acidentes = i;
        }
    }
}

float calcular_percentual_acidentes(const struct Estado estados[], int indice_estado) {
    if (indice_estado < 0 || indice_estado >= NUM_ESTADOS || estados[indice_estado].num_veiculos == 0) {
        return 0.0f;
    }
    return ((float)estados[indice_estado].num_acidentes / estados[indice_estado].num_veiculos) * 100.0f;
}

float calcular_media_acidentes_pais(const struct Estado estados[]) {
    if (NUM_ESTADOS == 0) {
        return 0.0f;
    }
    long total_acidentes = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        total_acidentes += estados[i].num_acidentes;
    }
    return (float)total_acidentes / NUM_ESTADOS;
}

void exibir_estados_acima_media(const struct Estado estados[], float media_pais) {
    printf("\nEstados com mais acidentes que a media nacional (%.2f):\n", media_pais);
    int encontrou_algum = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > media_pais) {
            printf("- %s (Acidentes: %d)\n", estados[i].nome, estados[i].num_acidentes);
            encontrou_algum = 1;
        }
    }
    if (!encontrou_algum) {
        printf("Nenhum estado encontrado acima da media nacional.\n");
    }
}

int main() {
    struct Estado estados_brasileiros[NUM_ESTADOS];

    coletar_dados_estados(estados_brasileiros);

    int idx_max, idx_min;
    encontrar_min_max_acidentes(estados_brasileiros, &idx_max, &idx_min);

    if (idx_max != -1 && idx_min != -1) {
        printf("\n--- Estatisticas de Acidentes ---\n");
        printf("Estado com o maior numero de acidentes: %s (%d acidentes)\n",
               estados_brasileiros[idx_max].nome, estados_brasileiros[idx_max].num_acidentes);
        printf("Estado com o menor numero de acidentes: %s (%d acidentes)\n",
               estados_brasileiros[idx_min].nome, estados_brasileiros[idx_min].num_acidentes);
    } else {
        printf("\nNao ha dados suficientes para determinar min/max de acidentes.\n");
    }

    printf("\n--- Percentual de Veiculos Envolvidos em Acidentes por Estado ---\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        float percentual = calcular_percentual_acidentes(estados_brasileiros, i);
        printf("%s: %.2f%%\n", estados_brasileiros[i].nome, percentual);
    }

    float media_nacional_acidentes = calcular_media_acidentes_pais(estados_brasileiros);
    printf("\n--- Media Nacional de Acidentes ---\n");
    printf("Media de acidentes no pais: %.2f\n", media_nacional_acidentes);

    exibir_estados_acima_media(estados_brasileiros, media_nacional_acidentes);

    return 0;
}
