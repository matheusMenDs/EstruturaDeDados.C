#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cidades.h"

Estrada *getEstrada(const char *NomeArquivo){

    FILE *arquivo;

    arquivo = fopen(NomeArquivo, "r");

    if (arquivo == NULL){
        printf("Erro!\n\n");
        exit(1);
    }


    Estrada *x = (Estrada *)(malloc(sizeof(Estrada)));

    if (x == NULL){
        printf("Erro de alocação de Memoria!\n");
        free(x);
        exit(1);
    }

    fscanf(arquivo, "%d\n", &x->T); 
    fscanf(arquivo, "%d\n", &x->N); 

    x->C = malloc(x->N * sizeof(Cidade));

    if (x->C == NULL){
        printf("Erro de alocação de Memoria!\n");
        free(x->C);
        exit(1);
    }

    int i = 0;   

    if (x->T < 3 || x->T > pow(10, 6)){ 
        printf("Erro! Estrada com tamanho inconsistente\n");
        return NULL;
    }else if (x->N < 2 || x->N > pow(10, 4)){ 
        printf("Erro! Cidades com numero inconsistente\n");
        return NULL;
    }
    
   char linha[256];

    while (fgets(linha,sizeof(linha), arquivo)){

        sscanf(linha, "%d %[^#]#", &x->C[i].Posicao, &x->C[i].Nome);

        if (x->C[i].Posicao < 0 || x->C[i].Posicao > x->T){
            printf("Erro! Distacia inconsistente\n");
            return NULL;
        }

        if (i > 0){
            if (x->C[i].Posicao == x->C[i - 1].Posicao){ 
            printf("Erro!\n");
            return NULL;
            }
        }
        
        i++; 

    if(i < 1 || i > x->N){ 
        printf("Erro! Numero de cidades nao condiz com a quantidade esperada\n");
        return NULL;
    }
    
    printf("Estrada/Cidades inicializados com sucesso\n");

        for (int i = 0; i < x->N; i++){ 
        int minIndex = i;

        for (int j = i + 1; j < x->N; j++){
            if (x->C[j].Posicao < x->C[minIndex].Posicao){
                minIndex = j;
            }
        }
        Cidade temp = x->C[minIndex];
        x->C[minIndex] = x->C[i];
        x->C[i] = temp;
    }

    fclose(arquivo);

    return x;

}

double calcularMenorVizinhanca(const char *nomeArquivo){

    Estrada *e = getEstrada(nomeArquivo);

    int numeroDeDivisas = e->N - 1;

    double posicaoDivisa[numeroDeDivisas];
    double areaCidade[e->N]; 
    for (int i = 0; i < numeroDeDivisas; i++){
        posicaoDivisa[i] = ((double)(e->C[i].Posicao + e->C[i + 1].Posicao) / 2); 
    }

    
    areaCidade[0] = posicaoDivisa [0]; 

    int fimDaEstrada = e->T;
    for (int i = 1; i < e->N; i++){
        if (i + 1 == e->N){ 
            areaCidade[i] = fimDaEstrada - posicaoDivisa[i - 1];
        }else{        
        areaCidade[i] = posicaoDivisa[i] - posicaoDivisa[i - 1];
        }
    }

    double menorVizinhanca = areaCidade[0];
    int menorCidadeIndex;

    for (int i = 0; i < e->N; i++){
        if (areaCidade[i] < menorVizinhanca){
            menorVizinhanca = areaCidade[i];
            menorCidadeIndex = i; 
        }
    }

    printf("Menor Area: %.2lf\n", menorVizinhanca);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL){
        printf("Erro na gravacao do nome da cidade\n");
        exit(1);
    }
    
    fprintf(arquivo, "%s\0", e->C[menorCidadeIndex].Nome);

    fclose(arquivo);

    return menorVizinhanca;
    
}

char *cidadeMenorVizinhanca(const char *nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro na abertura arquivo\n");
        return NULL;
    }

    char* menorCidade = NULL;
    char linha[100]; 

    while (fgets(linha, sizeof(linha), arquivo)) {

        linha[strcspn(linha, "\n")] = '\0';

        if (menorCidade == NULL || strlen(linha) < strlen(menorCidade)) {
            if (menorCidade != NULL) {
                free(menorCidade);
            }
            menorCidade = strdup(linha); 
        }
    }

    fclose(arquivo);
    return menorCidade;
}