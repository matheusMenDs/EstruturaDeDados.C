#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float X, Y;
} Ponto;

float calcAreaTriangulo(Ponto p1, Ponto p2, Ponto p3) {
    return abs((p1.X*(p2.Y-p3.Y) + p2.X*(p3.Y-p1.Y) + p3.X*(p1.Y-p2.Y)) / 2.0);
}

float calcAreaPoligono(char *filename) {
    FILE *file;
    int nVertices, i;
    float areaTotal = 0.0;
    Ponto *valores;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro!! .\n");
        exit(1);
    }

    fscanf(file, "%d", &nVertices);

    valores = (Ponto *)malloc(nVertices * sizeof(Ponto));
    if (valores == NULL) {
        printf("Erro de memoria!! \n");
        exit(1);
    }

    for (i = 0; i < nVertices; i++) {
        fscanf(file, "%f,%f", &valores[i].X, &valores[i].Y);
    }

    fclose(file);

    for (i = 1; i < nVertices - 1; i++) {
        areaTotal += calcAreaTriangulo(valores[0], valores[i], valores[i+1]);
    }

    free(valores);

    return areaTotal;
}

int main() {
    float Area;

    Area = calcAreaPoligono("valores.txt");

    printf("AREA DO POLIGONO: %.2f\n", Area);

    return 0;
}
