//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"

#ifndef DERCO_FUNCIONESAACCESORIOSARREGLO_H
#define DERCO_FUNCIONESAACCESORIOSARREGLO_H

void verAccesoriosArray(struct Accesorio **vectorAccesorios, int maxAccesorios){
    int i;
    int seMostroChasis = 0;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i]){
            if (seMostroChasis == 0){
                printf("Numero de chasis con el cual estan asociados los accesorios: %d\n", vectorAccesorios[i] -> numeroDeChasisAsociado);
                seMostroChasis++;
            }
            printf("%s\n", vectorAccesorios[i]->nombre);
            printf("Id asociado al accesorio: %d\n", vectorAccesorios[i]->idAccesorio);
            printf("Coste del accesorio: $%d\n\n", vectorAccesorios[i]->costo);
        }
    }
}

struct Accesorio *buscarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, int idBuscado){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] && vectorAccesorios[i] -> idAccesorio == idBuscado){
            return vectorAccesorios[i];
        }
    }
    return NULL;
}

int agregarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, struct Accesorio *nuevo){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] == NULL){
            vectorAccesorios[i] = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarAccesorioArray(struct Accesorio **vectorAccesorios, int maxAccesorios, int idBuscado){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (vectorAccesorios[i] && vectorAccesorios[i] -> idAccesorio == idBuscado){
            vectorAccesorios[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void modificarAccesorio(struct Accesorio **accesorioAModificar){
    int opcion;
    int temp;
    printf("Seleccione que desea modificar de este accesorio\n");
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
                (*accesorioAModificar) -> idAccesorio = temp;
                break;

            case 2:
                printf("Seleccione el nuevo precio que tendra la parte:");
                scanf("%d", &temp);
                (*accesorioAModificar) -> costo = temp;
                break;

            default:
                printf("La opcion que ingreso no coincide con ninguna presentada, por favor, intentelo nuevamente\n");
                break;
        }
    }
}


//Implementar a futuro al sistema Funcion modificarAccesorioArray
int modificarAccesorioArray(struct Accesorio **accesorios, int maxAccesorios, int idAccesorio, int numChasis){
    int i;
    for (i = 0; i < maxAccesorios; i++){
        if (accesorios[i] && accesorios[i] ->idAccesorio == idAccesorio && accesorios[i] ->numeroDeChasisAsociado == numChasis){
            modificarAccesorio(&accesorios[i]);
            return 1;
        }
    }
    return 0;
}

#endif //DERCO_FUNCIONESAACCESORIOSARREGLO_H
