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

int main(){  // #TODO: Organizar em funções/arquivos e limpar o código.

    FILE *file;  // O ponteiro do arquivo sempre aponta para o lugar que ele parou de ler (importante).

    file = fopen("entrada.txt", "r");  // Abre o arquivo txt que for passado no modo leitura.
    if(file == NULL) return -1;  // Se passar o nome do arquivo errado ele sai do programa.

    char alfabeto[30];
    int qtd_estados, qtd_transicoes;

    fscanf(file, "%s %d %d", &alfabeto, &qtd_estados, &qtd_transicoes);  // Obtem as 3 primeiras linhas.
    printf("%s\n%d\n%d\n", alfabeto, qtd_estados, qtd_transicoes);

    char lixo[5];
    fgets(lixo, 5, file);  // Pegar e descartar a quebra de linha.

    MAP *mapeamento = (MAP *) malloc(qtd_transicoes * sizeof(MAP));

    if (!inserir_mapeamento(file, mapeamento, qtd_transicoes, alfabeto)) {
        printf("\nERRO! Foi detectado um caractere invalido nas transicoes.\nEncerrando...\n");
        return -1;
    }

    for(int i = 0; i < qtd_transicoes; i++){
        printf("%d %c %c %c %d\n", mapeamento[i].est_atual, mapeamento[i].lendo, 
            mapeamento[i].grava, mapeamento[i].direcao, mapeamento[i].est_destino);
    }

    int qtd_palavras;

    fscanf(file, "%d", &qtd_palavras);
    fgets(lixo, 5, file);  // Pegar e descartar a quebra de linha.
    printf("%d\n", qtd_palavras);

    char **palavras = (char **) malloc(sizeof(char *) * (qtd_palavras + 1));

    for (int i = 0; i < qtd_palavras; i++) {
        palavras[i] = (char *) calloc((100 + 1), sizeof(char));

        for(int j = 0; j < 100; j++){

            fscanf(file, "%c", &palavras[i][j]);

            if (palavras[i][j] == '\n' || palavras[i][j] == '\000') {
                palavras[i][j] = '-';
                break;
            }
        }
        printf("%s\n", palavras[i]);
    }
    printf("\n");

    char fita[100];
    int resultado, pos_cabeca, estado;
    int estado_inicial = descobrir_estado_inicial(mapeamento, qtd_transicoes);

    for(int palavra = 0; palavra < qtd_palavras; palavra++){

        for(int i = 0; i < 100; i++){

            fita[i] = palavras[palavra][i];  // Joga uma palavra na fita por vez.

            if (fita[i] == '-')
                break;
        }
        resultado, pos_cabeca = 0;
        estado = estado_inicial;

        do {

            resultado = 2;  // resultado é tanto FLAG quanto RESPOSTA, ou seja: 0- Continua rodando, 1- OK e 2- not OK.

            for(int i = 0; i < qtd_transicoes; i++){

                // Procura o ESTADO que a máquina se encontra e o que ESTÁ LENDO o cabeçote de leitura da fita.
                if(mapeamento[i].est_atual == estado && mapeamento[i].lendo == fita[pos_cabeca]){

                    fita[pos_cabeca] = mapeamento[i].grava;  // Escreve na fita com base no mapeamento.
                    estado = mapeamento[i].est_destino;  // Próximo estado.

                    if(mapeamento[i].direcao == 'D'){  // Movimenta o cabeçote na fita.
                        pos_cabeca++;
                    }
                    else {
                        pos_cabeca--;
                    }

                    resultado = 0;  // Continua rodando.
                    break;  // Como é uma máquina deterministica, só tem um conjunto estado/leitura que o atende.
                }
            }

            if(estado == qtd_estados){
                resultado = 1;  // Se chegou no estado de aceitação == SUCESSO!
            }

        } while(resultado == 0);

        printf("%d: ", palavra);
        for(int i = 0; palavras[palavra][i] != '-'; i++){
            printf("%c", palavras[palavra][i]);   // Imprime a palavra sem o espaço vazio e
        }                                         // formaliza como o professor solicitou.
        if(resultado == 1) {
            printf(" OK\n");
        } else {
            printf(" not OK\n");
        }
    }

    for (int i = 0; i < qtd_palavras; i++) {
        free(palavras[i]);
    }
    free(palavras);
    free(mapeamento);
    fclose(file);  // Libera o arquivo txt da memória.
    return 0;
}