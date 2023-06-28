//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"

#ifndef DERCO_FUNCIONESPRODUCTOSARREGLO_H
#define DERCO_FUNCIONESPRODUCTOSARREGLO_H

void mostrarProductosArray(struct Producto **productos, int maxProductos){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i]){
            printf("%s %s\n", productos[i] -> marca, productos[i] -> modelo);
            printf("Año de fabricacion: %d\n", productos[i] -> yearFabricado);
            printf("Numero de Chasis: %d\n", productos[i] -> numeroDeChasis);
            printf("Total de partes que componen el producto: %d", productos[i] -> totalPartes);
            printf("Total de accesorios disponibles: %d", productos[i] -> totalAccesorios);
            printf("Valor del producto: $%d", productos[i] -> costeTotal);
        }
    }
}

struct Producto *buscarProductoArray(struct Producto **productos, int maxProductos, int chasisBuscado) {
    int i;
    for (i = 0; i < maxProductos; i++) {
        if (productos[i] && productos[i] -> numeroDeChasis == chasisBuscado) return productos[i];
    }
    return NULL;
}

int agregarProductoArray(struct Producto **productos, int maxProductos, struct Producto *nuevo){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i] == NULL){
            productos[i] = nuevo;
            return 1;
        }
    }
    return 0;
}

int eliminarProductoArray(struct Producto **productos, int maxProductos, int chasisBuscado){
    int i;
    for (i = 0; i < maxProductos; i++){
        if (productos[i] && productos[i] -> numeroDeChasis == chasisBuscado){
            productos[i] = NULL;
            return 1;
        }
    }
    return 0;
}

#endif //DERCO_FUNCIONESPRODUCTOSARREGLO_H
