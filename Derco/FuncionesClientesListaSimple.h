//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionAMayusculas.h"
#include "FuncionesCompraListaSimple.h"

#ifndef DERCO_FUNCIONESCLIENTESLISTASIMPLE_H
#define DERCO_FUNCIONESCLIENTESLISTASIMPLE_H

struct Cliente *buscarCliente(struct NodoCliente *head, int RUTBuscado){
    struct NodoCliente *rec = head;
    while (rec){
        if (rec -> cliente ->RUT == RUTBuscado) return rec -> cliente;
        rec = rec -> sig;
    }
    return NULL;
}

int modificarMailCliente(struct Cliente **cliente) {
    char desicion[2];
    char nuevoMail[100];

    printf("Desea seguir con la operacion? SI/NO:\n");
    while (1){
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        if (strcmp(desicion, "SI") == 0){
            printf("Por favor, ingrese el nuevo email: ");
            scanf(" %[^\n]", nuevoMail);
            strcpy((*cliente) -> email, nuevoMail);
            return 1;
        }
        else if (strcmp(desicion, "NO") == 0) return 0;
        printf("La desicion que usted ingreso no coincide con ninguna opcion presentada.\n");
    }
}

struct Cliente *crearCliente(){
    struct Cliente *temp = NULL;
    char buffer[100];
    temp = (struct Cliente *)malloc(sizeof(struct Cliente));
    printf("Ingrese el nombre del cliente:");
    scanf(" %s[^\n]", buffer);
    temp -> nombre = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> nombre, buffer);

    printf("Ingrese el RUT del cliente:");
    scanf("%d", &(temp -> RUT));

    printf("Ingrese e-mail de contacto del cliente:");
    scanf(" %[^\n]", buffer);
    temp -> email = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> email, buffer);

    printf("Ingrese la region de residencia del cliente:");
    scanf("%d", &(temp -> numRegion));

    printf("Ingrese la comuna donde vive el cliente:");
    scanf(" %[^\n]", buffer);
    temp -> comuna = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> comuna, buffer);

    printf("Ingrese la direccion del domicilio del cliente:");
    scanf(" %[^\n]", buffer);
    temp -> direccion = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(temp -> direccion, buffer);

    temp -> totalGastado = 0;
    temp -> headCompras = NULL;

    return temp;
}

struct NodoCliente *crearNodoCliente(struct Cliente *nuevo){
    struct NodoCliente *temp;
    temp = (struct NodoCliente *)malloc (sizeof(struct NodoCliente));
    temp -> cliente = nuevo;
    temp -> sig = NULL;
    return temp;
}

int agregarCliente(struct NodoCliente **head, struct NodoCliente *nuevo){
    struct NodoCliente *rec = *head;
    if (!(*head)){
        (*head) = nuevo;
    }
    else{
        while (rec) {
            if (rec->sig == NULL) {
                rec -> sig = nuevo;
                rec = rec -> sig;
            }
            rec = rec -> sig;
        }
    }
    return 1;

}

int eliminarCliente(struct NodoCliente **head, int RUT){
    struct NodoCliente *rec = *head, *ant = NULL;
    while (rec){
        if (rec -> cliente ->RUT == RUT){
            if (ant){
                ant -> sig = rec -> sig;
            }
            else{
                (*head) = (*head) -> sig;
            }
            return 1;
        }
        ant = rec;
        rec = rec -> sig;
    }
    return 0;
}

void mostrarClientes(struct NodoCliente *head){
    struct NodoCliente *rec = head;
    char desicion[2];
    while (rec){
        printf("Nombre Cliente: %s\n", rec -> cliente -> nombre);
        printf("Rut: %d\n", rec -> cliente -> RUT);
        printf("E-mail: %s\n", rec -> cliente -> email);
        printf("Direccion: %s\n", rec -> cliente -> direccion);
        printf("Comuna: %s\n", rec -> cliente -> comuna);
        printf("Desea ver las compras que ha realizado el cliente? Introduzca SI o NO\n");
        while (true){
            scanf(" %[^\n]", desicion);
            AMayusculas(desicion);
            if (strcmp(desicion, "SI") == 0){
                mostrarCompras(rec -> cliente -> headCompras);
                printf("Total gastado por el cliente: %d\n", rec -> cliente -> totalGastado);
                break;
            }
            else if (strcmp(desicion, "NO") == 0) break;
            printf("Por favor, introduzca una opcion valida");
        }
        printf("\n");
        rec = rec -> sig;
    }
}


//Implementar a futuro al sistema Funcion buscarNodoCliente
int buscarNodoCliente(struct NodoCliente *head, int rutBuscado)
{
    struct NodoCliente *rec = head;
    while(rec){
        if(rec -> cliente -> RUT == rutBuscado)
        {
            return 1;
        }
        rec = rec->sig;
    }

    return 0;
}

int contarGastosCliente(struct NodoCompra *head){
    int contador = 0;
    struct NodoCompra *rec = head;
    while (rec){
        contador += rec -> datos -> detalles -> costeTotal;
        contador += contarGastosRepuestos(rec -> datos ->headRepuestos);
        rec = rec -> sig;
    }
    return contador;
}

//TODO: Revisar utilidad funcion verOpcionesClientes con las funciones que llama



#endif //DERCO_FUNCIONESCLIENTESLISTASIMPLE_H
