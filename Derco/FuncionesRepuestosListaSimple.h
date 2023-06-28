//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"

#ifndef DERCO_FUNCIONESREPUESTOSLISTASIMPLE_H
#define DERCO_FUNCIONESREPUESTOSLISTASIMPLE_H

void verPartesLista(struct NodoParte *head){
    struct NodoParte *rec = head;
    while (rec){
        printf("%s\n", rec -> repuesto -> nombre);
        printf("Id asociada a la parte: $%d\n", rec -> repuesto -> idParte);
        printf("Costo individual de la parte: %d\n", rec -> repuesto -> costo);
        rec = rec -> sig;
    }
}

//Implementar a futuro en el sistem Funcion buscarParteLista y eliminarParteLista

struct Parte *buscarParteLista(struct NodoParte *head, int idParte){
    struct NodoParte *rec = head;
    while (rec){
        if (rec ->repuesto ->idParte == idParte) return rec -> repuesto;
        rec = rec -> sig;
    }
    return NULL;
}

int eliminarParteLista(struct NodoParte **head, int idParte){
    struct NodoParte *ant = NULL, *rec = *head;
    while (rec){
        if (rec -> repuesto ->idParte == idParte){
            if (ant){
                //No es el head
                ant -> sig = rec -> sig;
            }
            else{
                //Es el head;
                (*head) = (*head) -> sig;
            }
            return 1;
        }
        ant = rec;
        rec = rec -> sig;
    }
    return 0;
}

int agregarParteLista(struct NodoParte **headRepuestos, struct Parte *dato){
    struct NodoParte *rec = *headRepuestos;
    struct NodoParte *temp;
    while (rec){
        if (rec -> sig == NULL){
            temp = (struct NodoParte *)malloc(sizeof(struct NodoParte));
            temp -> repuesto = dato;
            temp -> sig = NULL;
            rec -> sig = temp;
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}


int contarGastosRepuestos(struct NodoParte *head){
    int contador = 0;
    struct NodoParte *rec = head;
    while (rec){
        contador += rec -> repuesto -> costo;
        rec = rec -> sig;
    }
    return contador;
}

#endif //DERCO_FUNCIONESREPUESTOSLISTASIMPLE_H
