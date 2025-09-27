
#include <stdio.h>   // I/O básico
#include <stdlib.h>  // system("pause") no Windows
#include <string.h>  // strcmp, strcpy

#define MAX_PNEUS 20  // limites práticos p/ vetores
#define MAX_STEPS 4

// Dados do veículo atual
struct Veiculo {
    int tipo;                 // 1=toco, 2=truck, 3=carreta simples, 4=carreta 3 eixos
    int qtdPneus;             // quantos pneus ativos neste veículo
    int pneus[MAX_PNEUS];     // números dos pneus
    int qtdSteps;             // quantos estepes
    int steps[MAX_STEPS];     // números dos estepes
};

// Usuário simples (login/senha)
struct Usuario {
    char usuario[20];
    char senha[20];
    int logado;               // 1=ok
};

// Estado global (facilita chamadas de função)
struct Veiculo gVeic;
struct Usuario gUser;

void inicializar() {
    int i;
    gVeic.tipo = 0;
    gVeic.qtdPneus = 0;
    gVeic.qtdSteps = 0;
    for (i = 0; i < MAX_PNEUS; i++) gVeic.pneus[i] = 0;  // "zera" slots
    for (i = 0; i < MAX_STEPS; i++) gVeic.steps[i] = 0;

    strcpy(gUser.usuario, "admin");  // credencial padrão (didático)
    strcpy(gUser.senha,  "1234");
    gUser.logado = 0;
}

// Confere se um número já está usado (evita duplicar)
int existeNumero(int numero) {
    int i;
    // procura entre pneus já cadastrados
    for (i = 0; i < gVeic.qtdPneus; i++) if (gVeic.pneus[i] == numero) return 1;
    // e entre steps
    for (i = 0; i < gVeic.qtdSteps; i++) if (gVeic.steps[i] == numero) return 1;
    return 0;
}

int fazerLogin() {
    char u[30], s[30];
    int tentativas = 0;
    printf("==== LOGIN ====\n");
    while (tentativas < 3) {                 // 3 chances está de bom tamanho
        printf("Usuario: ");
        scanf("%19s", u);
        printf("Senha: ");
        scanf("%19s", s);

        if (strcmp(u, gUser.usuario) == 0 && strcmp(s, gUser.senha) == 0) {
            gUser.logado = 1;
            printf("Login OK! Bem-vindo, %s.\n", gUser.usuario);
            return 1;
        } else {
            tentativas++;
            printf("Dados incorretos! Tentativa %d/3\n", tentativas);
        }
    }
    printf("Muitas tentativas. Encerrando.\n");
    return 0;
}

void escolherTipo() {
    int t;
    printf("\nEscolha o tipo de eixo:\n");
    printf("1 - TOCO (4 pneus)\n");
    printf("2 - TRUCK (6 pneus)\n");
    printf("3 - CARRETA SIMPLES (8 pneus)\n");
    printf("4 - CARRETA 3 EIXOS (10 pneus)\n");
    printf("Opcao: ");
    scanf("%d", &t);

    // mapeia o tipo para a quantidade de pneus (simples e direto)
    gVeic.tipo = t;
    if (t == 1) gVeic.qtdPneus = 4;
    else if (t == 2) gVeic.qtdPneus = 6;
    else if (t == 3) gVeic.qtdPneus = 8;
    else if (t == 4) gVeic.qtdPneus = 10;
    else {                                   // fallback razoável
        printf("Tipo invalido, vou considerar TOCO.\n");
        gVeic.tipo = 1;
        gVeic.qtdPneus = 4;
    }
}

void cadastrarPneus() {
    int i, num;
    printf("\n--- Cadastro dos PNEUS ---\n");
    for (i = 0; i < gVeic.qtdPneus; i++) {
        do {
            printf("Digite o numero do pneu %d (positivo e unico): ", i + 1);
            scanf("%d", &num);
            if (num <= 0) {
                printf("Numero invalido!\n");
            } else if (existeNumero(num)) {   // trava duplicados
                printf("Esse numero ja existe! Tente outro.\n");
                num = -1;                    // força repetir o laço
            }
        } while (num <= 0);
        gVeic.pneus[i] = num;
    }
}

void cadastrarSteps() {
    int i, q, num;
    printf("\nQuantos STEPS (estepe) deseja cadastrar? (0 a %d): ", MAX_STEPS);
    scanf("%d", &q);
    if (q < 0) q = 0;
    if (q > MAX_STEPS) q = MAX_STEPS;
    gVeic.qtdSteps = q;

    for (i = 0; i < gVeic.qtdSteps; i++) {
        do {
            printf("Digite o numero do STEP %d (positivo e unico): ", i + 1);
            scanf("%d", &num);
            if (num <= 0) {
                printf("Numero invalido!\n");
            } else if (existeNumero(num)) {   // confere contra pneus e steps
                printf("Esse numero ja existe entre pneus/steps! Tente outro.\n");
                num = -1;
            }
        } while (num <= 0);
        gVeic.steps[i] = num;
    }
}

