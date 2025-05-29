#include <stdio.h>
#include <string.h>

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
    if (*total >= MAX) return;
    int i = busca(c, *total, numero);
    if (i != -1) {
        printf("Conta ja cadastrada\n");
        return;
    }
    c[*total].numero = numero;
    scanf(" %[^\n]", c[*total].nome);
    scanf(" %[^\n]", c[*total].cpf);
    scanf(" %[^\n]", c[*total].telefone);
    scanf("%f", &c[*total].saldo);
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
        return;
    }
    float valor;
    scanf("%f", &valor);
    c[i].saldo += valor;
}

void sacar(Conta c[], int total, int numero) {
    int i = busca(c, total, numero);
    if (i == -2 || i == -1) {
        printf("Conta nao encontrada\n");
        return;
    }
    float valor;
    scanf("%f", &valor);
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
    int op, tipo, numero;

    do {
        scanf("%d", &op);
        if (op == 0) break;
        scanf("%d", &tipo);
        Conta *c = (tipo == 1) ? corrente : poupanca;
        int *t = (tipo == 1) ? &totalC : &totalP;

        if (op >= 1 && op <= 4) scanf("%d", &numero);

        if (op == 1) cadastrar(c, t, numero);
        if (op == 2) consultar(c, *t, numero);
        if (op == 3) depositar(c, *t, numero);
        if (op == 4) sacar(c, *t, numero);
        if (op == 5) exibir(c, *t);
    } while (1);

    return 0;
}

