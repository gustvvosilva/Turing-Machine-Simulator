#include <stdio.h>
#include <stdbool.h>

int main(){

    FILE *file;

    file = fopen("entrada.txt","r");
    if(file == NULL) return -1;

    char alfabeto[30], qtd_estados[2];
    int qtd_transicoes;

    fscanf(file, "%s %s %d", &alfabeto, &qtd_estados, &qtd_transicoes);

    printf("%s %s %d\n", alfabeto, qtd_estados, qtd_transicoes);

    char lixo[5];
    fgets(lixo, 5, file); // pegar a quebra de linha

    char mapeamento[11][5];
    char linha[12];

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

    fgets(lixo, 5, file); // pegar a quebra de linha

    char palavras[4][10];

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            palavras[i][j] = '-';
        }
        fscanf(file, "%s", &palavras[i]);
    }

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            if(palavras[i][j] == '\000')
                palavras[i][j] = '-';
        }
    }

    for(int i = 0; i < qtd_palavras; i++){
        for(int j = 0; j < 10; j++){

            printf("%c", palavras[i][j]);
        }
        printf("\n");
    }

    char fita[10];
    int resultado, pos_cabeca;
    char estado[2];
    bool flag;
    char fita_print[10];

    for(int palavra = 0; palavra < qtd_palavras; palavra++){

        for(int i = 0; i < 10; i++){
            fita[i] = palavras[palavra][i];
        }
        resultado = 0, pos_cabeca = 0;
        *estado = '1';

        for(int i = 0; fita[i] != '-'; i++){
            fita_print[i] = fita[i];
        }

        do {

            flag = false;

            for(int i = 0; i < qtd_transicoes; i++){

                if(mapeamento[i][0] == *estado && mapeamento[i][1] == fita[pos_cabeca]){

                    fita[pos_cabeca] = mapeamento[i][2];
                    *estado = mapeamento[i][4];

                    if(mapeamento[i][3] == 'D'){
                        pos_cabeca++;
                    }
                    else {
                        pos_cabeca--;
                    }

                    flag = true;
                    break;
                }
            }

            if(*estado == *qtd_estados){
                resultado = 1;
            }
            else if(!flag){
                resultado = 2;
            }

        } while(resultado == 0);

        if(resultado == 1) {
            printf("%d: %s OK\n", palavra, fita_print);
        } else {
            printf("%d: %s not OK\n", palavra, fita_print);
        }
    }

    fclose(file);
    return 0;
}