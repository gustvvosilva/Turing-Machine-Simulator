#include <stdio.h>
#include <stdlib.h>

typedef struct MAP {
    int est_atual;
    char lendo;
    char grava;
    char direcao;
    int est_destino;
} MAP;

void inserir_mapeamento(FILE *file, MAP *mapeamento, int qtd_transicoes) {

    for(int i = 0; i < qtd_transicoes; i++){

        fscanf(file, "%d %c %c %c %d", &mapeamento[i].est_atual, &mapeamento[i].lendo, 
            &mapeamento[i].grava, &mapeamento[i].direcao, &mapeamento[i].est_destino);
    }
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

    inserir_mapeamento(file, mapeamento, qtd_transicoes);  // #TODO: Falta fazer as validacoes, como verificar se a letra tem no alfabeto e tals

    for(int i = 0; i < qtd_transicoes; i++){
        printf("%d %c %c %c %d\n", mapeamento[i].est_atual, mapeamento[i].lendo, 
            mapeamento[i].grava, mapeamento[i].direcao, mapeamento[i].est_destino);
    }

    int qtd_palavras;

    fscanf(file, "%d", &qtd_palavras);
    fgets(lixo, 5, file);  // Pegar e descartar a quebra de linha.
    printf("%d\n", qtd_palavras);

    char palavras[4][10];  // #TODO: Chumbado! Mesmo problema do mapeamento.

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            palavras[i][j] = '-';  // Preenche o espaço da palavra com "espaço vazio".
        }
        fscanf(file, "%s", &palavras[i]);  // Atribue a palavra.
    }

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            if(palavras[i][j] == '\000')  // Laço APENAS pra tirar a quebra de linha das palavras.
                palavras[i][j] = '-';     // Deve ter um jeito mais inteligente de fazer...
        }
    }

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            printf("%c", palavras[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    char fita[10];  // Máquina de Turing Multi-fita por enquanto, ou seja, cada palavra em uma fita.
    int resultado, pos_cabeca, estado;


    for(int palavra = 0; palavra < qtd_palavras; palavra++){

        for(int i = 0; i < 10; i++){
            fita[i] = palavras[palavra][i];  // Joga uma palavra na fita por vez.
        }
        resultado, pos_cabeca = 0;
        estado = 1;

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

    free(mapeamento);
    fclose(file);  // Libera o arquivo txt da memória.
    return 0;
}