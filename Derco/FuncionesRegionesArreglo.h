//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesClientesListaSimple.h"
#include "FuncionesSucursalListaCircular.h"
#include "FuncionesClientesListaSimple.h"

#ifndef DERCO_FUNCIONESREGIONESARREGLO_H
#define DERCO_FUNCIONESREGIONESARREGLO_H

void mostrarRegiones(struct Region **regiones, int maxRegiones){
    int i;
    char desicion[2];
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i]){
            printf("Numero de region: %d\n", regiones[i] -> numRegion);
            printf("Cantidad de clientes en la region: %d\n", regiones[i] -> cantClientes);
            printf("Desea ver los datos de cada cliente? Introduzca SI o NO\n");
            while (true){
                scanf(" %[^\n]", desicion);
                AMayusculas(desicion);
                if (strcmp(desicion, "SI") == 0){
                    if (regiones[i] -> headClientes == NULL){
                        printf("Lo sentimos, no existen Clientes en nuestra base de datos respecto a esta region\n");
                    }
                    else{
                        mostrarClientes(regiones[i]->headClientes);
                    }
                    break;
                }
                else if (strcmp(desicion, "NO") != 0){
                    printf("Por favor, introduzca una opcion valida");
                }
                else break;
            }
            printf("Cantidad de sucursales operando en la region: %d\n", regiones[i] -> cantSucursales);
            printf("Desea ver los datos de cada sucursales? Introduzca SI o NO\n");
            while (true){
                scanf(" %[^\n]", desicion);
                AMayusculas(desicion);
                if (strcmp(desicion, "SI") == 0){
                    if (regiones[i] -> headSucursales == NULL){
                        printf("Lo sentimos, no existen sucursales en nuestras bases de datos operando en la region\n");
                    }
                    else{
                        mostrarSucursales(regiones[i]->headSucursales);
                    }
                    break;
                }
                else if (strcmp(desicion, "NO") != 0){
                    printf("Por favor, introduzca una opcion valida");
                }
                else break;
            }

        }
    }
}

struct Region *buscarRegion(struct Region **regiones, int maxRegiones, int numRegionBuscada){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] && regiones[i] -> numRegion == numRegionBuscada) return regiones[i];
    }
    return NULL;
}

int agregarRegion(struct Region **regiones, int maxRegiones, struct Region *nueva){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] == NULL){
            regiones[i] = (struct Region *)malloc(sizeof(struct Region));
            regiones[i]=nueva;
            return 1;
        }
    }
    return 0;
}

int eliminarRegion(struct Region **regiones, int maxRegiones, int numRegion){
    int i;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] && regiones[i] ->numRegion == numRegion){
            regiones[i] = NULL;
            return 1;
        }
    }
    return 0;
}



int calcularGanancia(struct Region *datosRegion){
    int contador = 0;
    struct NodoCliente *rec = datosRegion -> headClientes;
    while (rec){
        contador += contarGastosCliente(rec -> cliente -> headCompras);
        rec = rec -> sig;
    }
    return contador;
}


struct Region *calcularRegionMenorGanancia(struct Region **regiones, int maxRegiones, int *menor){
    int i;
    int menorGanancia;
    struct Region *regionMasIneficiente=NULL;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] != NULL){
            if (!regionMasIneficiente || menorGanancia > calcularGanancia(regiones[i]))
            {
                menorGanancia = calcularGanancia(regiones[i]);
                regionMasIneficiente=regiones[i];
            }
        }
    }
    (*menor)=menorGanancia;
    return regionMasIneficiente;
}

struct Region *calcularRegionMayorGanancia(struct Region **regiones, int maxRegiones, int *mayor){
    int i;
    int mayorGanancia;
    struct Region *regionMasEficiente;
    for (i = 0; i < maxRegiones; i++){
        if (regiones[i] != NULL){
            if (!regionMasEficiente || mayorGanancia < calcularGanancia(regiones[i]))
            {
                mayorGanancia = calcularGanancia(regiones[i]);
                regionMasEficiente = regiones[i];
            }

        }
    }
    (*mayor)=mayorGanancia;
    return regionMasEficiente;
}

struct Region *crearRegion(){
    struct Region *temp;
    temp = (struct Region *)malloc(sizeof(struct Region));
    printf("Ingrese el numero de la region:");
    scanf("%d", &(temp->numRegion));
    printf("Ingrese la cantidad de clientes en la region:");
    scanf("%d", &(temp->cantClientes));
    printf("Ingrese la cantidad de Sucursales operando en la region:");
    scanf("%d", &(temp->cantSucursales));
    temp->headClientes=NULL;
    temp->headSucursales=NULL;
    return temp;
}

struct Region **crearArrayRegiones(int maxRegiones){
    struct Region **temp=NULL;
    temp = (struct Region **)malloc(sizeof(struct Region *) * maxRegiones);
    return temp;
}




#endif //DERCO_FUNCIONESREGIONESARREGLO_H
