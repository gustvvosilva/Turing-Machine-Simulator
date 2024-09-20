#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"

int main(){

    FILE *file;  // O ponteiro do arquivo sempre aponta para o lugar que ele parou de ler (importante).

    file = fopen("entrada.txt", "r");  // Abre o arquivo txt que for passado no modo leitura.
    if(file == NULL) return -1;  // Se passar o nome do arquivo errado ele sai do programa.

    char alfabeto[30],  // Alfabeto de tamanho 30 como requisitado no PDF.
         resto[5];  // O resto serve apenas para retirar quebras de linha do ponteiro.
    int qtd_estados, qtd_transicoes, qtd_palavras;

    fscanf(file, "%s %d %d", alfabeto, &qtd_estados, &qtd_transicoes);  // Obtem as 3 primeiras linhas.
    fgets(resto, 5, file);  // Pegar e descartar a quebra de linha.
    // printf("%s\n%d\n%d\n", alfabeto, qtd_estados, qtd_transicoes);

    // Reserva na memória o espaço necessário para guardar as transições da máquina.
    MAP *mapeamento = (MAP *) malloc(qtd_transicoes * sizeof(MAP));

    // Insere o mapeamento das transições na variável
    // e também verifica se esse mapeamento contem apenas os caracteres presentes no alfabeto.
    if (!inserir_mapeamento(file, mapeamento, qtd_transicoes, alfabeto)) {
        printf("\nERRO! Foi detectado um caractere que nao esta presente no alfabeto.\nEncerrando...\n");
        free(mapeamento);
        fclose(file);
        return -1;
    }

    /*for(int i = 0; i < qtd_transicoes; i++){
        printf("%d %c %c %c %d\n", mapeamento[i].est_atual, mapeamento[i].lendo, 
            mapeamento[i].grava, mapeamento[i].direcao, mapeamento[i].est_destino);
    }*/

    fscanf(file, "%d", &qtd_palavras);  // Obtem a quantidade de palavras que serão testadas.
    fgets(resto, 5, file);  // Pegar e descartar a quebra de linha.
    // printf("%d\n", qtd_palavras);

    // Chama uma função para alocar memória para todas as palavras que serão testadas na máquina,
    // já as atribui e também verifica se os caracteres pertencem ao alfabeto.
    char **palavras = ler_palavras(file, qtd_palavras, alfabeto);

    /*for (int i = 0; i < qtd_palavras; i++) {
        printf("%s\n", palavras[i]);
    }*/

    printf("\n");

    char fita[100];  // Fita de 100 caracteres como requisitado no PDF.
    int resultado,  // resultado é tanto FLAG quanto RESPOSTA, ou seja: 0- Continua rodando, 1- OK e 2- not OK.
        pos_cabeca,  // Onde se encontra a cabeça de leitura na fita.
        estado;  // Estado atual da máquina.

    // Obtem o estado inicial (Q0) da máquina.
    int estado_inicial = descobrir_estado_inicial(mapeamento, qtd_transicoes);

    // Laço para colocar uma palavra na fita por vez.
    for(int palavra = 0; palavra < qtd_palavras; palavra++){

        limpar_fita(fita);  // Zera a fita para operar uma nova palavra.

        // Põe a palavra na fita
        for(int i = 0; i < 100; i++){
            fita[i] = palavras[palavra][i];
            if (fita[i] == '-')
                break;
        }
        resultado, pos_cabeca = 0;
        estado = estado_inicial;

        // Laço da máquina, onde será verificado se a palavra na fita pertence ou não à essa máquina.
        do {

            resultado = 2;

            for(int i = 0; i < qtd_transicoes; i++){

                // Procura o ESTADO que a máquina se encontra e o que ESTÁ LENDO o cabeçote de leitura da fita.
                if(mapeamento[i].est_atual == estado && mapeamento[i].lendo == fita[pos_cabeca]){

                    fita[pos_cabeca] = mapeamento[i].grava;  // Escreve na fita com base no mapeamento.
                    estado = mapeamento[i].est_destino;  // Próximo estado.

                    if(mapeamento[i].direcao == 'D'){  // Movimenta o cabeçote na fita.
                        pos_cabeca++;  // Direita.
                    }
                    else {
                        pos_cabeca--;  // Esquerda.
                    }

                    resultado = 0;  // Continua rodando.
                    break;  // Como é uma máquina deterministica, só tem um conjunto estado/leitura que o atende.
                }
            }

            if(estado == qtd_estados){
                resultado = 1;  // Se chegou no estado de aceitação == SUCESSO!
            }

        } while(resultado == 0);

        // Imprime a palavra sem o espaço vazio e formaliza como o professor solicitou.
        printf("%d: ", palavra);
        for(int i = 0; palavras[palavra][i] != '-'; i++){
            printf("%c", palavras[palavra][i]);
        }
        if(resultado == 1) {
            printf(" OK\n");
        } else {
            printf(" not OK\n");
        }
    }

    // Após rodar o programa, libera todos os espaços de memória que foram alocados.
    for (int i = 0; i < qtd_palavras; i++) {
        free(palavras[i]);
    }
    free(palavras);
    free(mapeamento);

    fclose(file);  // Libera o arquivo txt da memória.
    return 0;  // Finaliza com SUCESSO!
}