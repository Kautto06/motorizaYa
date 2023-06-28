//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesCompraListaSimple.h"
#include "FuncionesRepuestosListaSimple.h"

#ifndef DERCO_FUNCIONESRECALLSLISTASIMPLE_H
#define DERCO_FUNCIONESRECALLSLISTASIMPLE_H

void mostrarRecalls(struct NodoCompra *headRecalls){
    struct NodoCompra *rec = headRecalls;
    while (rec){
        printf("RUT del comprador: %d\n", rec -> datos ->RutComprador);
        mostrarAutomovil(rec -> datos -> detalles);
        verPartesLista(rec -> datos ->headRepuestos);
        rec = rec -> sig;
    }
}

int agregarRecall(struct NodoCompra **head, struct Compra *nuevo){
    struct NodoCompra *rec = *head;
    if (*head == NULL){
        (*head) = crearNodoCompra(nuevo);
        return 1;
    }
    while (rec){
        if (rec -> sig == NULL){
            rec -> sig = crearNodoCompra(nuevo);
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

//Implementar a futuro al sistema Funcion eliminarRecall

int eliminarRecall(struct NodoCompra **head, int numComprobante, int RUT){
    struct NodoCompra *rec = *head, *ant = NULL;
    while (rec){
        if (rec -> datos -> RutComprador == RUT && rec -> datos -> numeroComprobante == numComprobante){
            if (ant == NULL){
                (*head) = rec -> sig;
            }
            else{
                ant -> sig = rec -> sig;
            }
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}

#endif //DERCO_FUNCIONESRECALLSLISTASIMPLE_H
