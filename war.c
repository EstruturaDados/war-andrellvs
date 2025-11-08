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

// --- Constantes Globais (Missões) ---
#define MAX_MISSOES 5
const char *MISSOES[MAX_MISSOES] = {
    "Conquistar 3 Territórios (Total de 3).", // Missão 0
    "Destruir o Exército AZUL (Eliminar todos os territórios azuis).", // Missão 1
    "Ter 5 ou mais Territórios (Total de 5).", // Missão 2
    "Destruir o Exército VERDE (Eliminar todos os territórios verdes).", // Missão 3
    "Conquistar 4 Territórios (Total de 4)." // Missão 4
};

// --- Protótipos das Funções ---
// Gerenciamento de Mapa e Memória
Territorio* cadastrar_mapa(int *num_territorios);
void cadastrar_territorio_automatico(Territorio *t, int id); // Inicialização automática
void exibir_mapa(const Territorio mapa[], int tamanho);
void liberar_memoria(Territorio *mapa, char *missao);

// Batalha
int rolar_dado();
void atacar(Territorio *atacante, Territorio *defensor);

// Missão
void atribuir_missao(char **missao_jogador);
int verificar_missao(char *missao, Territorio *mapa, int tamanho, const char *cor_jogador);

// --- Função Principal ---
int main() {
    // Inicialização do gerador de números aleatórios
    srand(time(NULL)); 

    Territorio *mapa = NULL;
    char *missao_jogador = NULL; // Ponteiro para a missão do jogador (alocada dinamicamente)
    int num_territorios = 0;
    int escolha_atacante, escolha_defensor;
    int escolha_menu;
    const char *cor_jogador = "VERMELHO"; // A cor do nosso jogador no desafio
    int missao_cumprida = 0;
    
    printf("👑 --- WAR Estruturado: Nível Mestre (Com Missões) --- 👑\n\n");

    // 1. Alocação e Cadastro Automático do Mapa
    num_territorios = 5; // Mapa fixo para o Mestre
    mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Não foi possível alocar memória para o mapa. Encerrando.\n");
        return 1;
    }
    
    // Inicialização automática dos 5 territórios
    for (int i = 0; i < num_territorios; i++) {
        cadastrar_territorio_automatico(&mapa[i], i);
    }
    
    // 2. Atribuição e Exibição da Missão
    atribuir_missao(&missao_jogador);
    
    printf("======================================================\n");
    printf("🎖️ Sua Missão (%s): %s\n", cor_jogador, missao_jogador);
    printf("======================================================\n\n");
    
    exibir_mapa(mapa, num_territorios);

    // 3. Menu Interativo Principal
    while (missao_cumprida == 0) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Atacar\n");
        printf("2. Verificar Missão\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &escolha_menu) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while(getchar() != '\n');
            continue;
        }
        
        // Limpa o buffer após o scanf
        while(getchar() != '\n'); 

        if (escolha_menu == 0) {
            break;
        }

        switch (escolha_menu) {
            case 1: { // 1. Atacar
                printf("\n--- FASE DE ATAQUE ---\n");
                
                // Pede atacante
                printf("ID do Território ATACANTE (da sua cor %s, 1 a %d): ", cor_jogador, num_territorios);
                if (scanf("%d", &escolha_atacante) != 1 || escolha_atacante < 1 || escolha_atacante > num_territorios) {
                    printf("ID de atacante inválido.\n");
                    while(getchar() != '\n'); 
                    break;
                }
                
                // Pede defensor
                printf("ID do Território DEFENSOR (1 a %d): ", num_territorios);
                if (scanf("%d", &escolha_defensor) != 1 || escolha_defensor < 1 || escolha_defensor > num_territorios || escolha_defensor == escolha_atacante) {
                    printf("ID de defensor inválido.\n");
                    while(getchar() != '\n'); 
                    break;
                }

                // Validações
                if (mapa[escolha_atacante - 1].tropas <= 1) {
                    printf("❌ Atacante precisa de pelo menos 2 tropas.\n");
                    while(getchar() != '\n'); 
                    break;
                }
                if (strcmp(mapa[escolha_atacante - 1].cor, cor_jogador) != 0) {
                    printf("❌ Você só pode atacar com seus territórios (%s).\n", cor_jogador);
                    while(getchar() != '\n'); 
                    break;
                }
                if (strcmp(mapa[escolha_atacante - 1].cor, mapa[escolha_defensor - 1].cor) == 0) {
                    printf("❌ Você não pode atacar um território da mesma cor (%s).\n", mapa[escolha_defensor - 1].cor);
                    while(getchar() != '\n'); 
                    break;
                }

                // Simulação da Batalha
                atacar(&mapa[escolha_atacante - 1], &mapa[escolha_defensor - 1]);
                
                // Verifica a missão após o ataque
                missao_cumprida = verificar_missao(missao_jogador, mapa, num_territorios, cor_jogador);
                
                printf("\n================ MAPA APÓS BATALHA =================\n");
                exibir_mapa(mapa, num_territorios);
                printf("===================================================\n");
                
                break;
            }
            case 2: { // 2. Verificar Missão
                missao_cumprida = verificar_missao(missao_jogador, mapa, num_territorios, cor_jogador);
                if (missao_cumprida) {
                    printf("✅ Missão Cumprida! Parabéns!\n");
                } else {
                    printf("A missão ainda não foi concluída. Continue atacando!\n");
                }
                break;
            }
            default: {
                printf("Opção inválida.\n");
                break;
            }
        }
        
        if (missao_cumprida) {
            printf("\n🎉🎉 VOCÊ VENCEU O JOGO WAR ESTRUTURADO! 🎉🎉\n");
            printf("Missão de Vingança Estratégica: '%s'\n", missao_jogador);
            break;
        }
    }

    // 4. Liberação da Memória
    liberar_memoria(mapa, missao_jogador);

    printf("\nFim do Desafio Nível Mestre. Memória liberada com sucesso.\n");
    return 0;
}

