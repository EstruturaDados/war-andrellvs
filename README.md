# 🌍 Desafio WAR Estruturado em C

Este repositório contém a solução progressiva para o **Desafio WAR Estruturado**, um projeto de programação em C inspirado no famoso jogo de estratégia **WAR**. O desafio foi dividido em três níveis, focando na aplicação de conceitos fundamentais da linguagem C, desde estruturas básicas até gerenciamento avançado de memória e modularização.

---

## 🎯 Objetivo Geral

O objetivo é simular as mecânicas de cadastro de territórios, ataque e conquista, e cumprimento de missões, evoluindo a complexidade do código C a cada etapa.

---

## 🛠️ Tecnologia Utilizada

* **Linguagem de Programação:** C
* **Conceitos Principais:** `struct`, Vetores, Ponteiros, Alocação Dinâmica (`calloc`, `malloc`, `free`), Modularização em Funções, Aleatoriedade (`rand`/`srand`).

---

## 🗺️ Estrutura do Desafio (Níveis de Evolução)

O projeto foi desenvolvido em três etapas, cada uma adicionando novas funcionalidades e requisitos técnicos:

### 🟢 Nível Novato: Cadastro Inicial

Foco na fundação do jogo, utilizando estruturas de dados básicas.

* **Conceitos:** Criação da `struct Territorio`, uso de **vetor estático**.
* **Funcionalidade:** Cadastro e exibição do **Nome**, **Cor do Exército** e **Número de Tropas** de 5 territórios.

### 🔵 Nível Aventureiro: Batalhas Estratégicas

Introdução à dinâmica do jogo e ao gerenciamento avançado de memória.

* **Conceitos:** **Alocação dinâmica** de memória (`calloc`/`free`), manipulação de dados via **ponteiros**.
* **Funcionalidade:** Simulação interativa de **batalhas** com rolagem de dados aleatórios (`rand()`) e lógica de conquista/perda de tropas.

### 🟣 Nível Mestre: Missões e Modularização Total

Foco em design de software e lógica estratégica.

* **Conceitos:** **Modularização total** do código, alocação dinâmica para **strings de missão** (ponteiro para ponteiro).
* **Funcionalidade:** Implementação de um sistema de **missões aleatórias** e verificação de vitória para encerrar o jogo.

---

## ⚙️ Como Compilar e Rodar

Para compilar e rodar o projeto, utilize um compilador C (como GCC) em seu terminal:

1.  **Compilar:**
    ```bash
    gcc -o war war_estruturado.c
    ```
2.  **Executar:**
    ```bash
    ./war
    ```

Siga as instruções exibidas no terminal para cadastrar os territórios e iniciar a fase de ataque e verificação de missão.









# 🗺️ Desafio WAR Estruturado – Conquista de Territórios

Bem-vindo ao **Desafio WAR Estruturado!** Inspirado no famoso jogo de estratégia, este desafio convida você a programar diferentes versões do jogo WAR, evoluindo seus conhecimentos em **C** à medida que avança pelos níveis **Novato**, **Aventureiro** e **Mestre**.

A empresa **MateCheck** contratou você para criar uma versão estruturada do WAR. Cada nível propõe novas funcionalidades, conceitos e desafios de programação. **Você escolhe por onde começar!**

---

## 🧩 Nível Novato: Cadastro Inicial dos Territórios

### 🎯 Objetivo

- Criar uma `struct` chamada `Territorio`.
- Usar um **vetor estático de 5 elementos** para armazenar os territórios.
- Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
- Exibir o estado atual do mapa.

### ⚙️ Funcionalidades

- Leitura de dados pelo terminal (`fgets` e `scanf`)
- Impressão organizada dos dados de todos os territórios

### 💡 Conceitos abordados

- `struct`
- Vetor estático
- Entrada/saída com `scanf`, `fgets`, e `printf`

### 📥 Entrada

O usuário digita o nome do território, a cor do exército dominante e o número de tropas para **cada um dos 5 territórios**.

### 📤 Saída



## 🧗‍♂️ Nível Aventureiro: Batalhas Estratégicas

### 🎯 Objetivo

- Substituir o vetor estático por **alocação dinâmica com `calloc`**
- Criar uma função para **simular ataques entre dois territórios**
- Utilizar números aleatórios para representar dados de batalha

### 🆕 Novidades em relação ao Nível Novato

- Alocação dinâmica de memória com `calloc`
- Uso de **ponteiros**
- Laço interativo para o jogador escolher **territórios para atacar e defender**
- Simulação de dados de ataque e defesa com `rand()`

### ⚙️ Funcionalidades

- Cadastro dos territórios (como no Nível Novato)
- Fase de ataque com:
  - Escolha de atacante e defensor
  - Dados de ataque/defesa
  - Lógica:
    - Se atacante vence → defensor perde 1 tropa
    - Se defensor perde todas → território é conquistado
    - Empates favorecem o atacante

### 💡 Conceitos abordados

- Ponteiros
- `calloc` / `free`
- Aleatoriedade com `rand()` / `srand()`
- Funções para modularização

### 📥 Entrada

- Território **atacante** (1 a 5)
- Território **defensor** (1 a 5)

### 📤 Saída

Exibição do resultado da batalha, dados sorteados e mudanças no mapa.



## 🧠 Nível Mestre: Missões e Modularização Total

### 🎯 Objetivo

- Dividir o código em funções bem definidas
- Implementar um **sistema de missões**
- Verificar cumprimento da missão
- Aplicar **boas práticas** (uso de `const`, modularização, etc.)

### 🆕 Diferenças em relação ao Nível Aventureiro

- Modularização total em funções
- Missões aleatórias atribuídas:
  1. Destruir o exército **Verde**
  2. Conquistar **3 territórios**
- Menu interativo com opções

### ⚙️ Funcionalidades

- Inicialização automática dos territórios
- Menu principal com 3 opções:
  1. Atacar
  2. Verificar Missão
  3. Sair
- Verificação de vitória da missão

### 💡 Conceitos abordados

- Modularização
- `const` correctness
- Estruturação em múltiplas funções
- Passagem por referência

### 📥 Entrada

- Ações do jogador via menu:
  - `1` - Atacar
  - `2` - Verificar Missão
  - `0` - Sair
- Escolha de territórios para ataque

### 📤 Saída

- Mapa atualizado
- Resultados das batalhas
- Verificação da missão
- Mensagem de vitória



## 🏁 Conclusão

Com este **Desafio WAR Estruturado**, você praticará fundamentos essenciais da linguagem **C** de forma **divertida e progressiva**.

Cada nível foca em um conjunto de habilidades:

- 🟢 **Novato**: `struct`, vetor, entrada/saída
- 🔵 **Aventureiro**: ponteiros, memória dinâmica, lógica de jogo
- 🟣 **Mestre**: modularização, design limpo, sistema de missões



🚀 **Boa sorte! Avance nos níveis e torne-se um mestre da programação estratégica!**

> Equipe de Ensino – MateCheck
