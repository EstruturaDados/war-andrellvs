#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para um Território
typedef struct {
    char nome[50];
    char cor_exercito[20]; // Cor do exército dominante
    int num_tropas;
} Territorio;

// Constante para o número de territórios
#define NUM_TERRITORIOS 5

// --- Protótipos das Funções ---
void cadastrar_territorio(Territorio *t);
void exibir_mapa(const Territorio mapa[], int tamanho);

// --- Função Principal ---
int main() {
    // 1. Uso de um vetor estático de 5 elementos para armazenar os territórios
    Territorio mapa[NUM_TERRITORIOS];
    int i;

    printf("🗺️ --- Cadastro Inicial dos Territórios (Nível Novato) --- 🗺️\n\n");

    // 2. Cadastrando os dados de cada território
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        // Chama a função para ler os dados
        cadastrar_territorio(&mapa[i]);
    }

    printf("\n=======================================================\n");

    // 3. Exibir o estado atual do mapa
    exibir_mapa(mapa, NUM_TERRITORIOS);

    return 0;
}

// --- Definição das Funções ---

/**
 * @brief Lê os dados de um território a partir do terminal.
 * @param t Ponteiro para a struct Territorio a ser preenchida.
 */
void cadastrar_territorio(Territorio *t) {
    char buffer[100]; // Buffer temporário para strings lidas com fgets

    // Leitura do Nome (usando fgets para strings com espaços)
    printf("Nome do Território: ");
    // Limpa o buffer de entrada antes de usar fgets
    // (Útil se houver sujeira de scanf anterior, embora não haja aqui, é boa prática)
    // while (getchar() != '\n'); 
    
    // Leitura segura do nome
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // Tratar erro de leitura se necessário
        printf("Erro ao ler o nome. Saindo...\n");
        exit(1);
    }
    // Remove o '\n' que o fgets adiciona
    buffer[strcspn(buffer, "\n")] = 0;
    strncpy(t->nome, buffer, sizeof(t->nome) - 1);
    t->nome[sizeof(t->nome) - 1] = '\0'; // Garantir terminação

    // Leitura da Cor do Exército
    printf("Cor do Exército dominante: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Erro ao ler a cor. Saindo...\n");
        exit(1);
    }
    buffer[strcspn(buffer, "\n")] = 0;
    strncpy(t->cor_exercito, buffer, sizeof(t->cor_exercito) - 1);
    t->cor_exercito[sizeof(t->cor_exercito) - 1] = '\0';

    // Leitura do Número de Tropas (usando scanf)
    printf("Número de Tropas: ");
    // O '\n' fica no buffer de entrada após o scanf
    if (scanf("%d", &t->num_tropas) != 1) {
        printf("Entrada inválida para número de tropas. Usando 1.\n");
        t->num_tropas = 1;
    }
    // Limpar o buffer de entrada após o scanf para evitar problemas no próximo fgets
    while (getchar() != '\n');
}

/**
 * @brief Exibe uma lista organizada de todos os territórios e seus dados.
 * @param mapa O vetor de structs Territorio (passado como constante).
 * @param tamanho O número de elementos no vetor.
 */
void exibir_mapa(const Territorio mapa[], int tamanho) {
    printf("🌍 --- Estado Atual do Mapa --- 🌍\n");
    printf("+----------------------+----------------+----------------+\n");
    printf("| **Território** | **Exército** | **Tropas** |\n");
    printf("+----------------------+----------------+----------------+\n");

    for (int i = 0; i < tamanho; i++) {
        printf("| %-20s | %-14s | %-14d |\n",
               mapa[i].nome,
               mapa[i].cor_exercito,
               mapa[i].num_tropas);
    }
    printf("+----------------------+----------------+----------------+\n");
}