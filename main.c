#include <stdio.h>

int main(){

    FILE *file;

    file = fopen("entrada.txt","r");

    char tudo[1000];

    while(fgets(tudo, 1000, file) != NULL){
        printf("%s", tudo);
    }

    fclose(file);

    return 0;
}