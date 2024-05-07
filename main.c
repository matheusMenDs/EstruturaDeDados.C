#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTA_DE_CORTE 7.0

typedef struct {
    char Nome[75]; char Telefone[30]; char Curso[30];
    float Nota1; float Nota2; char *consideracaoFinal;
} Aluno;

void lerCSV(const char *filename) {
    FILE *entrada = fopen(filename, "r");
    FILE *saida = fopen("output/SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        perror("Erro!!");
        exit(EXIT_FAILURE);
    }

    char Linha[1000];

    fgets(Linha, sizeof(Linha), entrada);

    printf("Nome,Media,Situacao Final\n");

    while (fgets(Linha, sizeof(Linha), entrada)) {

        Aluno aluno;

        char *token = strtok(Linha, ",");
        strcpy(aluno.Nome, token);
     
        token = strtok(NULL, ",");
        strcpy(aluno.Telefone, token);

        token = strtok(NULL, ",");
        strcpy(aluno.Curso, token);

        token = strtok(NULL, ",");
        aluno.Nota1 = atof(token);

        token = strtok(NULL, ",");
        aluno.Nota2 = atof(token);

        double media = (double)(aluno.Nota1 + aluno.Nota2) / 2.0;

        aluno.consideracaoFinal = (media >= NOTA_DE_CORTE) ? "APROVADO" : "REPROVADO";

        char formatString[5000];

        sprintf(formatString, "%s,%.2lf,%s", aluno.Nome, (double)media, aluno.consideracaoFinal);

        printf("%s\n", formatString);

        fprintf(saida, "%s\n", formatString);
    }

    fclose(saida);
    fclose(entrada);
}

int main() {

    lerCSV("DadosEntrada.csv");

    return 0;
}
