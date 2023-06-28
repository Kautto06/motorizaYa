//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesProductosArreglo.h"
#include "FuncionesParteArreglo.h"
#include "FuncionesaAccesoriosArreglo.h"
#include "FuncionesRecallsListaSimple.h"

#ifndef DERCO_FUNCIONESSUCURSALLISTACIRCULAR_H
#define DERCO_FUNCIONESSUCURSALLISTACIRCULAR_H

void mostrarStock(struct Stock *almacenamiento){
    printf("Automoviles a la venta:\n");
    mostrarProductosArray(almacenamiento -> autosEnVenta, almacenamiento -> maxProductos);
    printf("\nRepuestos disponibles:\n");
    verPartesArray(almacenamiento ->repuestosEnVenta, almacenamiento -> maxRepuestos);
    printf("\nAccesorios en venta:\n");
    verAccesoriosArray(almacenamiento -> accesoriosDisponibles, almacenamiento -> maxAccesorios);
}

void mostrarSucursales(struct NodoSucursal *head){
    struct NodoSucursal *rec = head;
    do {
        printf("Jefe de la sucursal: %s\n", rec ->sucursal -> director);
        printf("Direccion: %s\n", rec -> sucursal -> direccion);
        printf("Comuna:%s\n", rec -> sucursal -> comuna);
        mostrarStock(rec -> sucursal -> almacenamiento);
        mostrarRecalls(rec -> sucursal -> headRecalls);
        rec = rec -> sig;
    }while (rec != head);
}

struct Sucursal *buscarSucursal(struct NodoSucursal *head, char *comuna, char *direccion){
    struct NodoSucursal *rec=head;
    do{
        if (strcmp(rec ->sucursal ->comuna, comuna) == 0 &&
            strcmp(rec ->sucursal ->direccion, direccion) == 0) return rec->sucursal;
        rec = rec -> sig;
    }while (rec != head);
    return NULL;
}

void modificarDatosSucursal(struct NodoSucursal **headSucursales) {
    char comunaBusc[100], direccionBusc[100], nuevoDirector[100];
    struct Sucursal *sucursalBuscada = NULL;
    char desicion[2];

    printf("Ingrese la comuna y direccion de la sucursal que desea cambiar");
    while (sucursalBuscada == NULL || strlen(comunaBusc) == 0) {
        printf("Escriba la comuna de la sucursal:");
        scanf(" %[^\n]", comunaBusc); // CHEQUEAR ESTE SCAN DE STRING
        printf("Escriba la direccion de la sucursal:");
        scanf(" %[^\n]", direccionBusc);
        sucursalBuscada = buscarSucursal((*headSucursales), comunaBusc, direccionBusc);
    }
    printf("El unico dato que puede ser cambiado es el director debido a falta de permisos\n");
    while (1){
        printf("Ingrese el nombre del nuevo director:");
        scanf(" %[^\n] ", nuevoDirector);
        printf("Esta seguro de colocar a este nuevo director? SI/NO");
        scanf(" %[^\n]", desicion);
        if (strcmp(sucursalBuscada -> director, nuevoDirector) == 0){
            printf("Usted no puede colocar como nuevo director al actual\n");
        }
        else{
            if (strcmp(desicion, "SI") == 0) {
                strcpy(sucursalBuscada->director, nuevoDirector);
                return;
            }
            if (strcmp(desicion, "NO") == 0){
                printf("Desea ingresar otro nombre? SI/NO");
                scanf(" %[\n]", desicion);
                if (strcmp(desicion, "NO") == 0){
                    return;
                }
                if (strcmp(desicion, "SI") != 0){
                    printf("Por favor, ingrese una opcion valida\n");
                }
            }
        }
    }
}

struct Producto *busquedaAutoNumeroChasis(struct NodoProducto *abb){
    int numeroDeChasis;
    struct Producto *automovil;
    printf("Ingrese el numero de chasis del producto que desea agregar:");
    do {
        scanf("%d", &numeroDeChasis);
        automovil = buscarProducto(abb, numeroDeChasis);
    } while (automovil == NULL);
    return automovil;
}

struct Parte *busquedaRepuestoSegunAuto(struct NodoProducto *abb){
    int numeroDeChasis,id;
    struct Producto *automovil;
    struct Parte *repuesto;
    printf("Ingrese el id del repuesto que desea agregar junto al numero de chasis asociado");
    do {
        scanf("%d %d", &id, &numeroDeChasis);
        automovil = buscarProducto(abb, numeroDeChasis);
        if (automovil != NULL) {
            repuesto = buscarParteArray(automovil->partes, automovil->totalPartes, id);
        } else {
            printf("El numero de chasis ingresado no coincide con ningun producto de nuestro catalogo\n");
        }
    } while (repuesto == NULL);
    return repuesto;
}

struct Accesorio *busquedaAccesorioSegunAuto(struct NodoProducto *abb){
    int numeroDeChasis,id;
    struct Producto *automovil;
    struct Accesorio *accesorio;
    printf("Ingrese el id del accesorio que desea agregar junto al numero de chasis asociado");
    do {
        scanf("%d %d", &id, &numeroDeChasis);
        automovil = buscarProducto(abb, numeroDeChasis);
        if (automovil != NULL) {
            accesorio = buscarAccesorioLista(automovil->headAccesorios, id);
        } else {
            printf("El numero de chasis ingresado no coincide con ningun producto de nuestro catalogo\n");
        }
    } while (accesorio == NULL);
    return accesorio;
}