// --- Definição das Funções Auxiliares ---

/**
 * @brief Inicializa um território com dados automáticos.
 * @param t Ponteiro para a struct Territorio a ser preenchida.
 * @param id ID do território (para nome e distribuição de cores).
 */
void cadastrar_territorio_automatico(Territorio *t, int id) {
    char nome_buffer[30];
    
    // Distribuição de cores
    if (id == 0 || id == 3) {
        strcpy(t->cor, "VERMELHO"); // Nosso jogador
    } else if (id == 1) {
        strcpy(t->cor, "AZUL"); // Inimigo 1
    } else {
        strcpy(t->cor, "VERDE"); // Inimigo 2
    }
    
    // Nome
    sprintf(nome_buffer, "T-Beta-%d", id + 1);
    strcpy(t->nome, nome_buffer);
    
    // Tropas iniciais
    t->tropas = (id % 2) + 2; // 2 ou 3 tropas
}

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
    
    printf("\nDado de Ataque (%s): %d\n", atacante->cor, dado_ataque);
    printf("Dado de Defesa (%s): %d\n", defensor->cor, dado_defesa);

    // Lógica de Batalha: Empates favorecem o atacante
    if (dado_ataque >= dado_defesa) {
        printf("🏆 %s VENCEU a batalha! %s foi CONQUISTADO!\n", atacante->nome, defensor->nome);

        // Mudar a cor do defensor (mudança de dono)
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';
        
        // Transferir metade das tropas do atacante (mínimo 1)
        int tropas_a_mover = (atacante->tropas > 1) ? (atacante->tropas / 2) : 1;
        
        atacante->tropas -= tropas_a_mover;
        defensor->tropas = tropas_a_mover; 

        printf("Movidas %d tropas. Tropas remanescentes do atacante: %d\n", tropas_a_mover, atacante->tropas);
               
    } else {
        printf("🛡️ %s VENCEU a defesa! Atacante %s perde 1 tropa.\n", defensor->nome, atacante->nome);
        
        // Atacante perde 1 tropa, mantendo pelo menos 1
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("Tropas remanescentes do atacante: %d\n", atacante->tropas);
        }
    }
}


