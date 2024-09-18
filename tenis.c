#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TENIS 100
#define NOME_MAX 50
#define MARCA_MAX 50
#define ARQUIVO "tenis.txt"

typedef struct {
    int id;
    char marca[MARCA_MAX];
    char nome[NOME_MAX];
    float preco;
    int numeracao;
} Tenis;

Tenis loja[MAX_TENIS];
int total_tenis = 0;

void carregarTenis() {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("Nenhum arquivo encontrado. Iniciando com lista vazia.\n");
        return;
    }

    total_tenis = 0;
    while (fscanf(file, "%d %s %s %f %d", &loja[total_tenis].id, loja[total_tenis].marca, loja[total_tenis].nome, &loja[total_tenis].preco, &loja[total_tenis].numeracao) == 5) {
        total_tenis++;
    }

    fclose(file);
}

void salvarTenis() {
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    int i;
    for (i = 0; i < total_tenis; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", loja[i].id, loja[i].marca, loja[i].nome, loja[i].preco, loja[i].numeracao);
    }

    fclose(file);
}

void criarTenis() {
    if (total_tenis >= MAX_TENIS) {
        printf("Limite de t�nis atingido!\n");
        return;
    }

    Tenis novo_tenis;
    novo_tenis.id = total_tenis + 1;
    printf("Marca do t�nis: ");
    scanf(" %[^\n]s", novo_tenis.marca);
    printf("Nome do t�nis: ");
    scanf(" %[^\n]s", novo_tenis.nome);
    printf("Pre�o: ");
    scanf("%f", &novo_tenis.preco);
    printf("Numera��o: ");
    scanf("%d", &novo_tenis.numeracao);

    loja[total_tenis] = novo_tenis;
    total_tenis++;
    printf("T�nis adicionado com sucesso!\n");

    salvarTenis();
}

void lerTenis() {
    carregarTenis();
    printf("Lista de T�nis:\n");
    int i;
    for (i = 0; i < total_tenis; i++) {
        printf("ID: %d, Marca: %s, Nome: %s, Pre�o: %.2f, Numera��o: %d\n", 
                loja[i].id, loja[i].marca, loja[i].nome, loja[i].preco, loja[i].numeracao);
    }
}

void atualizarTenis() {
    int id;
    printf("Digite o ID do t�nis a ser atualizado: ");
    scanf("%d", &id);

    if (id < 1 || id > total_tenis) {
        printf("ID inv�lido!\n");
        return;
    }

    Tenis *tenis_atualizado = &loja[id - 1];
    printf("Atualizando t�nis com ID %d\n", tenis_atualizado->id);
    
    printf("Nova marca do t�nis (atual: %s): ", tenis_atualizado->marca);
    scanf(" %[^\n]s", tenis_atualizado->marca);
    
    printf("Novo nome do t�nis (atual: %s): ", tenis_atualizado->nome);
    scanf(" %[^\n]s", tenis_atualizado->nome);
    
    printf("Novo pre�o (atual: %.2f): ", tenis_atualizado->preco);
    scanf("%f", &tenis_atualizado->preco);
    
    printf("Nova numera��o (atual: %d): ", tenis_atualizado->numeracao);
    scanf("%d", &tenis_atualizado->numeracao);

    printf("T�nis atualizado com sucesso!\n");

    salvarTenis();
}

void deletarTenis() {
    int id;
    printf("Digite o ID do t�nis a ser deletado: ");
    scanf("%d", &id);

    if (id < 1 || id > total_tenis) {
        printf("ID inv�lido!\n");
        return;
    }

    int i;
    for (i = id - 1; i < total_tenis - 1; i++) {
        loja[i] = loja[i + 1];
    }
    total_tenis--;
    printf("T�nis deletado com sucesso!\n");

    salvarTenis();
}

int main() {
    carregarTenis();

    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Criar T�nis\n");
        printf("2. Ler T�nis\n");
        printf("3. Atualizar T�nis\n");
        printf("4. Deletar T�nis\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarTenis();
                break;
            case 2:
                lerTenis();
                break;
            case 3:
                atualizarTenis();
                break;
            case 4:
                deletarTenis();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while (opcao != 0);

    return 0;
}