struct Stock *rellenarAlmacenes(struct NodoProducto *arbol) {
    struct Stock *temp = NULL;
    int opcion;
    int numeroDeChasis, id;
    struct Producto *automovil = NULL;
    struct Parte *repuesto = NULL;
    struct Accesorio *accesorio = NULL;

    temp = (struct Stock *) malloc(sizeof(struct Stock));
    printf("Ingrese la cantidad maxima de productos que se pueden almacenenar:");
    scanf("%d", &temp->maxProductos);
    temp->autosEnVenta = (struct Producto **) malloc(sizeof(struct Producto *) * temp->maxProductos);
    temp->totalProductos = 0;

    printf("Ingrese la cantidad maxima de repuestos que se pueden almacenenar:");
    scanf("%d", &temp->maxRepuestos);
    temp->repuestosEnVenta = (struct Parte **) malloc(sizeof(struct Parte *) * temp->maxRepuestos);
    temp->totalRepuestos = 0;

    printf("Ingrese la cantidad maxima de accesorios que se pueden almacenenar:");
    scanf("%d", &temp->maxAccesorios);
    temp->accesoriosDisponibles = (struct Accesorio **) malloc(sizeof(struct Accesorio *) * temp->maxAccesorios);
    temp->totalAccesorios = 0;

    while (true) {
        printf("Por favor, seleccione una opcion:\n");
        printf("Opcion 1: Agregar Producto:\n");
        printf("Opcion 2: Agregar Repuesto:\n");
        printf("Opcion 3: Agregar Accesorio:\n");
        printf("Ingresar un 0: Salir");
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return temp;

            case 1:
                if (temp->totalProductos < temp->maxProductos) {
                    automovil= busquedaAutoNumeroChasis(arbol);
                    temp->totalProductos += agregarProductoArray(temp->autosEnVenta, temp->maxProductos, automovil);
                } else {
                    printf("Lo sentimos, no queda espacio dentro del almacen para guardar mas automoviles");
                }
                break;

            case 2:
                if (temp->totalRepuestos < temp->maxRepuestos) {
                    repuesto= busquedaRepuestoSegunAuto(arbol);
                    temp->totalRepuestos = agregarParteArray(temp->repuestosEnVenta, temp->maxRepuestos, repuesto);
                } else {
                    printf("Lo sentimos, no queda espacio dentro del almacen para guardar mas repuestos");
                }
                break;
            case 3:
                if (temp->totalAccesorios < temp->maxAccesorios) {
                    accesorio= busquedaAccesorioSegunAuto(arbol);
                    temp->totalAccesorios += agregarAccesorioArray(temp->accesoriosDisponibles, temp->maxAccesorios,accesorio);
                }
                break;
            default:
                printf("Lo sentimos, esa opcion no se encuentra disponible\n");
                break;
        }
    }

}


struct Sucursal *rellenarDatosSucursal(struct NodoProducto *arbol){
    struct Sucursal *temp;
    char buffer[100];

    temp = (struct Sucursal *)malloc(sizeof(struct Sucursal));
    printf("Ingrese el nombre del director de esta sucursal:");
    scanf(" %[^\n]", buffer);
    temp -> director = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> director, buffer);

    printf("Ingrese el nombre de la comuna donde esta la sucursal:");
    scanf(" %[^\n]", buffer);
    temp -> comuna = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> comuna, buffer);

    printf("Ingrese la direccion de esta sucursal:");
    scanf(" %[^\n]", buffer);
    temp -> direccion = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> direccion, buffer);

    temp -> almacenamiento = NULL;
    if (arbol == NULL){
        printf("Lo sentimos, no se pueden rellenar los almacenes debido a que no existe catalogo\n");
    }
    else {
        temp -> almacenamiento = rellenarAlmacenes(arbol);
    }
    temp -> headRecalls = NULL;
    return temp;
}

struct NodoSucursal *crearNodoSucursal(struct Sucursal *nuevo){
    struct NodoSucursal *temp = NULL;
    temp = (struct NodoSucursal *)malloc(sizeof(struct Sucursal));
    temp -> sucursal = nuevo;
    temp -> ant = temp -> sig = NULL;
    return temp;
}

int agregarSucursal(struct NodoSucursal **head, struct NodoSucursal *nuevo){
    if (nuevo){
        if ((*head) == NULL) {
            (*head) = nuevo;
            (*head)->ant = (*head)->sig = (*head);
            return 1;
        } else {
            nuevo->ant = (*head)->ant;
            (*head)->ant->sig = nuevo;
            nuevo->sig = (*head);
            (*head)->ant = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarSucursal(struct NodoSucursal **head, char *comuna, char *direccion){
    struct NodoSucursal *rec;
    if(*head!=NULL)
    {
        rec = *head;
        do{
            if (strcmp(rec->sucursal->comuna, comuna) == 0 && strcmp(rec->sucursal->direccion, direccion) == 0) {
                if (rec->sig == (*head) && rec->ant == (*head) && rec == (*head)) {
                    (*head) = NULL;
                    return 1;
                } else {
                    if (rec == *head) {
                        (*head) = (*head)->sig;
                        (*head)->ant = rec->ant;
                        rec->ant->sig = (*head);
                    } else {
                        rec->ant->sig = rec->sig;
                        rec->sig->ant = rec->ant;
                    }
                    rec = NULL;
                    return 1;
                }
            }
            rec = rec->sig;
        }while (rec != *head);
    }
    return 0;
}

#endif //DERCO_FUNCIONESSUCURSALLISTACIRCULAR_H