void listarPneusESteps() {
    int i;
    printf("\n==== LISTA DE PNEUS ====\n");
    for (i = 0; i < gVeic.qtdPneus; i++) {
        printf("Pneu %02d: #%d\n", i + 1, gVeic.pneus[i]);
    }
    if (gVeic.qtdSteps > 0) {
        printf("---- STEPS ----\n");
        for (i = 0; i < gVeic.qtdSteps; i++) {
            printf("STEP %02d: #%d\n", i + 1, gVeic.steps[i]);
        }
    } else {
        printf("(Sem steps)\n");
    }
}

void mostrarDesenho() {
    // esquema bem simples (ASCII), o suficiente p/ visualizar
    printf("\n==== DESENHO ASCII ====\n");
    if (gVeic.tipo == 1) {
        printf("   Frente\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[0], gVeic.pneus[1]);
        printf("   Traseira\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[2], gVeic.pneus[3]);
    } else if (gVeic.tipo == 2) {
        printf("   Frente\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[0], gVeic.pneus[1]);
        printf("   Meio\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[2], gVeic.pneus[3]);
        printf("   Traseira\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[4], gVeic.pneus[5]);
    } else if (gVeic.tipo == 3) {
        printf("   Frente\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[0], gVeic.pneus[1]);
        printf("   Eixo 2\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[2], gVeic.pneus[3]);
        printf("   Eixo 3\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[4], gVeic.pneus[5]);
        printf("   Eixo 4\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[6], gVeic.pneus[7]);
    } else if (gVeic.tipo == 4) {
        printf("   Frente\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[0], gVeic.pneus[1]);
        printf("   Eixo 2\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[2], gVeic.pneus[3]);
        printf("   Eixo 3\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[4], gVeic.pneus[5]);
        printf("   Eixo 4\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[6], gVeic.pneus[7]);
        printf("   Eixo 5\n");
        printf("[ %d ]  [ %d ]\n", gVeic.pneus[8], gVeic.pneus[9]);
    }
    if (gVeic.qtdSteps > 0) {
        int i;
        printf("\nSTEPS: ");
        for (i = 0; i < gVeic.qtdSteps; i++) {
            printf("#%d ", gVeic.steps[i]);
        }
        printf("\n");
    }
}

void rodizio() {
    int total = gVeic.qtdPneus + gVeic.qtdSteps;  // espaço unificado
    int a, b;
    int i;

    printf("\n==== RODIZIO (Pneus + Steps, sem ponteiros) ====\n");
    printf("Posicoes numeradas:\n");
    // lista "1..qtdPneus" como pneus…
    for (i = 0; i < gVeic.qtdPneus; i++) {
        printf("%2d - Pneu #%d\n", i + 1, gVeic.pneus[i]);
    }
    // …e depois os steps
    for (i = 0; i < gVeic.qtdSteps; i++) {
        printf("%2d - STEP #%d\n", gVeic.qtdPneus + i + 1, gVeic.steps[i]);
    }

    printf("\nDigite a primeira posicao (1 a %d): ", total);
    scanf("%d", &a);
    printf("Digite a segunda posicao (1 a %d): ", total);
    scanf("%d", &b);

    if (a < 1 || a > total || b < 1 || b > total) {
        printf("Posicao invalida!\n");
        return;
    }

    // traduz posição global para índice interno e "tipo"
    int aEhPneu = (a <= gVeic.qtdPneus);
    int bEhPneu = (b <= gVeic.qtdPneus);
    int idxA = aEhPneu ? (a - 1) : (a - 1 - gVeic.qtdPneus);
    int idxB = bEhPneu ? (b - 1) : (b - 1 - gVeic.qtdPneus);

    // lê valores atuais (mantém regra de unicidade, só troca posições)
    int valorA = aEhPneu ? gVeic.pneus[idxA] : gVeic.steps[idxA];
    int valorB = bEhPneu ? gVeic.pneus[idxB] : gVeic.steps[idxB];

    // grava de volta com a troca
    if (aEhPneu) gVeic.pneus[idxA] = valorB; else gVeic.steps[idxA] = valorB;
    if (bEhPneu) gVeic.pneus[idxB] = valorA; else gVeic.steps[idxB] = valorA;

    printf("Rodizio concluido entre posicao %d e %d!\n", a, b);
}

int main() {
    int opcao;
    int rodando = 1;

    inicializar();

    if (!fazerLogin()) {
        return 0;                // sem login, não segue
    }

    printf("\n==== Sistema de Pneus (estilo aluno iniciante) ====\n");
    escolherTipo();
    cadastrarPneus();
    cadastrarSteps();

    while (rodando == 1) {
        printf("\n\n===== MENU =====\n");
        printf("1 - Mostrar pneus/steps\n");
        printf("2 - Rodizio (pneus e steps)\n");
        printf("3 - Mostrar desenho\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            listarPneusESteps();
            system("pause"); // Windows; no Linux pode tirar
        } else if (opcao == 2) {
            rodizio();
            system("pause");
        } else if (opcao == 3) {
            mostrarDesenho();
            system("pause");
        } else if (opcao == 4) {
            rodando = 0;     // finaliza loop principal
        } else {
            printf("Opcao invalida!\n");
            system("pause");
        }
    }

    printf("\nEncerrando... Valeu!\n");
    return 0;
}
