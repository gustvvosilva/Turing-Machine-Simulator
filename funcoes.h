#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct MAP {
    int est_atual;
    char lendo;
    char grava;
    char direcao;
    int est_destino;
} MAP;

int descobrir_estado_inicial(MAP *mapeamento, int qtd_transicoes);
bool inserir_mapeamento(FILE *file, MAP *mapeamento, int qtd_transicoes, char *alfabeto);
char **ler_palavras(FILE *file, int qtd_palavras);