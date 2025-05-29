#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int numero;
    char nome[100];
    char cpf[20];
    char telefone[20];
    float saldo;
} Conta;

int busca(Conta c[], int total, int numero) {
    if (total == 0) return -2;
    for (int i = 0; i < total; i++)
        if (c[i].numero == numero)
            return i;
    return -1;
}

void cadastrar(Conta c[], int *total, int numero) {
    if (*total >= MAX) {
        char buffer[256];
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        return;
    }
    int i = busca(c, *total, numero);
    if (i != -1) {
        printf("Conta ja cadastrada\n");
        char buffer[256];
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        fgets(buffer, sizeof(buffer), stdin);
        return;
    }
    
    fgets(c[*total].nome, sizeof(c[*total].nome), stdin);
    c[*total].nome[strcspn(c[*total].nome, "\n")] = 0;

    fgets(c[*total].cpf, sizeof(c[*total].cpf), stdin);
    c[*total].cpf[strcspn(c[*total].cpf, "\n")] = 0;

    fgets(c[*total].telefone, sizeof(c[*total].telefone), stdin);
    c[*total].telefone[strcspn(c[*total].telefone, "\n")] = 0;

    char buffer_saldo[50];
    fgets(buffer_saldo, sizeof(buffer_saldo), stdin);
    c[*total].saldo = strtof(buffer_saldo, NULL);

    (*total)++;
}

void consultar(Conta c[], int total, int numero) {
    int i = busca(c, total, numero);
    if (i == -2 || i == -1)
        printf("Conta nao encontrada\n");
    else
        printf("Saldo: %.2f\n", c[i].saldo);
}

void depositar(Conta c[], int total, int numero) {
    int i = busca(c, total, numero);
    if (i == -2 || i == -1) {
        printf("Conta nao encontrada\n");
        char buffer[50];
        fgets(buffer, sizeof(buffer), stdin);
        return;
    }
    char buffer_valor[50];
    fgets(buffer_valor, sizeof(buffer_valor), stdin);
    float valor = strtof(buffer_valor, NULL);
    c[i].saldo += valor;
}

void sacar(Conta c[], int total, int numero) {
    int i = busca(c, total, numero);
    if (i == -2 || i == -1) {
        printf("Conta nao encontrada\n");
        char buffer[50];
        fgets(buffer, sizeof(buffer), stdin);
        return;
    }
    char buffer_valor[50];
    fgets(buffer_valor, sizeof(buffer_valor), stdin);
    float valor = strtof(buffer_valor, NULL);

    if (valor > c[i].saldo)
        printf("Saldo insuficiente\n");
    else
        c[i].saldo -= valor;
}

void exibir(Conta c[], int total) {
    for (int i = 0; i < total; i++)
        printf("Conta: %d | Nome: %s | Telefone: %s\n", c[i].numero, c[i].nome, c[i].telefone);
}

int main() {
    Conta corrente[MAX], poupanca[MAX];
    int totalC = 0, totalP = 0;
    char linha[256];
    int op, tipo, numero;

    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        if (sscanf(linha, "%d %d %d", &op, &tipo, &numero) < 2) {
            if (op == 0) break;
            continue;
        }

        if (op == 0) break;

        Conta *c = (tipo == 1) ? corrente : poupanca;
        int *t = (tipo == 1) ? &totalC : &totalP;

        if (op == 1) {
            cadastrar(c, t, numero);
        } else if (op == 2) {
            consultar(c, *t, numero);
        } else if (op == 3) {
            depositar(c, *t, numero);
        } else if (op == 4) {
            sacar(c, *t, numero);
        } else if (op == 5) {
            exibir(c, *t);
        }
    }

    return 0;
}
