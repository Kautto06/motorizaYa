//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesParteArreglo.h"
#include "FuncionesAccesoriosLista.h"
#include "InterfacesExtras.h"
#include "FuncionAMayusculas.h"

#ifndef DERCO_FUNCIONESPRODUCTOSARBOL_H
#define DERCO_FUNCIONESPRODUCTOSARBOL_H

struct Producto *rellenarDatosProducto(){
    char buffer[100];
    struct Producto *temp = NULL;
    int i;
    temp = (struct Producto *)malloc (sizeof(struct Producto));
    printf("Ingrese numero de chasis del automovil:");
    scanf("%d", &(temp->numeroDeChasis));
    printf("Ingrese el año de fabricacion:");
    scanf("%d", &(temp->yearFabricado));
    printf("Ingrese la marca del automovil:");
    scanf(" %[^\n]", buffer);
    temp -> marca = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> marca, buffer);
    printf("temp marca = %s\n",temp->marca);
    printf("Ingrese el modelo del automovil:");
    scanf(" %[^\n]", buffer);
    temp -> modelo = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp->modelo, buffer);
    printf("temp modelo = %s\n",temp->modelo);
    printf("Ingrese el total de partes que componen el automovil:");
    scanf("%d", &(temp->totalPartes));
    temp ->partes = (struct Parte **)malloc(sizeof(struct Parte *) * temp -> totalPartes);
    temp ->headAccesorios = NULL;
    for (i = 0; i < temp->totalPartes; i++){
        agregarParteArray(temp->partes, temp->totalPartes, crearParte());
    }


    printf("Ingrese la cantidad maxima de accesorios disponibles para el producto:");
    scanf("%d", &(temp->totalAccesorios));
    for (i = 0; i < temp->totalAccesorios; i++){
        agregarAccesorioLista(&(temp->headAccesorios), crearNodoAccesorio(crearAccesorio((temp) -> numeroDeChasis)));
    }

    return temp;
}

void mostrarAutomovil(struct Producto *producto){
    char desicion[2];
    printf("Automovil Marca: %s\n", producto -> marca);
    printf("Modelo: %s\n", producto -> modelo);
    printf("Fabricado en el año: %d\n", producto -> yearFabricado);
    printf("Su valor total es de $%d dolares\n", producto -> costeTotal);

    while (true){
        // pasar el string leido a mayusculas
        printf("Desea ver las partes del automovil? SI/NO\n");
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        if (strcmp(desicion, "SI") == 0) {
            verPartesArray(producto -> partes, producto -> totalPartes);
            break;
        }
        else if(strcmp(desicion, "NO") == 0) break;
        printf("POR FAVOR INTRODUZCA UNA OPCION VALIDA\n");
    }

    while(true){
        // pasar el string leido a mayusculas
        printf("Desea ver los accesorios del automovil? SI/NO\n");
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        if (strcmp(desicion, "SI") == 0) {
            verAccesoriosLista(producto -> headAccesorios);
            break;
        }
        else if(strcmp(desicion, "NO") == 0) break;
        printf("POR FAVOR INTRODUZCA UNA OPCION VALIDA\n");
    }
    /*Mostrar partes y accesorios disponibles*/
}

struct Producto *buscarProducto(struct NodoProducto *raiz, int numeroDeChasis){
    if (raiz){
        if (numeroDeChasis < raiz -> automovil -> numeroDeChasis)
            return buscarProducto(raiz -> izq, numeroDeChasis); //Moverse a la izquierda
        if (numeroDeChasis > raiz -> automovil -> numeroDeChasis)
            return buscarProducto(raiz -> der, numeroDeChasis); //Moverse a la derecha
        return raiz -> automovil; //Retorna el nodo
    }
    return NULL; //Retorna NULL
}

