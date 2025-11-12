/*
+------------------------------------------------------------------------------+
¦                    JOGO DO LABIRINTO                                         ¦
¦                                                                              ¦
¦ Alunos: Gabriela Vieira e Jean Lucas                                         ¦
¦                                                                              ¦
¦ Recursos utilizados:                                                         ¦
¦ • Beep() para sons                                                           ¦
¦ • system("color") para cores                                                 ¦
¦ • Matrizes bidimensionais [10][10]                                           ¦
¦ • Estruturas de controle: if, for, while                                     ¦
¦ • For aninhado para percorrer matriz                                         ¦
¦ • Funções para modularização                                                 ¦
¦                                                                              ¦
+------------------------------------------------------------------------------+
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>   // Para Beep() e system("color")
#include <conio.h>     // Para getch()

// Constantes do jogo
#define TAMANHO 10
#define JOGADOR '@'
#define PAREDE 'X'
#define CAMINHO ' '
#define SAIDA 'O'
#define ARMADILHA 'T'

// Estrutura do jogador
typedef struct {
    int linha;
    int coluna;
    int movimentos;
    int pontos;
    int vivo;
} Jogador;

// Variáveis globais
char labirinto[TAMANHO][TAMANHO];
Jogador player;

// ---------------------------------------------------------------------------
//                              FUNÇÕES DE SOM
// ---------------------------------------------------------------------------

void somMovimento() {
    Beep(750, 100);  // Som médio e curto - movimento válido
    printf("\a");    // Som alternativo (Bell)
}

void somParede() {
    Beep(400, 300);  // Som grave e longo - bateu na parede
    printf("\a\a");  // Som alternativo (2 Bells)
}

void somArmadilha() {
    // Som de armadilha - dois beeps
    Beep(200, 200);
    Beep(150, 400);
    printf("\a\a\a");  // Som alternativo (3 Bells)
}

void somVitoria() {
    // Som de vitória - três beeps crescentes
    Beep(1000, 200);
    Beep(1500, 200);
    Beep(2000, 400);
    printf("\a");  // Som alternativo
}

void somInicio() {
    // Som de início - sequência curta
    Beep(500, 100);
    Beep(700, 100);
    printf("\a");  // Som alternativo
}

// ---------------------------------------------------------------------------
//                              FUNÇÕES DO LABIRINTO
// ---------------------------------------------------------------------------

// Inicializa o labirinto com layout predefinido
void inicializarLabirinto() {
    // Layout do labirinto 10x10
    char layout[TAMANHO][TAMANHO] = {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', '@', ' ', 'X', ' ', ' ', ' ', 'X', 'T', 'X'},
        {'X', 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
        {'X', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'X', 'X', 'T', 'X', 'X', 'X', ' ', 'X'},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X'},
        {'X', 'X', 'X', ' ', 'X', 'T', ' ', 'X', ' ', 'X'},
        {'X', ' ', ' ', ' ', 'X', 'X', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'X', ' ', ' ', ' ', ' ', 'X', 'O', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}
    };

    // Usa FOR para copiar o layout
    int i, j;
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            labirinto[i][j] = layout[i][j];
        }
    }

    // Inicializa o jogador
    player.linha = 1;
    player.coluna = 1;
    player.movimentos = 0;
    player.pontos = 1000;
    player.vivo = 1;
}

// Mostra o labirinto na tela
void mostrarLabirinto() {
    system("cls");  // Limpa a tela

    // Define cor de fundo preto e texto verde (0 = preto, A = verde claro)
    system("color 0A");

    // Titulo
    printf("\n");
    printf("  ===============================================\n");
    printf("  ||       LABIRINTO MOCAMBICANO                 ||\n");
    printf("  ===============================================\n\n");

    // Legenda
    printf("  Legenda: @ = Voce  X = Parede  O = Saida  T = Armadilha\n\n");

    // Números das colunas
    printf("       ");
    int j;
    for (j = 0; j < TAMANHO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    printf("      ");
    for (j = 0; j < TAMANHO; j++) {
        printf("--");
    }
    printf("\n");

    // Mostra o labirinto usando FOR
    int i;
    for (i = 0; i < TAMANHO; i++) {
        printf("   %d |", i);  // Número da linha

        for (j = 0; j < TAMANHO; j++) {
            // Usa IF para decidir o que mostrar
            if (i == player.linha && j == player.coluna) {
                printf(" @");  // Mostra o jogador
            } else {
                printf(" %c", labirinto[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");
}

// Mostra informacoes do jogo
void mostrarInfo() {
    printf("  ----------------------------------------------------------\n");
    printf("  | Posicao: (%d,%d) | Movimentos: %d | Pontos: %d       \n",
           player.linha, player.coluna, player.movimentos, player.pontos);
    printf("  ----------------------------------------------------------\n\n");

    printf("  Controles: W(cima) A(esq) S(baixo) D(dir) | Q(Sair)\n");
    printf("  Digite seu movimento: ");
}

// Valida se o movimento é possível usando IF
int validarMovimento(int novaLinha, int novaColuna) {
    // Usa IF para verificar limites
    if (novaLinha < 0 || novaLinha >= TAMANHO) {
        return 0;  // Fora dos limites
    }

    if (novaColuna < 0 || novaColuna >= TAMANHO) {
        return 0;  // Fora dos limites
    }

    // Usa IF para verificar se não é parede
    if (labirinto[novaLinha][novaColuna] == PAREDE) {
        return 0;  // É uma parede
    }

    return 1;  // Movimento válido
}

// Processa o movimento do jogador
void moverJogador(char movimento) {
    int novaLinha = player.linha;
    int novaColuna = player.coluna;

    // Usa IF para determinar nova posição
    if (movimento == 'W' || movimento == 'w') {
        novaLinha--;
    } else if (movimento == 'S' || movimento == 's') {
        novaLinha++;
    } else if (movimento == 'A' || movimento == 'a') {
        novaColuna--;
    } else if (movimento == 'D' || movimento == 'd') {
        novaColuna++;
    } else {
        return;  // Movimento inválido
    }

    // Valida o movimento
    if (validarMovimento(novaLinha, novaColuna)) {
        // Movimento válido
        player.linha = novaLinha;
        player.coluna = novaColuna;
        player.movimentos++;
        player.pontos = player.pontos + 10;  // Ganha pontos

        char celula = labirinto[novaLinha][novaColuna];

        // Usa IF para verificar o tipo de célula
        if (celula == ARMADILHA) {
            // Caiu em armadilha
            somArmadilha();
            player.pontos = player.pontos - 100;
            player.vivo = 0;

            mostrarLabirinto();
            mostrarInfo();

            // Muda cor para vermelho
            system("color 0C");

            printf("\n  *** OH NAO! Voce caiu em uma armadilha! ***\n");
            printf("  Pontuacao final: %d pontos em %d movimentos\n",
                   player.pontos, player.movimentos);
            printf("\n  Pressione qualquer tecla para sair...");
            getch();

        } else if (celula == SAIDA) {
            // Chegou na saída
            somVitoria();

            mostrarLabirinto();
            mostrarInfo();

            // Muda cor para verde brilhante
            system("color 0A");

            printf("\n  *** PARABENS! Voce escapou do labirinto! ***\n");
            printf("  Pontuacao final: %d pontos em %d movimentos\n",
                   player.pontos, player.movimentos);

            // Bonus por eficiencia
            if (player.movimentos < 20) {
                player.pontos = player.pontos + 500;
                printf("  *** Bonus de eficiencia: +500 pontos!\n");
            }

            printf("\n  Pressione qualquer tecla para sair...");
            getch();
            player.vivo = 0;

        } else {
            // Movimento normal
            somMovimento();
        }

    } else {
        // Movimento inválido (parede)
        somParede();
        player.pontos = player.pontos - 5;  // Perde pontos

        mostrarLabirinto();
        mostrarInfo();

        // Muda cor temporariamente para vermelho
        system("color 0C");

        printf("\n  *** Movimento invalido! Voce bateu na parede!\n");
        Sleep(1000);  // Pausa de 1 segundo

        // Volta cor normal
        system("color 0A");
    }
}

// Tela de boas-vindas
void telaBoasVindas() {
    system("cls");
    system("color 0B");  // Cor azul claro

    printf("\n");
    printf("  ================================================================\n");
    printf("  ||              *** JOGO DO LABIRINTO ***                     ||\n");
    printf("  ||                                                            ||\n");
    printf("  ||        Inspirado no jogo tradicional de Mocambique         ||\n");
    printf("  ||                                                            ||\n");
    printf("  ||  > Historia:                                               ||\n");
    printf("  ||  O jogo Labirinto tem origem em Mocambique, um pais        ||\n");
    printf("  ||  africano. E um jogo de tabuleiro simples e divertido,     ||\n");
    printf("  ||  praticado por criancas e adultos.                         ||\n");
    printf("  ||                                                            ||\n");
    printf("  ||  > Objetivo: Chegue na saida (O) evitando armadilhas (T)   ||\n");
    printf("  ||  > Controles: W/A/S/D para mover, Q para sair              ||\n");
    printf("  ||  > Pontos: +10 por movimento, -5 parede, -100 armadilha    ||\n");
    printf("  ||                                                            ||\n");
    printf("  ================================================================\n");

    printf("\n  Pressione qualquer tecla para comecar...");
    getch();
    somInicio();
}

// ---------------------------------------------------------------------------
//                              FUNÇÃO PRINCIPAL
// ---------------------------------------------------------------------------

int main() {
    // Tela de boas-vindas
    telaBoasVindas();

    // Inicializa o jogo
    inicializarLabirinto();

    // Loop principal usando WHILE
    while (player.vivo) {
        mostrarLabirinto();
        mostrarInfo();

        char movimento = getch();

        // Verifica se quer sair
        if (movimento == 'Q' || movimento == 'q') {
            system("color 0E");  // Amarelo
            printf("\n  *** Obrigado por jogar! Ate a proxima!\n");
            break;
        }

        // Processa movimento
        moverJogador(movimento);
    }

    return 0;
}
