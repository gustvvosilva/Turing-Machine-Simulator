#include <stdio.h>

int main(){

    FILE *file;

    file = fopen("entrada.txt","r");
    if(file == NULL) return -1;

    // char tudo[1000];

    // while(fgets(tudo, 1000, file) != NULL){
    //     printf("%s", tudo);
    // }

    char alfabeto[30];
    int qtd_estados, qtd_transicoes;

    fscanf(file, "%s %d %d", &alfabeto, &qtd_estados, &qtd_transicoes);

    printf("%s %d %d\n", alfabeto, qtd_estados, qtd_transicoes);

    // char test1[1], test2[30], test3[30];

    // fgets(test1, 100, file);
    // fgets(test2, 100, file);
    // fgets(test3, 100, file);

    // printf("\naaa%sbbb%sccc%s", test1, test2, test3);

    char lixo[2];
    fgets(lixo, 2, file); // pegar a quebra de linha

    // char oi, oi2, oi3, oi4, oi5, oi6, oi7, oi8;

    // fscanf(file, "%c %c %c %c %c %c %c %c", &oi, &oi2, &oi3, &oi4, &oi5, &oi6, &oi7, &oi8);

    // printf("aaaa%c %c %c %c %c %c %c %c", oi, oi2, oi3, oi4, oi5, oi6, oi7, oi8);

    char mapeamento[11][5];

    // for(int i = 0; i < qtd_transicoes; i++){
    //     for(int j = 0; j < 5; j++){

    //         fscanf(file, "%c", &mapeamento[i][j]);
    //         fscanf(file, "%c", &lixo[0]);
    //     }
    //     // fgets(lixo, 2, file);
    // }

    // for(int i = 0; i < qtd_transicoes; i++){
    //     fscanf(file, "%s", &mapeamento[i]);
    // }

    // for(int i = 0; i < qtd_transicoes; i++){
    //     for(int j = 0; j < 5; j++){

    //         printf("%c", mapeamento[i][j]);
    //     }
    //     printf("\n");
    // }

    // for(int i = 0; i < qtd_transicoes; i++){
    //     printf("mm%s\n", mapeamento[i]);
    // }

    // char linha[15], linha2[15];

    // fgets(linha, 15, file);
    // fgets(linha2, 15, file);

    // printf("%s", linha);
    // printf("%s", linha2);

    // printf("*%c", linha[4]);

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

    fclose(file);
    return 0;
}