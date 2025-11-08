#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura para um Território
typedef struct {
    char nome[30];
    char cor[10]; // Cor do exército dominante
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
Territorio* cadastrar_mapa(int *num_territorios);
void cadastrar_territorio(Territorio *t);
void exibir_mapa(const Territorio mapa[], int tamanho);
void atacar(Territorio *atacante, Territorio *defensor);
void liberar_memoria(Territorio *mapa);
int rolar_dado();

// --- Função Principal ---
int main() {
    // 1. Inicializa o gerador de números aleatórios
    srand(time(NULL)); 

    Territorio *mapa = NULL;
    int num_territorios = 0;
    int escolha_atacante, escolha_defensor;
    
    printf("🗺️ --- WAR Estruturado: Nível Aventureiro --- 🗺️\n\n");

    // 2. Cadastro e alocação dinâmica
    mapa = cadastrar_mapa(&num_territorios);

    if (mapa == NULL) {
        printf("Não foi possível alocar memória. Encerrando o programa.\n");
        return 1;
    }
    
    printf("\n================ MAPA INICIAL =================\n");
    exibir_mapa(mapa, num_territorios);
    printf("===============================================\n\n");

    // 3. Laço interativo de ataque
    while (1) {
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Digite o número do Território ATACANTE (1 a %d, ou 0 para Sair): ", num_territorios);
        if (scanf("%d", &escolha_atacante) != 1) {
            printf("Entrada inválida.\n");
            // Limpa o buffer de entrada
            while(getchar() != '\n'); 
            continue;
        }

        if (escolha_atacante == 0) {
            break;
        }

        if (escolha_atacante < 1 || escolha_atacante > num_territorios) {
            printf("Escolha de atacante inválida.\n");
            continue;
        }
        
        // Validação de Tropas: Precisa de pelo menos 2 tropas para atacar (1 fica no território)
        if (mapa[escolha_atacante - 1].tropas <= 1) {
            printf("O território atacante precisa de pelo menos 2 tropas para poder atacar.\n");
            continue;
        }

        printf("Digite o número do Território DEFENSOR (1 a %d): ", num_territorios);
        if (scanf("%d", &escolha_defensor) != 1) {
            printf("Entrada inválida.\n");
            while(getchar() != '\n');
            continue;
        }

        if (escolha_defensor < 1 || escolha_defensor > num_territorios || escolha_defensor == escolha_atacante) {
            printf("Escolha de defensor inválida.\n");
            continue;
        }

        // Validação de Cor: Não pode atacar território da mesma cor
        if (strcmp(mapa[escolha_atacante - 1].cor, mapa[escolha_defensor - 1].cor) == 0) {
            printf("❌ Erro: Você não pode atacar um território da sua própria cor (%s).\n", mapa[escolha_atacante - 1].cor);
            continue;
        }

        // 4. Chamada da função de ataque (passagem por ponteiro)
        printf("\n--- Simulação de Batalha ---\n");
        atacar(&mapa[escolha_atacante - 1], &mapa[escolha_defensor - 1]);
        
        // 5. Exibição dos dados atualizados
        printf("\n================ MAPA APÓS BATALHA =================\n");
        exibir_mapa(mapa, num_territorios);
        printf("===================================================\n");
        
        // Limpa o buffer após o scanf
        while(getchar() != '\n'); 
    }

    // 6. Liberação da memória
    liberar_memoria(mapa);

    printf("\nFim do Desafio Nível Aventureiro. Memória liberada com sucesso.\n");
    return 0;
}

// --- Definição das Funções Auxiliares ---

/**
 * @brief Rola um dado aleatório de 1 a 6.
 * @return O valor do dado (int).
 */
int rolar_dado() {
    return (rand() % 6) + 1;
}

/**
 * @brief Simula um ataque entre dois territórios e atualiza seus dados.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio *atacante, Territorio *defensor) {
    int dado_ataque = rolar_dado();
    int dado_defesa = rolar_dado();
    
    printf("Dado de Ataque (%s): %d\n", atacante->cor, dado_ataque);
    printf("Dado de Defesa (%s): %d\n", defensor->cor, dado_defesa);

    // Lógica de Batalha: Empates favorecem o atacante (dado_ataque >= dado_defesa)
    if (dado_ataque >= dado_defesa) {
        printf("🏆 O ATACANTE %s VENCEU a batalha contra %s!\n", atacante->nome, defensor->nome);

        // O território é conquistado: muda de dono
        printf("Território CONQUISTADO! O controle de %s passa para o exército %s.\n", defensor->nome, atacante->cor);
        
        // 1. Mudar a cor do defensor (mudança de dono)
        // Usando ponteiros para acessar e modificar campos da struct
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';
        
        // 2. Transferir metade das tropas do atacante para o novo território (conquista)
        int tropas_a_mover = atacante->tropas / 2;
        
        // O atacante move suas tropas
        atacante->tropas -= tropas_a_mover;
        // O defensor (agora conquistado) recebe as tropas
        defensor->tropas = tropas_a_mover; 

        printf("Movidas %d tropas de %s para %s. Novo total de tropas do atacante: %d\n", 
               tropas_a_mover, atacante->nome, defensor->nome, atacante->tropas);
               
    } else {
        printf("🛡️ O DEFENSOR %s VENCEU a batalha contra %s!\n", defensor->nome, atacante->nome);
        
        // Atacante perde 1 tropa (se tiver mais de 1 para não zerar totalmente, embora 1 deva ser suficiente)
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("O atacante %s perdeu 1 tropa. Tropas restantes: %d\n", atacante->nome, atacante->tropas);
        } else {
            // Se as tropas do atacante caírem para 1, ele não pode mais atacar
            printf("O atacante %s não perdeu tropas, pois restavam apenas 1.\n", atacante->nome);
        }
    }
}


/**
 * @brief Solicita o número de territórios, aloca memória e inicia o cadastro.
 * @param num_territorios Ponteiro para armazenar o número total de territórios.
 * @return Ponteiro para o primeiro elemento do vetor de Territorio alocado dinamicamente.
 */
Territorio* cadastrar_mapa(int *num_territorios) {
    int i;
    Territorio *mapa = NULL;

    printf("Quantos territórios haverá no mapa? ");
    if (scanf("%d", num_territorios) != 1 || *num_territorios <= 0) {
        printf("Número de territórios inválido. Usando 3 como padrão.\n");
        *num_territorios = 3;
    }
    
    // Limpar o buffer após o scanf para não interferir no próximo fgets
    while (getchar() != '\n'); 

    // Alocação dinâmica de memória com calloc
    // calloc(quantidade, tamanho_do_elemento) garante que a memória seja inicializada com zeros.
    mapa = (Territorio*)calloc(*num_territorios, sizeof(Territorio));

    if (mapa == NULL) {
        return NULL; // Falha na alocação
    }

    printf("\n--- Cadastrando os %d Territórios ---\n", *num_territorios);

    for (i = 0; i < *num_territorios; i++) {
        printf("\nTerritório %d:\n", i + 1);
        // Passa o endereço do elemento atual do vetor (que é um ponteiro)
        cadastrar_territorio(&mapa[i]); 
    }

    return mapa;
}

/**
 * @brief Lê os dados de um território a partir do terminal.
 * @param t Ponteiro para a struct Territorio a ser preenchida.
 */
void cadastrar_territorio(Territorio *t) {
    char buffer[100]; 
    
    printf("Nome: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        exit(1);
    }
    buffer[strcspn(buffer, "\n")] = 0;
    // Uso de ponteiro (t->nome) para acessar e preencher o campo
    strncpy(t->nome, buffer, sizeof(t->nome) - 1);
    t->nome[sizeof(t->nome) - 1] = '\0'; 

    printf("Cor do Exército (Ex: Verde, Azul): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        exit(1);
    }
    buffer[strcspn(buffer, "\n")] = 0;
    // Uso de ponteiro (t->cor) para acessar e preencher o campo
    strncpy(t->cor, buffer, sizeof(t->cor) - 1);
    t->cor[sizeof(t->cor) - 1] = '\0';

    printf("Número de Tropas: ");
    // Uso de ponteiro (&t->tropas) para ler o inteiro
    if (scanf("%d", &t->tropas) != 1 || t->tropas < 1) {
        printf("Tropas inválidas. Definindo 1 tropa.\n");
        t->tropas = 1;
    }
    while (getchar() != '\n');
}

/**
 * @brief Exibe uma lista organizada de todos os territórios e seus dados.
 * @param mapa O vetor de structs Territorio (passado como constante).
 * @param tamanho O número de elementos no vetor.
 */
void exibir_mapa(const Territorio mapa[], int tamanho) {
    printf("🌎 Mapa Atualizado 🌎\n");
    printf("+----+------------------------------+------------+----------+\n");
    printf("| ID | **Território** | **Exército** | **Tropas** |\n");
    printf("+----+------------------------------+------------+----------+\n");

    for (int i = 0; i < tamanho; i++) {
        // Uso de ponteiro para iteração (mapa + i) e acesso aos campos
        printf("| %-2d | %-28s | %-10s | %-8d |\n",
               i + 1,
               (mapa + i)->nome,
               (mapa + i)->cor,
               (mapa + i)->tropas);
    }
    printf("+----+------------------------------+------------+----------+\n");
}

/**
 * @brief Libera a memória alocada dinamicamente para o mapa.
 * @param mapa O ponteiro para o bloco de memória alocado por calloc.
 */
void liberar_memoria(Territorio *mapa) {
    // 7. Uso de 'free' para liberar a memória alocada dinamicamente
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória do mapa liberada.\n");
    }
}