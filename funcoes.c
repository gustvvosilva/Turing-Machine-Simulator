#include "funcoes.h"

int descobrir_estado_inicial(MAP *mapeamento, int qtd_transicoes) {
    int inicial = -1;

    for (int i = 0; i < qtd_transicoes; i++) {
        if (mapeamento[i].est_atual < inicial || inicial == -1)
            inicial = mapeamento[i].est_atual;
    }
    return inicial;
}

bool inserir_mapeamento(FILE *file, MAP *mapeamento, int qtd_transicoes, char *alfabeto) {

    for(int i = 0; i < qtd_transicoes; i++){

        fscanf(file, "%d %c %c %c %d", &mapeamento[i].est_atual, &mapeamento[i].lendo, 
            &mapeamento[i].grava, &mapeamento[i].direcao, &mapeamento[i].est_destino);

        if(strchr(alfabeto, mapeamento[i].lendo) == NULL && mapeamento[i].lendo != '-'
            || strchr(alfabeto, mapeamento[i].grava) == NULL && mapeamento[i].grava != '-'){
            return false;
        }
    }
    return true;
}

char **ler_palavras(FILE *file, int qtd_palavras) {

    char **leitura = (char **) malloc(sizeof(char *) * (qtd_palavras + 1));

    for (int i = 0; i < qtd_palavras; i++) {
        leitura[i] = (char *) calloc((100 + 1), sizeof(char));

        for(int j = 0; j < 100; j++){

            fscanf(file, "%c", &leitura[i][j]);

            if (leitura[i][j] == '\n' || leitura[i][j] == '\000') {
                leitura[i][j] = '-';
                break;
            }
        }
    }
    return leitura;
}