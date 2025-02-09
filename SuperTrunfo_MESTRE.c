#include <stdio.h>

#define MAX_NOME 50
#define MAX_CARTAS 20

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

typedef enum {
    CODIGO = 1,
    POPULACAO,
    AREA,
    PIB,
    PONTOS_TURISTICOS
} Atributo;

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

void exibirCidade(Cidade cidade, int index) {
    if (!cidade.inicializada) {
        printf("\nCarta %d: Não cadastrada!\n", index + 1);
        return;
    }
    
    printf("\n----- Carta %d -----\n", index + 1);
    printf("Código da carta: %d\n", cidade.codigo);
    printf("Cidade: %s (%s)\n", cidade.nome, cidade.estado);
    printf("População: %d habitantes\n", cidade.populacao);
    printf("Área: %.2f km²\n", cidade.area);
    printf("PIB: %.2f bilhões\n", cidade.pib);
    printf("Pontos Turísticos: %d\n", cidade.pontos_turisticos);
    printf("------------------\n");
}

void exibirTodasCidades(Cidade cidades[]) {
    printf("\n=== Cartas Cadastradas ===\n");
    for (int i = 0; i < MAX_CARTAS; i++) {
        exibirCidade(cidades[i], i);
    }
}

void exibirMenuAtributos() {
    printf("\nAtributos disponíveis:\n");
    printf("1 - Código\n");
    printf("2 - População\n");
    printf("3 - Área\n");
    printf("4 - PIB\n");
    printf("5 - Pontos Turísticos\n");
}

float obterValorAtributo(Cidade cidade, Atributo atributo) {
    switch (atributo) {
        case CODIGO: return (float)cidade.codigo;
        case POPULACAO: return (float)cidade.populacao;
        case AREA: return cidade.area;
        case PIB: return cidade.pib;
        case PONTOS_TURISTICOS: return (float)cidade.pontos_turisticos;
        default: return 0.0f;
    }
}

const char* obterNomeAtributo(Atributo atributo) {
    switch (atributo) {
        case CODIGO: return "Código";
        case POPULACAO: return "População";
        case AREA: return "Área";
        case PIB: return "PIB";
        case PONTOS_TURISTICOS: return "Pontos Turísticos";
        default: return "Desconhecido";
    }
}

int selecionarCarta(Cidade cidades[], const char *mensagem) {
    int cartaIndex;
    do {
        printf("\n%s (1-%d): ", mensagem, MAX_CARTAS);
        if (scanf("%d", &cartaIndex) != 1 || cartaIndex < 1 || cartaIndex > MAX_CARTAS) {
            printf("Número de carta inválido!\n");
            limparBuffer();
            continue;
        }
        cartaIndex--; // Ajusta para índice do array
        
        if (!cidades[cartaIndex].inicializada) {
            printf("Esta carta não está cadastrada!\n");
            continue;
        }
        break;
    } while (1);
    
    return cartaIndex;
}

void compararCartas(Cidade cidades[]) {
    // Verifica se existem pelo menos duas cartas cadastradas
    int cartas_cadastradas = 0;
    for (int i = 0; i < MAX_CARTAS; i++) {
        if (cidades[i].inicializada) cartas_cadastradas++;
    }
    
    if (cartas_cadastradas < 2) {
        printf("\nErro: É necessário ter pelo menos 2 cartas cadastradas para comparar!\n");
        return;
    }

    // Seleciona as cartas para comparação
    int index1 = selecionarCarta(cidades, "Selecione a primeira carta");
    int index2;
    do {
        index2 = selecionarCarta(cidades, "Selecione a segunda carta");
        if (index2 == index1) {
            printf("Selecione uma carta diferente da primeira!\n");
            continue;
        }
        break;
    } while (1);

    Cidade c1 = cidades[index1];
    Cidade c2 = cidades[index2];

    Atributo attr1, attr2;
    
    printf("\nEscolha o primeiro atributo para comparação:\n");
    exibirMenuAtributos();
    scanf("%d", (int*)&attr1);
    limparBuffer();
    
    printf("\nEscolha o segundo atributo para comparação:\n");
    exibirMenuAtributos();
    scanf("%d", (int*)&attr2);
    limparBuffer();
    
    float val1_c1 = obterValorAtributo(c1, attr1);
    float val1_c2 = obterValorAtributo(c2, attr1);
    float val2_c1 = obterValorAtributo(c1, attr2);
    float val2_c2 = obterValorAtributo(c2, attr2);
    
    printf("\nComparando %s e %s...\n", obterNomeAtributo(attr1), obterNomeAtributo(attr2));
    
    int vitorias_c1 = (val1_c1 > val1_c2 ? 1 : (val1_c1 < val1_c2 ? 0 : 0)) +
                      (val2_c1 > val2_c2 ? 1 : (val2_c1 < val2_c2 ? 0 : 0));
    
    int vitorias_c2 = (val1_c2 > val1_c1 ? 1 : (val1_c2 < val1_c1 ? 0 : 0)) +
                      (val2_c2 > val2_c1 ? 1 : (val2_c2 < val2_c1 ? 0 : 0));
    
    printf("\nResultados da comparação:\n");
    printf("%s: %s %.2f vs %.2f %s\n", 
           obterNomeAtributo(attr1), 
           c1.nome, val1_c1, val1_c2, c2.nome);
    printf("%s: %s %.2f vs %.2f %s\n", 
           obterNomeAtributo(attr2), 
           c1.nome, val2_c1, val2_c2, c2.nome);
    
    printf("\nResultado final: ");
    if (vitorias_c1 > vitorias_c2) {
        printf("%s vence com %d vitórias contra %d!\n", c1.nome, vitorias_c1, vitorias_c2);
    } else if (vitorias_c2 > vitorias_c1) {
        printf("%s vence com %d vitórias contra %d!\n", c2.nome, vitorias_c2, vitorias_c1);
    } else {
        printf("Empate no número de vitórias! ");
        printf("Desempatando pelo %s: ", obterNomeAtributo(attr1));
        printf("%s %s!\n", 
               val1_c1 > val1_c2 ? c1.nome : 
               val1_c1 < val1_c2 ? c2.nome : "Empate total", 
               val1_c1 != val1_c2 ? "vence" : "");
    }
}

int contarCartasCadastradas(Cidade cidades[]) {
    int count = 0;
    for (int i = 0; i < MAX_CARTAS; i++) {
        if (cidades[i].inicializada) count++;
    }
    return count;
}

int main() {
    Cidade cidades[MAX_CARTAS] = {0};
    int opcao;
    
    printf("\nBem-vindo ao Super Trunfo - Cidades (Nível Mestre)!\n");
    
    do {
        int cartas_cadastradas = contarCartasCadastradas(cidades);
        
        printf("\nMenu Principal:\n");
        printf("1 - Cadastrar nova carta (%d/%d cartas cadastradas)\n", cartas_cadastradas, MAX_CARTAS);
        printf("2 - Exibir todas as cartas\n");
        printf("3 - Comparar cartas\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        
        switch (opcao) {
            case 1:
                if (cartas_cadastradas >= MAX_CARTAS) {
                    printf("\nLimite máximo de cartas atingido!\n");
                } else {
                    for (int i = 0; i < MAX_CARTAS; i++) {
                        if (!cidades[i].inicializada) {
                            cadastrarCidade(&cidades[i]);
                            break;
                        }
                    }
                }
                break;
            case 2:
                exibirTodasCidades(cidades);
                break;
            case 3:
                compararCartas(cidades);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
    
    return 0;
}