int insertarProducto(struct NodoProducto **raiz, struct Producto *producto){
    if ((*raiz)){
        if (producto -> numeroDeChasis < (*raiz) -> automovil ->numeroDeChasis)
            return insertarProducto(&((*raiz) -> izq), producto); //Moverse a la izquierda
        if (producto -> numeroDeChasis > (*raiz) -> automovil ->numeroDeChasis)
            return insertarProducto(&((*raiz) -> der), producto); //Moverse a la derecha
        return 0;
    }
    (*raiz) = (struct NodoProducto *) malloc (sizeof(struct NodoProducto));
    if ((*raiz)){ //Validacion de memoria
        (*raiz)->automovil=producto;
        (*raiz)->izq=(*raiz)->der=NULL;
        return 1;
    }
    else return 0;
}

void mostrarProductos(struct NodoProducto *raiz){
    if (raiz){
        mostrarProductos(raiz -> izq);
        mostrarProductos(raiz -> der);
        mostrarAutomovil(raiz -> automovil);
        printf("\n");
    }
}

void reemplazar(struct NodoProducto **raiz, struct NodoProducto **aux){
    if (!((*raiz) -> der)){
        (*aux) -> automovil = (*raiz) -> automovil;
        *aux = *raiz;
        *raiz = (*raiz) -> izq;
    }
    else{
        reemplazar(&((*raiz) -> der), &(*aux));
    }
}

int eliminarProductoArbol(struct NodoProducto **raiz, int numeroChasis){
    struct NodoProducto *aux;
    if (!(*raiz)){
        return 0;
    }
    if ((*raiz) -> automovil -> numeroDeChasis < numeroChasis){
        return eliminarProductoArbol(&((*raiz) -> der), numeroChasis);
    }
    else{
        if (numeroChasis < (*raiz) -> automovil -> numeroDeChasis){
            return eliminarProductoArbol(&((*raiz) -> izq), numeroChasis);
        }
        else{
            if ((*raiz) -> automovil -> numeroDeChasis == numeroChasis){
                aux = *raiz;
                if (!((*raiz) -> izq)){
                    *raiz = (*raiz) -> der;
                }
                else{
                    if (!((*raiz) -> der)){
                        *raiz = (*raiz) -> izq;
                    }
                    else{
                        reemplazar(&((*raiz) -> izq), &aux);
                    }
                    free(aux);
                }
                return 1;
            }
        }
    }
    return 0;
}

int modificarProducto(struct NodoProducto **raiz, int numeroDeChasis){
    if (*raiz){
        if (numeroDeChasis < ((*raiz) -> automovil -> numeroDeChasis))
            return modificarProducto(&((*raiz) -> izq), numeroDeChasis); //Moverse a la izquierda
        if (numeroDeChasis > ((*raiz) -> automovil -> numeroDeChasis))
            return modificarProducto(&((*raiz) -> der), numeroDeChasis); //Moverse a la derecha
        return realizarCambiosProducto(raiz);
    }
    printf("Lo sentimos, este producto no existe en nuestro catalogo");
    return 0;
}

///////////////////FUNCION EXTRA///////////////////////////

void recorrerCompras(struct NodoCompra *rec, int *ventas)
{
    struct NodoCompra *ptr = rec;
    while(ptr != NULL)
    {
        if(strcmp(rec->datos->detalles->modelo,ptr->datos->detalles->modelo) == 0)
            ventas++;
        ptr=ptr->sig;
    }
}

struct Producto *autoMasVendidoEnSucursal(struct NodoCompra *compras)
{
    struct Producto *autoMasVendido = NULL;
    if(compras == NULL)
    {
        struct NodoCompra *rec = compras;
        int masVentas = 0;
        while(rec != NULL)
        {
            int ventas = 0;
            recorrerCompras(rec, &ventas);
            if(ventas > masVentas)
            {
                masVentas = ventas;
                autoMasVendido = rec->datos->detalles;
            }
            rec = rec->sig;
        }
    }
    return autoMasVendido;
}

#endif //DERCO_FUNCIONESPRODUCTOSARBOL_H
