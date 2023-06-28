//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesAccesoriosLista.h"


#ifndef DERCO_INTERFACESEXTRAS_H
#define DERCO_INTERFACESEXTRAS_H

int modificarCosteTotalProducto(struct Producto **producto, int nuevoCostoBase){
    int i;
    (*producto) -> costeTotal = nuevoCostoBase;
    for (i = 0; i < (*producto) -> totalPartes; i++){
        if ((*producto) ->partes[i]){
            (*producto) -> costeTotal += (*producto) -> partes[i] -> costo;
        }
        else return 0;
    }
    return 1;
}

int eliminarAccesorioIngresoChasis(struct NodoProducto**hoja){
    int chasisAEliminar;
    printf("Ingrese el numero del chasis del automovil que desea eliminar:");
    do{
        scanf("%d", &chasisAEliminar);
    } while (buscarAccesorioLista((*hoja) ->automovil ->headAccesorios, chasisAEliminar) == 0);
    (*hoja) -> automovil -> totalAccesorios -= 1;
    if(eliminarAccesorioLista(&((*hoja) -> automovil -> headAccesorios), chasisAEliminar) == 1){
        printf("Accesorio eliminado correctamente");
        return 1;
    }
    else{
        printf("Accesorio no encontrado en la lista");
        return 0;
    }
}


int realizarCambiosProducto(struct NodoProducto **hoja){
    int opcion, cambios = 0;
    int nuevoCostoBase;


    while (true){
        printf("Por favor, ingrese lo que desea modificar del producto\n");
        printf("Opcion 1: Agregar un Accesorio\n");
        printf("Opcion 2: Eliminar un accesorio\n");
        printf("Opcion 3: Cambiar el coste del producto\n");
        printf("Ingresar un 0: Finalizar modificacion\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return cambios;
            case 1:
                (*hoja) -> automovil -> totalAccesorios += agregarAccesorioLista(&((*hoja) ->automovil -> headAccesorios), crearNodoAccesorio(crearAccesorio((*hoja) -> automovil -> numeroDeChasis)));
                cambios++;
                break;
            case 2:
                eliminarAccesorioIngresoChasis(hoja);
                cambios++;
                break;

            case 3:
                printf("Ingrese el nuevo coste base del producto:");
                scanf("%d", &nuevoCostoBase);
                modificarCosteTotalProducto(&(*hoja) -> automovil, nuevoCostoBase);
                cambios++;

            default:
                printf("La opcion que usted ha ingresado no se encuentra disponible\n");
        }
    }
}



#endif //DERCO_INTERFACESEXTRAS_H
