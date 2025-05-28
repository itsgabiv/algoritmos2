/*
 * Trabalho de Algoritmos II – N2 (Peso 3)
 * Ordenação de números de cheques emitidos
 *
 * Nome: Gabriela Vieira
 * Curso: Bacharelado em Sistemas de Informação
 * Professor: Alessandro João Brassanini
 * Data de entrega: 28/05/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // para memset

#define MAX_CHEQUES 100
#define VALOR_MIN    1
#define VALOR_MAX  100

int main(void) {
    int n, valor;
    int *contador = NULL;
    int *cheques  = NULL;

    printf("Quantos cheques foram emitidos hoje (1 a %d)? ", MAX_CHEQUES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_CHEQUES) {
        printf("Quantidade invalida. Encerrando.\n");
        return EXIT_FAILURE;
    }

    // aloca vetor de contador de 0..100 e zera com memset
    contador = malloc((VALOR_MAX + 1) * sizeof *contador);
    if (!contador) {
        perror("Falha ao alocar contador");
        return EXIT_FAILURE;
    }
    memset(contador, 0, (VALOR_MAX + 1) * sizeof *contador);

    // aloca vetor dinâmico para os cheques
    cheques = malloc(n * sizeof *cheques);
    if (!cheques) {
        perror("Falha ao alocar cheques");
        free(contador);
        return EXIT_FAILURE;
    }

    // leitura e contagem
    for (int i = 0; i < n; i++) {
        printf("Cheque #%d (entre %d e %d): ", i + 1, VALOR_MIN, VALOR_MAX);
        if (scanf("%d", cheques + i) != 1 ||
            *(cheques + i) < VALOR_MIN ||
            *(cheques + i) > VALOR_MAX) {
            printf("Valor de cheque invalido. Encerrando.\n");
            free(contador);
            free(cheques);
            return EXIT_FAILURE;
        }
        contador[ *(cheques + i) ]++;
    }

    // impressão em ordem
    printf("\nCheques em ordem crescente:\n");
    for (int v = VALOR_MIN; v <= VALOR_MAX; v++) {
        while (contador[v]-- > 0) {
            printf("%d ", v);
        }
    }
    printf("\n");

    free(contador);
    free(cheques);
    return EXIT_SUCCESS;
}
