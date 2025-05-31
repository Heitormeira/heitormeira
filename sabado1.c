#include <stdio.h>
#include <string.h>

// funcao para contar vogais
int contar_vogais(const char *frase) {
    int count = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        char c = frase[i];
        // se for letra maiuscula transforma em minuscula
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        // verifica se e vogal
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

// funcao para colocar a primeira letra de cada palavra em maiuscula
void capitalizar_palavras(char *frase) {
    int novo_inicio = 1;
    for (int i = 0; frase[i] != '\0'; i++) {
        // se encontrar espaco a proxima letra pode ser o inicio de uma palavra
        if (frase[i] == ' ') {
            novo_inicio = 1;
        } else if (novo_inicio && frase[i] >= 'a' && frase[i] <= 'z') {
            frase[i] = frase[i] - 32; // transforma em maiuscula
            novo_inicio = 0;
        } else {
            novo_inicio = 0;
        }
    }
}

int main() {
    char resposta[200];
    // pede para digitar uma frase
    printf("digite uma frase\n");
    // le a frase digitada
    fgets(resposta, sizeof(resposta), stdin);

    // remove o enter do final se existir
    size_t len = strlen(resposta);
    if (len > 0 && resposta[len-1] == '\n') {
        resposta[len-1] = '\0';
    }

    // mostra a frase digitada
    printf("a frase digitada foi %s\n", resposta);

    // conta as vogais
    int vogais = contar_vogais(resposta);
    printf("quantidade de vogais %d\n", vogais);

    // coloca a primeira letra de cada palavra em maiuscula
    capitalizar_palavras(resposta);
    printf("frase com cada palavra iniciando em maiuscula %s\n", resposta);

    return 0;
}
