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

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto() {
    Produto p;
    FILE *fp = fopen("produtos.dat", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo de produtos.\n");
        return;
    }

    scanf("%d", &p.id);
    limparBuffer();

    fgets(p.descricao, MAX_DESC, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = 0;

    scanf("%f", &p.preco);

    scanf("%d", &p.quantidade);
    limparBuffer();

    fwrite(&p, sizeof(Produto), 1, fp);
    fclose(fp);
    printf("Produto cadastrado com sucesso! (ID: %d)\n\n", p.id);
}

void listarProdutos() {
    Produto p;
    FILE *fp = fopen("produtos.dat", "rb");
    if (fp == NULL) {
        printf("Nenhum produto cadastrado.\n\n");
        return;
    }

    printf("\n--- Produtos ---\n");
    while (fread(&p, sizeof(Produto), 1, fp)) {
        printf("ID: %d | Descrição: %s | Preço: R$%.2f | Estoque: %d\n", p.id, p.descricao, p.preco, p.quantidade);
    }
    fclose(fp);
    printf("\n");
}

void cadastrarVenda() {
    Venda v;
    FILE *fp = fopen("vendas.dat", "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return;
    }

    scanf("%d", &v.idVenda);
    limparBuffer();

    scanf("%d", &v.totalProdutos);
    limparBuffer();

    if (v.totalProdutos > MAX_PRODUTOS_POR_VENDA) {
        v.totalProdutos = MAX_PRODUTOS_POR_VENDA;
        printf("Aviso: Quantidade de produtos na venda limitada a %d.\n", MAX_PRODUTOS_POR_VENDA);
    }

    for (int i = 0; i < v.totalProdutos; i++) {
        scanf("%d", &v.produtos[i]);
        limparBuffer();
    }

    fwrite(&v, sizeof(Venda), 1, fp);
    fclose(fp);
    printf("Venda %d registrada com sucesso!\n\n", v.idVenda);
}

void listarVendas() {
    FILE *fpV = fopen("vendas.dat", "rb");
    FILE *fpP = fopen("produtos.dat", "rb");
    if (fpV == NULL || fpP == NULL) {
        printf("Nenhum registro de vendas ou produtos para listar.\n\n");
        if (fpV) fclose(fpV);
        if (fpP) fclose(fpP);
        return;
    }

    Venda v;
    Produto p;
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
        printf("\n");
    }

    fclose(fpV);
    fclose(fpP);
}

void removerProduto() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fp = fopen("produtos.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Erro ao abrir arquivos.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    Produto p;
    int removido = 0;
    while (fread(&p, sizeof(Produto), 1, fp)) {
        if (p.id != id) fwrite(&p, sizeof(Produto), 1, temp);
        else removido = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("produtos.dat");
    rename("temp.dat", "produtos.dat");

    if (removido) printf("Produto %d removido com sucesso!\n\n", id);
    else printf("Produto %d não encontrado.\n\n", id);
}

void atualizarProduto() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fp = fopen("produtos.dat", "rb+");
    if (!fp) {
        printf("Erro ao abrir arquivo de produtos.\n");
        return;
    }

    Produto p;
    int achou = 0;
    long pos;

    while (fread(&p, sizeof(Produto), 1, fp)) {
        if (p.id == id) {
            pos = ftell(fp) - sizeof(Produto);

            fgets(p.descricao, MAX_DESC, stdin);
            p.descricao[strcspn(p.descricao, "\n")] = 0;

            scanf("%f", &p.preco);

            scanf("%d", &p.quantidade);
            limparBuffer();

            fseek(fp, pos, SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, fp);
            achou = 1;
            break;
        }
    }

    fclose(fp);
    if (achou) printf("Produto %d atualizado com sucesso!\n\n", id);
    else printf("Produto %d não encontrado.\n\n", id);
}

