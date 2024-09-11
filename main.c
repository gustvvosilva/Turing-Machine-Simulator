#include <stdio.h>
#include <stdbool.h>

int main(){  // #TODO: Organizar em funções/arquivos e limpar o código.

    FILE *file;  // O ponteiro do arquivo sempre aponta para o lugar que ele parou de ler (importante).

    file = fopen("entrada.txt", "r");  // Abre o arquivo txt que for passado no modo leitura.
    if(file == NULL) return -1;  // Se passar o nome do arquivo errado ele sai do programa.

    char alfabeto[30], qtd_estados[2];  // qtd_estados como string pra ficar mais facil de comparar no laço principal.
    int qtd_transicoes;

    fscanf(file, "%s %s %d", &alfabeto, &qtd_estados, &qtd_transicoes);  // Obtem as 3 primeiras linhas.
    printf("%s\n%s\n%d\n", alfabeto, qtd_estados, qtd_transicoes);

    char lixo[5];
    fgets(lixo, 5, file);  // Pegar e descartar a quebra de linha.

    char mapeamento[11][5];  // #TODO: 11 transições chumbadas por enquanto, seria melhor usar lista encadeada de structs (imo).
    char linha[12];  // #TODO: Problema! Pois se o estado tiver dois digitos, essa lógica quebra.

    for(int i = 0; i < qtd_transicoes; i++){

        fgets(linha, 12, file);

        mapeamento[i][0] = linha[0];
        mapeamento[i][1] = linha[2];
        mapeamento[i][2] = linha[4];
        mapeamento[i][3] = linha[6];
        mapeamento[i][4] = linha[8];
    }

    for(int i = 0; i < qtd_transicoes; i++){
        for(int j = 0; j < 5; j++){

            printf("%c", mapeamento[i][j]);
        }
        printf("\n");
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
    int resultado, pos_cabeca;
    char estado[2];

    for(int palavra = 0; palavra < qtd_palavras; palavra++){

        for(int i = 0; i < 10; i++){
            fita[i] = palavras[palavra][i];  // Joga uma palavra na fita por vez.
        }
        resultado, pos_cabeca = 0;
        *estado = '1';

        do {

            resultado = 2;  // resultado é tanto FLAG quanto RESPOSTA, ou seja: 0- Continua rodando, 1- OK e 2- not OK.

            for(int i = 0; i < qtd_transicoes; i++){

                // Procura o ESTADO que a máquina se encontra e o que ESTÁ LENDO o cabeçote de leitura da fita.
                if(mapeamento[i][0] == *estado && mapeamento[i][1] == fita[pos_cabeca]){

                    fita[pos_cabeca] = mapeamento[i][2];  // Escreve na fita com base no mapeamento.
                    *estado = mapeamento[i][4];  // Próximo estado.

                    if(mapeamento[i][3] == 'D'){  // Movimenta o cabeçote na fita.
                        pos_cabeca++;
                    }
                    else {
                        pos_cabeca--;
                    }

                    resultado = 0;  // Continua rodando.
                    break;  // Como é uma máquina deterministica, só tem um conjunto estado/leitura que o atende.
                }
            }

            if(*estado == *qtd_estados){
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

    fclose(file);  // Libera o arquivo txt da memória.
    return 0;
}