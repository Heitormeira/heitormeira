#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_DESC 100
#define MAX_PRODUTOS_POR_VENDA 10

typedef struct {
    int id;
    char descricao[MAX_DESC];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    int idVenda;    
    int produtos[MAX_PRODUTOS_POR_VENDA];
    int totalProdutos;
} Venda;

void cadastrarProduto() {
    Produto p;
    FILE *fp = fopen("produtos.dat", "ab");
    if (fp == NULL) { printf("Erro ao abrir arquivo de produtos.\n"); return; }
    printf("ID: "); scanf("%d", &p.id); getchar();
    printf("Descrição: "); fgets(p.descricao, MAX_DESC, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = 0;
    printf("Preço: "); scanf("%f", &p.preco);
    printf("Quantidade: "); scanf("%d", &p.quantidade);
    fwrite(&p, sizeof(Produto), 1, fp);
    fclose(fp);
    printf("Produto cadastrado!\n");
}

void listarProdutos() {
    Produto p;
    FILE *fp = fopen("produtos.dat", "rb");
    if (fp == NULL) { printf("Nenhum produto cadastrado.\n"); return; }
    printf("\n--- Produtos ---\n");
    while (fread(&p, sizeof(Produto), 1, fp))
        printf("ID: %d | %s | R$%.2f | Estoque: %d\n", p.id, p.descricao, p.preco, p.quantidade);
    fclose(fp);
}

void cadastrarVenda() {
    Venda v;
    FILE *fp = fopen("vendas.dat", "ab");
    if (fp == NULL) { printf("Erro ao abrir arquivo de vendas.\n"); return; }
    printf("ID da venda: "); scanf("%d", &v.idVenda);
    printf("Qtd produtos: "); scanf("%d", &v.totalProdutos);
    if (v.totalProdutos > MAX_PRODUTOS_POR_VENDA) v.totalProdutos = MAX_PRODUTOS_POR_VENDA;
    for (int i = 0; i < v.totalProdutos; i++) {
        printf("ID produto %d: ", i+1);
        scanf("%d", &v.produtos[i]);
    }
    fwrite(&v, sizeof(Venda), 1, fp);
    fclose(fp);
    printf("Venda registrada!\n");
}

void listarVendas() {
    FILE *fpV = fopen("vendas.dat", "rb");
    FILE *fpP = fopen("produtos.dat", "rb");
    if (fpV == NULL || fpP == NULL) { printf("Nenhum registro de vendas ou produtos.\n"); return; }
    Venda v; Produto p;
    printf("\n--- Vendas ---\n");
    while (fread(&v, sizeof(Venda), 1, fpV)) {
        printf("Venda %d:\n", v.idVenda);
        for (int i = 0; i < v.totalProdutos; i++) {
            rewind(fpP);
            int achou = 0;
            while (fread(&p, sizeof(Produto), 1, fpP)) {
                if (p.id == v.produtos[i]) {
                    printf("  - %s (ID %d)\n", p.descricao, p.id);
                    achou = 1;
                    break;
                }
            }
            if (!achou) printf("  - Produto ID %d não encontrado\n", v.produtos[i]);
        }
    }
    fclose(fpV);
    fclose(fpP);
}

void removerProduto() {
    int id;
    printf("ID a remover: ");
    scanf("%d", &id);
    FILE *fp = fopen("produtos.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) { printf("Erro ao abrir arquivos.\n"); return; }
    Produto p;
    while (fread(&p, sizeof(Produto), 1, fp))
        if (p.id != id) fwrite(&p, sizeof(Produto), 1, temp);
    fclose(fp);
    fclose(temp);
    remove("produtos.dat");
    rename("temp.dat", "produtos.dat");
    printf("Produto removido.\n");
}

int main() {
    int opcao;
    do {
        printf("\n1 - Cadastrar Produto\n2 - Listar Produtos\n3 - Cadastrar Venda\n4 - Listar Vendas\n5 - Remover Produto\n0 - Sair\n> ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: cadastrarVenda(); break;
            case 4: listarVendas(); break;
            case 5: removerProduto(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    return 0;
}