/**
 * @brief Sorteia uma missão e aloca/copia para a variável do jogador.
 * @param missao_jogador Ponteiro para o ponteiro char* onde a missão será armazenada.
 */
void atribuir_missao(char **missao_jogador) {
    int id_missao = rand() % MAX_MISSOES;
    const char *missao_sorteada = MISSOES[id_missao];
    size_t len = strlen(missao_sorteada) + 1;

    // Alocação dinâmica para a string da missão
    *missao_jogador = (char *)malloc(len);
    
    if (*missao_jogador == NULL) {
        printf("Falha na alocação da missão.\n");
        exit(1);
    }

    // Passagem por referência (**missao_jogador) e cópia usando strcpy
    strcpy(*missao_jogador, missao_sorteada);
}


/**
 * @brief Verifica se a missão do jogador foi cumprida.
 * @param missao A string da missão (passagem por valor).
 * @param mapa O vetor de territórios.
 * @param tamanho O número de territórios.
 * @param cor_jogador A cor do exército do jogador.
 * @return 1 se cumprida, 0 caso contrário.
 */
int verificar_missao(char *missao, Territorio *mapa, int tamanho, const char *cor_jogador) {
    // Lógica: Conquistar 3/4/5 territórios
    if (strstr(missao, "Territórios")) {
        int territorios_necessarios = 0;
        int territorios_conquistados = 0;
        
        // Extrai o número da missão (simples: 3, 4 ou 5)
        if (strstr(missao, " 3 ")) territorios_necessarios = 3;
        else if (strstr(missao, " 4 ")) territorios_necessarios = 4;
        else if (strstr(missao, " 5 ")) territorios_necessarios = 5;

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                territorios_conquistados++;
            }
        }
        
        if (territorios_conquistados >= territorios_necessarios) {
            return 1;
        }

    // Lógica: Destruir Exército (Eliminar todas as cores inimigas)
    } else if (strstr(missao, "Destruir o Exército")) {
        char cor_alvo[10];
        int inimigo_presente = 0;
        
        // Determina a cor alvo
        if (strstr(missao, "AZUL")) strcpy(cor_alvo, "AZUL");
        else if (strstr(missao, "VERDE")) strcpy(cor_alvo, "VERDE");
        else return 0; // Missão de destruição inválida

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_alvo) == 0) {
                inimigo_presente = 1;
                break; // Inimigo ainda existe
            }
        }
        
        if (inimigo_presente == 0) {
            return 1; // Cor alvo eliminada
        }
    }
    
    return 0; // Missão não cumprida
}

/**
 * @brief Exibe uma lista organizada de todos os territórios e seus dados.
 * @param mapa O vetor de structs Territorio (passado como constante).
 * @param tamanho O número de elementos no vetor.
 */
void exibir_mapa(const Territorio mapa[], int tamanho) {
    int cont_jogador = 0;
    printf("🌎 Mapa Atualizado 🌎\n");
    printf("+----+------------------------------+------------+----------+\n");
    printf("| ID | **Território** | **Exército** | **Tropas** |\n");
    printf("+----+------------------------------+------------+----------+\n");

    for (int i = 0; i < tamanho; i++) {
        printf("| %-2d | %-28s | %-10s | %-8d |\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
        if (strcmp(mapa[i].cor, "VERMELHO") == 0) {
            cont_jogador++;
        }
    }
    printf("+----+------------------------------+------------+----------+\n");
    printf("Total de territórios do jogador VERMELHO: %d\n", cont_jogador);
}

/**
 * @brief Libera toda a memória alocada dinamicamente (mapa e missão).
 * @param mapa O ponteiro para o bloco de memória dos territórios.
 * @param missao O ponteiro para a string da missão.
 */
void liberar_memoria(Territorio *mapa, char *missao) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao != NULL) {
        free(missao); // Liberar a memória da string da missão
    }
}