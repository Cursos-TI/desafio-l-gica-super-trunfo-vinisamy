#include <stdio.h>

#define MAX_NOME 50

typedef struct {
    char estado[MAX_NOME];
    char nome[MAX_NOME];
    int codigo;
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    int inicializada;
} Cidade;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerString(char *destino, const char *campo) {
    printf("%s: ", campo);
    return scanf(" %[^\n]", destino);
}

int lerIntPositivo(int *valor, const char *campo) {
    printf("%s: ", campo);
    if (scanf("%d", valor) != 1 || *valor <= 0) {
        printf("Por favor, digite um número positivo válido.\n");
        limparBuffer();
        return 0;
    }
    limparBuffer();
    return 1;
}

int lerFloatPositivo(float *valor, const char *campo) {
    printf("%s: ", campo);
    if (scanf("%f", valor) != 1 || *valor <= 0) {
        printf("Por favor, digite um número positivo válido.\n");
        limparBuffer();
        return 0;
    }
    limparBuffer();
    return 1;
}

void cadastrarCidade(Cidade *cidade) {
    printf("\nCadastro da Cidade:\n");
    
    do {
        if (!lerIntPositivo(&cidade->codigo, "Código da carta")) continue;
        break;
    } while (1);
    
    lerString(cidade->estado, "Estado");
    limparBuffer();
    
    lerString(cidade->nome, "Nome da cidade");
    limparBuffer();
    
    do {
        if (!lerIntPositivo(&cidade->populacao, "População")) continue;
        break;
    } while (1);
    
    do {
        if (!lerFloatPositivo(&cidade->area, "Área (km²)")) continue;
        break;
    } while (1);
    
    do {
        if (!lerFloatPositivo(&cidade->pib, "PIB (em bilhões)")) continue;
        break;
    } while (1);
    
    do {
        if (!lerIntPositivo(&cidade->pontos_turisticos, "Número de pontos turísticos")) continue;
        break;
    } while (1);
    
    cidade->inicializada = 1;
}

void exibirCidade(Cidade cidade) {
    if (!cidade.inicializada) {
        printf("\nCidade não cadastrada!\n");
        return;
    }
    
    printf("\n------------------------\n");
    printf("Código da carta: %d\n", cidade.codigo);
    printf("Cidade: %s (%s)\n", cidade.nome, cidade.estado);
    printf("População: %d habitantes\n", cidade.populacao);
    printf("Área: %.2f km²\n", cidade.area);
    printf("PIB: %.2f bilhões\n", cidade.pib);
    printf("Pontos Turísticos: %d\n", cidade.pontos_turisticos);
    printf("------------------------\n");
}

void compararCidades(Cidade c1, Cidade c2) {
    if (!c1.inicializada || !c2.inicializada) {
        printf("\nErro: Ambas as cidades precisam estar cadastradas para comparação!\n");
        return;
    }
    
    printf("\nComparação aninhada das cidades...\n");
    
    if (c1.populacao != c2.populacao) {
        printf("Comparando População...\n");
        printf("A cidade vencedora é: %s\n", (c1.populacao > c2.populacao) ? c1.nome : c2.nome);
        return;
    }
    
    if (c1.area != c2.area) {
        printf("Comparando Área...\n");
        printf("A cidade vencedora é: %s\n", (c1.area > c2.area) ? c1.nome : c2.nome);
        return;
    }
    
    if (c1.pib != c2.pib) {
        printf("Comparando PIB...\n");
        printf("A cidade vencedora é: %s\n", (c1.pib > c2.pib) ? c1.nome : c2.nome);
        return;
    }
    
    if (c1.pontos_turisticos != c2.pontos_turisticos) {
        printf("Comparando Pontos Turísticos...\n");
        printf("A cidade vencedora é: %s\n", (c1.pontos_turisticos > c2.pontos_turisticos) ? c1.nome : c2.nome);
        return;
    }
    
    printf("Empate! As cidades possuem atributos iguais.\n");
}

int main() {
    Cidade cidade1 = {0};
    Cidade cidade2 = {0};
    int opcao;
    
    printf("\nBem-vindo ao Super Trunfo - Cidades!\n");
    
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar primeira cidade\n");
        printf("2 - Cadastrar segunda cidade\n");
        printf("3 - Exibir cidades\n");
        printf("4 - Comparar cidades\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarCidade(&cidade1);
                break;
            case 2:
                cadastrarCidade(&cidade2);
                break;
            case 3:
                exibirCidade(cidade1);
                exibirCidade(cidade2);
                break;
            case 4:
                compararCidades(cidade1, cidade2);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);
    
    return 0;
}