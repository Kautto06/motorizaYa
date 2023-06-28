//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesRepuestosListaSimple.h"
#include "FuncionAMayusculas.h"

#ifndef DERCO_FUNCIONESCOMPRALISTASIMPLE_H
#define DERCO_FUNCIONESCOMPRALISTASIMPLE_H

struct Compra *buscarCompra(struct NodoCompra *head, int idComprobante){
    struct NodoCompra *rec = head;
    while(rec)
    {
        if(rec -> datos -> numeroComprobante == idComprobante) return rec -> datos;
    }
    return NULL;
}

struct Compra *crearCompra(struct Cliente **cliente, struct Producto *compra){
    struct Compra *temp = NULL;
    temp =(struct Compra *) malloc(sizeof (struct Compra));
    temp -> RutComprador = (*cliente) -> RUT;
    temp -> headRepuestos = NULL;
    printf("Ingrese el numero de comprobante:");
    scanf("%d",&(temp -> numeroComprobante));
    temp -> detalles = (struct Producto *)malloc(sizeof(struct Producto));
    temp -> detalles = compra;
    (*cliente) -> totalGastado += temp -> detalles -> costeTotal;
    return temp;
}

struct NodoCompra *crearNodoCompra(struct Compra *nuevo){
    struct NodoCompra *temp = NULL;
    temp = (struct NodoCompra *)malloc(sizeof(struct NodoCompra));
    temp ->datos = nuevo;
    temp -> sig = NULL;
    return temp;
}

int agregarCompra(struct NodoCompra **head, struct NodoCompra *nuevo)
{
    struct NodoCompra *rec = *head;

    if(!(*head))
        (*head) = nuevo;

    else{
        while (rec -> sig) {
            rec = rec->sig;
        }
        rec -> sig = nuevo;
        rec -> sig -> sig = NULL;
    }

    return 1;
}

int eliminarCompra(struct NodoCompra **head, int idComprobanteElim){
    struct NodoCompra *rec, *temp = NULL;
    rec = *head;

    while(rec)
    {
        if(rec->datos->numeroComprobante == idComprobanteElim)
        {
            if(rec == *head)
            {
                (*head) = rec -> sig;
            }
            else{
                temp -> sig = rec -> sig;
            }
            rec=NULL;
            return 1;
        }
        temp = rec;
        rec = rec->sig;
    }
    return 0;
}

void mostrarCompras(struct NodoCompra *head){
    struct NodoCompra *rec = head;
    while (rec){
        mostrarAutomovil(rec -> datos -> detalles);
        verPartesLista(rec -> datos -> headRepuestos);
        rec = rec -> sig;
    }
}

int modificarCompra(struct Compra **detalles){
    char desicion[2];

    printf("Usted solo puede modificar el numero del comprobante de la compra. ");
    printf("Desea realizar la operacion? SI/NO");
    while (true){
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        if (strcmp(desicion, "SI") == 0){
            printf("Ingrese el nuevo numero de comprobante");
            scanf("%d", &((*detalles) -> numeroComprobante));
            return 1;
        }
        if (strcmp(desicion, "NO") == 0) return 0;
        printf("La opcion igresedada no es valida intentelo nuevamente");
    }
}





#endif //DERCO_FUNCIONESCOMPRALISTASIMPLE_H
