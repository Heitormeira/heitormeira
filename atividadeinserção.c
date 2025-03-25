#include <stdio.h>

int main() {
    int vetor[50];
    int tamanho, opcao, valor, posicao, i, j;

    printf("Digite o tamanho do vetor (3 a 50): ");
    scanf("%d", &tamanho);

    if (tamanho < 3 || tamanho > 50) {
        printf("Tamanho invalido.\n");
        return 1;

        
    }

    printf("Digite %d valores ordenados:\n", tamanho);
    for (i = 0; i < tamanho; i++) {
        scanf("%d", &valor);
        if (i == 0 || valor >= vetor[i - 1]) {
            vetor[i] = valor;
        } else {
            printf("Valor deve ser maior ou igual ao anterior.\n");
            i--;
        }
    }

    opcao = -1;
    while (opcao != 0) {
        printf("\nMenu:\n");
        printf("1. Imprimir vetor\n");
        printf("2. Consultar elemento\n");
        printf("3. Remover elemento\n");
        printf("4. Inserir elemento\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Vetor: ");
                for (i = 0; i < tamanho; i++) {
                    printf("%d ", vetor[i]);
                }
                printf("\n");
                break;
            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                posicao = -1;
                int inicio = 0, fim = tamanho - 1, meio;
                while (inicio <= fim) {
                    meio = (inicio + fim) / 2;
                    if (vetor[meio] == valor) {
                        posicao = meio;
                        break;
                    } else if (vetor[meio] < valor) {
                        inicio = meio + 1;
                    } else {
                        fim = meio - 1;
                    }
                }
                printf("Posicao: %d\n", posicao);
                break;
            case 3:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                posicao = -1;
                for (i = 0; i < tamanho; i++) {
                    if (vetor[i] == valor) {
                        posicao = i;
                        break;
                    }
                }
                if (posicao != -1) {
                    for (i = posicao; i < tamanho - 1; i++) {
                        vetor[i] = vetor[i + 1];
                    }
                    tamanho--;
                }
                break;
            case 4:
                if (tamanho >= 50) {
                    printf("Vetor cheio.\n");
                    break;
                }
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                for (i = 0; i < tamanho; i++) {
                    if (vetor[i] > valor) {
                        break;
                    }
                }
                for (j = tamanho; j > i; j--) {
                    vetor[j] = vetor[j - 1];
                }
                vetor[i] = valor;
                tamanho++;
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}