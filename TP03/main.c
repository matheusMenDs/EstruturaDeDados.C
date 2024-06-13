#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cidades.h"

int main(){

    double menorVizinhanca;

    menorVizinhanca = calcularMenorVizinhanca("arquivoCidades.txt");

    char* menorCidade = cidadeMenorVizinhanca("arquivoCidades.txt");

    if (menorCidade != NULL) {
        printf("Menor area de cidade|: %s\n", menorCidade);
        free(menorCidade);
    } else {
        printf("Nenhuma cidade encontrada!\n");
    }

    return 0;

}