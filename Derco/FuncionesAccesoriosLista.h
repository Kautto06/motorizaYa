//
// Created by gerar on 6/23/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesaAccesoriosArreglo.h"

#ifndef DERCO_FUNCIONESACCESORIOSLISTA_H
#define DERCO_FUNCIONESACCESORIOSLISTA_H

struct Accesorio *crearAccesorio(int numChasisAsociado){
    char buffer[100];
    struct Accesorio *temp=NULL;
    temp = (struct Accesorio *)malloc(sizeof(struct Accesorio));
    printf("Ingrese el nombre del accesorio:");
    scanf(" %s[^\n]", buffer);
    temp -> nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);
    printf("Ingrese el costo del accesorio:");
    scanf("%d", &(temp -> costo));
    printf("Ingrese el id con el que se identificara al accesorio:");
    scanf("%d", &(temp -> idAccesorio));
    temp -> numeroDeChasisAsociado = numChasisAsociado;

    return temp;
}

struct NodoAccesorio *crearNodoAccesorio(struct Accesorio *nuevo){
    struct NodoAccesorio *temp = NULL;

    temp = (struct NodoAccesorio *)malloc(sizeof(struct NodoAccesorio));
    temp -> accesorio = nuevo;
    temp -> sig = NULL;

    return temp;
}

int agregarAccesorioLista(struct NodoAccesorio **head, struct NodoAccesorio *nuevo){

    struct NodoAccesorio *rec = *head;

    if (*head == NULL){
        *head = nuevo;
        return 1;
    }
    else {
        while (rec) {
            if (rec->sig == NULL) {
                rec->sig = nuevo;
                return 1;
            }
            rec = rec->sig;
        }
    }
    return 0;
}

void verAccesoriosLista(struct NodoAccesorio *head){
    struct NodoAccesorio *rec = head;
    printf("Numero de chasis con el cual estan asociados los accesorios: %d\n", rec -> accesorio ->numeroDeChasisAsociado);
    if (head == NULL){
        printf("Producto no tiene accesorios!\n");
    }
    else{
        while (rec) {
            printf("%s\n", rec->accesorio->nombre);
            printf("Id asociado al accesorio: %d\n", rec->accesorio->idAccesorio);
            printf("Coste del accesorio: $%d\n\n", rec->accesorio->idAccesorio);
            rec = rec->sig;
        }
    }
}

struct Accesorio *buscarAccesorioLista(struct NodoAccesorio *headAccesorios, int idBuscado){
    struct NodoAccesorio *rec = headAccesorios;
    while (rec){
        if (rec -> accesorio ->idAccesorio == idBuscado) return rec -> accesorio;
        rec = rec -> sig;
    }
    return NULL;
}

int eliminarAccesorioLista(struct NodoAccesorio **headAccesorios, int idAccesorioAEliminar){
    struct NodoAccesorio *rec = *headAccesorios;
    struct NodoAccesorio *ant = NULL;

    while (rec) {
        if (rec->accesorio->idAccesorio == idAccesorioAEliminar) {
            if (ant != NULL) { //no es el head
                ant->sig = rec->sig;
                rec = ant;
            } else { //es el head
                (*headAccesorios) = rec->sig;
            }
            return 1;
        }
        ant = rec;
        rec = rec->sig;
    }
    return 0;
}


//Implementar a futuro al sistema Funcion modificarAccesorioLista
int modificarAccesorioLista(struct NodoAccesorio **headAccesorios, int idAccesorio){
    struct NodoAccesorio *rec = *headAccesorios;
    while (rec){
        if (rec ->accesorio ->idAccesorio == idAccesorio){
            modificarAccesorio(&(rec ->accesorio));
            return 1;
        }
        rec = rec -> sig;
    }
    return 0;
}


#endif //DERCO_FUNCIONESACCESORIOSLISTA_H