void atualizarVenda() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fp = fopen("vendas.dat", "rb+");
    if (!fp) {
        printf("Erro ao abrir arquivo de vendas.\n");
        return;
    }

    Venda v;
    int achou = 0;
    long pos;

    while (fread(&v, sizeof(Venda), 1, fp)) {
        if (v.idVenda == id) {
            pos = ftell(fp) - sizeof(Venda);

            scanf("%d", &v.totalProdutos);
            limparBuffer();
            if (v.totalProdutos > MAX_PRODUTOS_POR_VENDA) {
                v.totalProdutos = MAX_PRODUTOS_POR_VENDA;
                printf("Aviso: Quantidade de produtos na venda limitada a %d.\n", MAX_PRODUTOS_POR_VENDA);
            }

            for (int i = 0; i < v.totalProdutos; i++) {
                scanf("%d", &v.produtos[i]);
                limparBuffer();
            }

            fseek(fp, pos, SEEK_SET);
            fwrite(&v, sizeof(Venda), 1, fp);
            achou = 1;
            break;
        }
    }

    fclose(fp);
    if (achou) printf("Venda %d atualizada com sucesso!\n\n", id);
    else printf("Venda %d não encontrada.\n\n", id);
}

void consultarProdutoPorID() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fp = fopen("produtos.dat", "rb");
    if (!fp) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, fp)) {
        if (p.id == id) {
            printf("Produto ID %d: Descrição: %s | Preço: R$%.2f | Quantidade: %d\n", p.id, p.descricao, p.preco, p.quantidade);
            achou = 1;
            break;
        }
    }

    fclose(fp);
    if (!achou) printf("Produto ID %d não encontrado.\n", id);
    printf("\n");
}

void consultarVendaPorID() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fpV = fopen("vendas.dat", "rb");
    FILE *fpP = fopen("produtos.dat", "rb");
    if (!fpV || !fpP) {
        printf("Erro ao abrir arquivos.\n");
        if (fpV) fclose(fpV);
        if (fpP) fclose(fpP);
        return;
    }

    Venda v;
    Produto p;
    int achou = 0;
    while (fread(&v, sizeof(Venda), 1, fpV)) {
        if (v.idVenda == id) {
            printf("Venda %d:\n", v.idVenda);
            for (int i = 0; i < v.totalProdutos; i++) {
                rewind(fpP);
                int ok = 0;
                while (fread(&p, sizeof(Produto), 1, fpP)) {
                    if (p.id == v.produtos[i]) {
                        printf("  - %s (ID %d)\n", p.descricao, p.id);
                        ok = 1;
                        break;
                    }
                }
                if (!ok) printf("  - Produto ID %d não encontrado\n", v.produtos[i]);
            }
            achou = 1;
            break;
        }
    }

    fclose(fpV);
    fclose(fpP);
    if (!achou) printf("Venda %d não encontrada.\n", id);
    printf("\n");
}

void removerVenda() {
    int id;
    scanf("%d", &id);
    limparBuffer();

    FILE *fp = fopen("vendas.dat", "rb");
    FILE *temp = fopen("temp_vendas.dat", "wb");
    if (!fp || !temp) {
        printf("Erro ao abrir arquivos.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    Venda v;
    int removido = 0;
    while (fread(&v, sizeof(Venda), 1, fp)) {
        if (v.idVenda != id) fwrite(&v, sizeof(Venda), 1, temp);
        else removido = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("vendas.dat");
    rename("temp_vendas.dat", "vendas.dat");

    if (removido) printf("Venda %d removida com sucesso!\n\n", id);
    else printf("Venda %d não encontrada.\n\n", id);
}

int main() {
    int opcao;
    do {
        printf("--- Menu ---\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Cadastrar Venda\n");
        printf("4 - Listar Vendas\n");
        printf("5 - Remover Produto\n");
        printf("6 - Atualizar Produto\n");
        printf("7 - Atualizar Venda\n");
        printf("8 - Consultar Produto por ID\n");
        printf("9 - Consultar Venda por ID\n");
        printf("10 - Remover Venda\n");
        printf("0 - Sair\n");
        printf("> ");
        scanf("%d", &opcao);
        limparBuffer();
        printf("\n");

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: cadastrarVenda(); break;
            case 4: listarVendas(); break;
            case 5: removerProduto(); break;
            case 6: atualizarProduto(); break;
            case 7: atualizarVenda(); break;
            case 8: consultarProdutoPorID(); break;
            case 9: consultarVendaPorID(); break;
            case 10: removerVenda(); break;
            case 0: printf("Saindo do programa. Até mais!\n"); break;
            default: printf("Opção inválida. Tente novamente.\n\n");
        }
    } while (opcao != 0);

    return 0;
}
