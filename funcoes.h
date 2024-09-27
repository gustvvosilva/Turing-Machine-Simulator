#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct MAP {
    int est_atual;     // Estado corrente;
    char lendo;        // Símbolo do alfabeto lido;
    char grava;        // Gravar na fita;
    char direcao;      // Direção do movimento da cabeça na fita;
    int est_destino;   // Próximo estado.
} MAP;

int descobrir_estado_inicial(MAP *mapeamento, int qtd_transicoes);
bool inserir_mapeamento(FILE *file, MAP *mapeamento, int qtd_transicoes, char *alfabeto);
char **ler_palavras(FILE *file, int qtd_palavras, char *alfabeto);
void limpar_fita(char *fita);