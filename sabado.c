#include <stdio.h>
#include <string.h>

// define o registro livro com os campos solicitados
typedef struct {
    char titulo[100];      
    char autor[100];       
    char editora[100];     
    int anoPublicacao;     
    int qtdPaginas;        
} Livro;

// funcao para preencher o vetor de livros com os dados digitados pelo usuario
void preencherVetor(Livro *vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("livro %d\n", i+1);

        // le o titulo do livro
        printf("digite o titulo do livro\n");
        fgets(vetor[i].titulo, sizeof(vetor[i].titulo), stdin);
        vetor[i].titulo[strcspn(vetor[i].titulo, "\n")] = '\0'; // remove o enter

        // le o autor do livro
        printf("digite o autor do livro\n");
        fgets(vetor[i].autor, sizeof(vetor[i].autor), stdin);
        vetor[i].autor[strcspn(vetor[i].autor, "\n")] = '\0'; 

        // le a editora do livro
        printf("digite a editora do livro\n");
        fgets(vetor[i].editora, sizeof(vetor[i].editora), stdin);
        vetor[i].editora[strcspn(vetor[i].editora, "\n")] = '\0'; 

        // le o ano de publicacao
        printf("digite o ano de publicacao\n");
        scanf("%d", &vetor[i].anoPublicacao);

        // le a quantidade de paginas
        printf("digite a quantidade de paginas\n");
        scanf("%d", &vetor[i].qtdPaginas);

        getchar(); // limpa o enter do buffer apos o scanf
    }
}

// funcao para imprimir todos os livros cadastrados
void imprimirVetor(Livro *vetor, int n) {
    printf("livros cadastrados:\n");
    for (int i = 0; i < n; i++) {
        // imprime todos os campos do livro em uma linha
        printf("%s | %s | %s | %d | %d\n", vetor[i].titulo, vetor[i].autor, vetor[i].editora, vetor[i].anoPublicacao, vetor[i].qtdPaginas);
    }
}

// funcao para buscar um livro pelo titulo usando busca linear
int buscarPorTitulo(Livro *vetor, int n, char *titulo) {
    for (int i = 0; i < n; i++) {
        // compara o titulo buscado com o titulo do livro atual
        if (strcmp(vetor[i].titulo, titulo) == 0) {
            return i; // retorna o indice se encontrar
        }
    }
    return -1; // retorna -1 se nao encontrar
}

// funcao para ordenar o vetor de livros pelo titulo usando bubble sort
void ordenarPorTitulo(Livro *vetor, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            // compara os titulos dos livros vizinhos
            if (strcmp(vetor[j].titulo, vetor[j+1].titulo) > 0) {
                // troca os livros de lugar se estiverem fora de ordem
                Livro temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

// funcao para busca binaria pelo titulo (vetor deve estar ordenado)
int buscaBinariaPorTitulo(Livro *vetor, int n, char *titulo) {
    int inicio = 0, fim = n-1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(vetor[meio].titulo, titulo);
        if (cmp == 0) {
            return meio; // encontrou o livro
        } else if (cmp < 0) {
            inicio = meio + 1; // busca na metade direita
        } else {
            fim = meio - 1; // busca na metade esquerda
        }
    }
    return -1; // nao encontrou o livro
}

int main() {
    int n;
    // pede ao usuario quantos livros deseja cadastrar
    printf("quantos livros deseja cadastrar?\n");
    scanf("%d", &n);
    getchar(); // limpa o enter do buffer

    Livro livros[n]; // cria o vetor de livros

    // preenche o vetor de livros
    preencherVetor(livros, n);

    // imprime todos os livros cadastrados
    imprimirVetor(livros, n);

    // exemplo de busca linear
    char tituloBusca[100];
    printf("digite o titulo para buscar (busca linear)\n");
    fgets(tituloBusca, sizeof(tituloBusca), stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0'; // remove o enter
    int pos = buscarPorTitulo(livros, n, tituloBusca);
    if (pos != -1) {
        printf("livro encontrado na posicao %d\n", pos);
    } else {
        printf("livro nao encontrado\n");
    }

    // ordena o vetor de livros pelo titulo
    ordenarPorTitulo(livros, n);
    printf("livros ordenados por titulo:\n");
    imprimirVetor(livros, n);

    // exemplo de busca binaria
    printf("digite o titulo para buscar (busca binaria)\n");
    fgets(tituloBusca, sizeof(tituloBusca), stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0'; // remove o enter
    pos = buscaBinariaPorTitulo(livros, n, tituloBusca);
    if (pos != -1) {
        printf("livro encontrado na posicao %d\n", pos);
    } else {
        printf("livro nao encontrado\n");
    }

    return 0;
}
