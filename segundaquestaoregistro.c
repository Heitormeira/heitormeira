#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 40
#define MAX_DESCRICAO 100

typedef struct {
    int codigo;
    char descricao[MAX_DESCRICAO];
    float valor_unitario;
    int quantidade_estoque;
} Produto;

Produto produtos[MAX_PRODUTOS];
int num_produtos = 0;

int encontrar_produto_indice(int codigo) {
    for (int i = 0; i < num_produtos; i++)
        if (produtos[i].codigo == codigo)
            return i;
    return -1;
}

void limpar_buffer() {
    while (getchar() != '\n');
}

int ler_inteiro(const char* prompt) {
    int valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &valor) == 1) {
            limpar_buffer();
            return valor;
        }
        printf("Entrada invalida. Tente novamente.\n");
        limpar_buffer();
    }
}

float ler_float(const char* prompt) {
    float valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &valor) == 1) {
            limpar_buffer();
            return valor;
        }
        printf("Entrada invalida. Tente novamente.\n");
        limpar_buffer();
    }
}

void cadastrar_novo_produto() {
    if (num_produtos >= MAX_PRODUTOS) {
        printf("Limite maximo de produtos atingido.\n");
        return;
    }

    int codigo;
    do {
        codigo = ler_inteiro("Digite o codigo do produto: ");
        if (encontrar_produto_indice(codigo) != -1)
            printf("Codigo ja existe, digite outro.\n");
        else
            break;
    } while (1);

    produtos[num_produtos].codigo = codigo;

    printf("Digite a descricao do produto: ");
    fgets(produtos[num_produtos].descricao, MAX_DESCRICAO, stdin);
    produtos[num_produtos].descricao[strcspn(produtos[num_produtos].descricao, "\n")] = 0;

    float valor = ler_float("Digite o valor unitario do produto: ");
    produtos[num_produtos].valor_unitario = (valor < 0) ? 0 : valor;

    int qtd = ler_inteiro("Digite a quantidade em estoque: ");
    produtos[num_produtos].quantidade_estoque = (qtd < 0) ? 0 : qtd;

    num_produtos++;
    printf("Produto cadastrado com sucesso!\n");
}

void alterar_valor_unitario() {
    int codigo = ler_inteiro("Digite o codigo do produto para alterar o valor unitario: ");
    int idx = encontrar_produto_indice(codigo);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Produto encontrado: %s\n", produtos[idx].descricao);
    float valor = ler_float("Digite o novo valor unitario: ");
    if (valor < 0) {
        printf("Valor nao pode ser negativo.\n");
    } else {
        produtos[idx].valor_unitario = valor;
        printf("Valor unitario alterado para R$%.2f com sucesso!\n", valor);
    }
}

float informar_valor_unitario(int codigo) {
    int idx = encontrar_produto_indice(codigo);
    return (idx != -1) ? produtos[idx].valor_unitario : -1.0f;
}

int informar_quantidade_estoque(int codigo) {
    int idx = encontrar_produto_indice(codigo);
    return (idx != -1) ? produtos[idx].quantidade_estoque : -1;
}

void realizar_venda() {
    int codigo = ler_inteiro("Digite o codigo do produto para venda: ");
    int idx = encontrar_produto_indice(codigo);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    if (produtos[idx].quantidade_estoque == 0) {
        printf("Produto '%s' com estoque zerado.\n", produtos[idx].descricao);
        return;
    }

    printf("Produto: %s (Estoque: %d)\n", produtos[idx].descricao, produtos[idx].quantidade_estoque);
    int qtd = ler_inteiro("Digite a quantidade desejada: ");
    if (qtd <= 0) {
        printf("Quantidade deve ser maior que zero.\n");
        return;
    }

    if (qtd <= produtos[idx].quantidade_estoque) {
        produtos[idx].quantidade_estoque -= qtd;
        printf("Venda realizada! Total: R$%.2f\n", qtd * produtos[idx].valor_unitario);
        printf("Estoque restante: %d\n", produtos[idx].quantidade_estoque);
    } else {
        printf("Quantidade desejada maior que estoque.\nDeseja comprar o estoque todo? (s/n): ");
        char opc;
        scanf(" %c", &opc);
        limpar_buffer();
        if (tolower(opc) == 's') {
            float total = produtos[idx].quantidade_estoque * produtos[idx].valor_unitario;
            printf("Venda efetuada! Total: R$%.2f\n", total);
            produtos[idx].quantidade_estoque = 0;
        } else {
            printf("Venda cancelada.\n");
        }
    }
}

void atualizar_quantidade_estoque() {
    int codigo = ler_inteiro("Digite o codigo do produto para atualizar o estoque: ");
    int idx = encontrar_produto_indice(codigo);
    if (idx == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    printf("Produto: %s (Estoque atual: %d)\n", produtos[idx].descricao, produtos[idx].quantidade_estoque);

    int qtd = ler_inteiro("Digite a nova quantidade em estoque: ");
    if (qtd < 0) {
        printf("Quantidade nao pode ser negativa.\n");
    } else {
        produtos[idx].quantidade_estoque = qtd;
        printf("Estoque atualizado com sucesso.\n");
    }
}

void exibir_todos_produtos() {
    if (num_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- Produtos Cadastrados ---\n");
    for (int i = 0; i < num_produtos; i++)
        printf("Codigo: %d, Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
}

void exibir_produtos_estoque_zero() {
    int encontrou = 0;
    printf("\n--- Produtos com Estoque Zero ---\n");
    for (int i = 0; i < num_produtos; i++)
        if (produtos[i].quantidade_estoque == 0) {
            printf("Codigo: %d, Descricao: %s\n", produtos[i].codigo, produtos[i].descricao);
            encontrou = 1;
        }
    if (!encontrou) printf("Nenhum produto com estoque zero.\n");
}

int main() {
    int opcao;
    do {
        printf("\n1.Cadastrar produto\n2.Alterar valor\n3.Consultar valor\n4.Consultar estoque\n5.Venda\n6.Atualizar estoque\n7.Listar produtos\n8.Produtos estoque zero\n9.Sair\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch(opcao) {
            case 1: cadastrar_novo_produto(); break;
            case 2: alterar_valor_unitario(); break;
            case 3: {
                int c = ler_inteiro("Codigo para consultar valor: ");
                float v = informar_valor_unitario(c);
                if (v >= 0) printf("Valor unitario: R$%.2f\n", v);
                else printf("Produto nao encontrado.\n");
                break;
            }
            case 4: {
                int c = ler_inteiro("Codigo para consultar estoque: ");
                int q = informar_quantidade_estoque(c);
                if (q >= 0) printf("Quantidade em estoque: %d\n", q);
                else printf("Produto nao encontrado.\n");
                break;
            }
            case 5: realizar_venda(); break;
            case 6: atualizar_quantidade_estoque(); break;
            case 7: exibir_todos_produtos(); break;
            case 8: exibir_produtos_estoque_zero(); break;
            case 9: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 9);
    return 0;
}
