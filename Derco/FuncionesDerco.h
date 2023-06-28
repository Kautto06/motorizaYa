//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"

#ifndef DERCO_FUNCIONESDERCO_H
#define DERCO_FUNCIONESDERCO_H

struct Derco *crearEmpresa(){
    struct Derco *temp;
    char jefe[100];
    temp = (struct Derco *)malloc(sizeof(struct Derco));
    printf("Ingrese el nombre del Jefe a cargo de la empresa:");
    scanf(" %[^\n]", jefe);
    temp -> jefe = (char *)malloc(sizeof(char) * strlen(jefe));
    strcpy(temp -> jefe, jefe);
    temp->raizProductos = NULL;
    temp->totalProductos = 0;
    temp->region = NULL;
    temp ->ganancias = 0;
    return temp;
}

#endif //DERCO_FUNCIONESDERCO_H
