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
} Cidade;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarCidade(Cidade *cidade) {
    printf("\nCadastro da Cidade:\n");
    
    printf("Código da carta: ");
    while(scanf("%d", &cidade->codigo) != 1) {
        printf("Digite um número válido para o código: ");
        limparBuffer();
    }
    limparBuffer();

    printf("Estado: ");
    scanf("%[^\n]s", cidade->estado);
    limparBuffer();
    
    printf("Nome da cidade: ");
    scanf("%[^\n]s", cidade->nome);
    limparBuffer();
    
    printf("População: ");
    while(scanf("%d", &cidade->populacao) != 1) {
        printf("Digite um número válido para população: ");
        limparBuffer();
    }
    limparBuffer();
    
    printf("Área (km²): ");
    while(scanf("%f", &cidade->area) != 1) {
        printf("Digite um número válido para área: ");
        limparBuffer();
    }
    limparBuffer();
    
    printf("PIB (em bilhões): ");
    while(scanf("%f", &cidade->pib) != 1) {
        printf("Digite um número válido para o PIB: ");
        limparBuffer();
    }
    limparBuffer();
    
    printf("Número de pontos turísticos: ");
    while(scanf("%d", &cidade->pontos_turisticos) != 1) {
        printf("Digite um número válido para pontos turísticos: ");
        limparBuffer();
    }
    limparBuffer();
}

void exibirCidade(Cidade cidade) {
    printf("\n------------------------\n");
    printf("Código da carta: %d\n", cidade.codigo);
    printf("Cidade: %s (%s)\n", cidade.nome, cidade.estado);
    printf("População: %d habitantes\n", cidade.populacao);
    printf("Área: %.2f km²\n", cidade.area);
    printf("PIB: %.2f bilhões\n", cidade.pib);
    printf("Pontos Turísticos: %d\n", cidade.pontos_turisticos);
    printf("------------------------\n");
}

void compararCidades(Cidade c1, Cidade c2, int atributo) {
    printf("\nComparando as cidades...\n");
    int vitoria = 0;
    
    switch (atributo) {
        case 1:
            printf("Comparando População:\n");
            vitoria = (c1.populacao > c2.populacao) ? 1 : (c1.populacao < c2.populacao) ? 2 : 0;
            break;
        case 2:
            printf("Comparando Área:\n");
            vitoria = (c1.area > c2.area) ? 1 : (c1.area < c2.area) ? 2 : 0;
            break;
        case 3:
            printf("Comparando PIB:\n");
            vitoria = (c1.pib > c2.pib) ? 1 : (c1.pib < c2.pib) ? 2 : 0;
            break;
        case 4:
            printf("Comparando Pontos Turísticos:\n");
            vitoria = (c1.pontos_turisticos > c2.pontos_turisticos) ? 1 : (c1.pontos_turisticos < c2.pontos_turisticos) ? 2 : 0;
            break;
        default:
            printf("Atributo inválido!\n");
            return;
    }
    
    if (vitoria == 0)
        printf("Empate! As cidades possuem o mesmo valor.\n");
    else
        printf("A cidade vencedora é: %s!\n", (vitoria == 1) ? c1.nome : c2.nome);
}

int main() {
    Cidade cidade1, cidade2;
    int atributo;
    
    printf("\nBem-vindo ao Super Trunfo - Cidades!\n");
    
    printf("\nCadastrando primeira cidade:");
    cadastrarCidade(&cidade1);
    
    printf("\nCadastrando segunda cidade:");
    cadastrarCidade(&cidade2);
    
    printf("\nCidades cadastradas:\n");
    exibirCidade(cidade1);
    exibirCidade(cidade2);
    
    printf("\nEscolha um atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos turísticos\n");
    printf("Digite o número correspondente: ");
    scanf("%d", &atributo);
    
    compararCidades(cidade1, cidade2, atributo);
    
    return 0;
}
