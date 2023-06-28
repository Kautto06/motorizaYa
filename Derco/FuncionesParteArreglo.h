//
// Created by gerar on 6/23/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Structs.h"

#ifndef DERCO_FUNCIONESPARTEARREGLO_H
#define DERCO_FUNCIONESPARTEARREGLO_H

struct Parte *crearParte(){
    char buffer[100];
    struct Parte *temp=NULL;
    temp = (struct Parte *)malloc(sizeof(struct Parte));
    printf("Ingrese el nombre de la parte:");
    scanf(" %[^\n]", buffer);
    temp ->nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);
    printf("Ingrese el id de la parte:");
    scanf("%d", &(temp -> idParte));
    printf("Ingrese el coste de esta parte:");
    scanf("%d", &(temp -> costo));
    return temp;
}

void verPartesArray(struct Parte **vectorPartes, int maxPartes){
    int i;
    int seMostroChasis = 0;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i]){
            if (seMostroChasis == 0){
                printf("Numero de chasis al que pertenecen las partes: %d\n", vectorPartes[i] -> numeroDeChasisAsociado);
                seMostroChasis++;
            }
            printf("%s\n", vectorPartes[i] -> nombre);
            printf("Id asociada a la parte: %d\n", vectorPartes[i] -> idParte);
            printf("Costo individual de la parte: $%d\n", vectorPartes[i] -> costo);
        }
    }
}

int agregarParteArray(struct Parte **vectorPartes, int maxPartes, struct Parte *nuevo){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] == NULL){
            vectorPartes[i] = nuevo;
            return 1;
        }
    }
    return 0;
}

struct Parte *buscarParteArray(struct Parte **vectorPartes, int maxPartes, int idBuscado){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] && vectorPartes[i] -> idParte == idBuscado) return vectorPartes[i];
    }
    return NULL;
}

int eliminarParteArray(struct Parte **vectorPartes, int maxPartes, int idBuscado){
    int i;
    for (i = 0; i < maxPartes; i++){
        if (vectorPartes[i] && vectorPartes[i] -> idParte == idBuscado){
            vectorPartes[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void modificarParte(struct Parte **parteAModificar){
    int opcion;
    int temp;
    printf("Seleccione que desea modificar de esta parte\n");
    printf("Opcion 1: Modificar id\n");
    printf("Opcion 2: Modificar precio.\n");
    printf("Ingresar un 0: Salir.");
    while (1){
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;

            case 1:
                printf("Ingrese el nuevo id que desea asociar con la parte:");
                scanf("%d", &temp);
                (*parteAModificar) -> idParte = temp;
                break;

            case 2:
                printf("Seleccione el nuevo precio que tendra la parte:");
                scanf("%d", &temp);
                (*parteAModificar) -> costo = temp;
                break;

            default:
                printf("La opcion que ingreso no coincide con ninguna presentada, por favor, intentelo nuevamente\n");
                break;
        }
    }
}

//Implementar a futuro al sistema Funcion modificarParteArray

int modificarParteArray(struct Parte **partes, int maxPartes, int idParte, int numChasis){
    int i;
    for (i = 0; i < maxPartes; i++) {
        if (partes[i] && partes[i]->idParte == idParte && partes[i]->numeroDeChasisAsociado == numChasis){
            modificarParte(&partes[i]);
            return 1;
        }
    }
    return 0;
}


#endif //DERCO_FUNCIONESPARTEARREGLO_H
