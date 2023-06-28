//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Structs.h"
#include "FuncionesSucursalListaCircular.h"
#include "FuncionesProductosArbol.h"
#include "FuncionesRegionesArreglo.h"
#include "FuncionesDerco.h"
#include "FuncionAMayusculas.h"
#include "Helpers.h"

#ifndef DERCO_INTERFACESYMENUS_H
#define DERCO_INTERFACESYMENUS_H


struct Compra *busquedaCompraIngresoComprobante(struct NodoCompra *head,int comprobante){
    struct Compra *buscado=NULL;
    buscado = buscarCompra(head, comprobante);
    if (buscado) {
        printf("Se encontro la compra!\n");
        return buscado;
    } else {
        printf("La compra no se encuentra en la lista\n");
        return NULL;
    }
}

void revisarCompras(struct Cliente** clienteRev) {
    int opcion;
    int comprobante;
    struct Compra *buscado;
    if ((*clienteRev)->headCompras == NULL) {
        printf("Cliente no tiene compras\n");
        return;
    }
    printf("Escriba la opcion a revisar.\n");
    printf("Opcion 1: Mostrar compras.\n");
    printf("Opcion 2: Buscar una compra.\n");
    printf("Opcion 3: Eliminar una compra.\n");
    printf("Opcion 4: Modificar una compra.\n");
    while (true) {
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;

            case 1:
                mostrarCompras((*clienteRev)->headCompras);
                break;
            case 2:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = busquedaCompraIngresoComprobante((*clienteRev)->headCompras, comprobante);
                break;
            case 3:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = busquedaCompraIngresoComprobante((*clienteRev)->headCompras, comprobante);
                if (buscado) {
                    eliminarCompra(&(*clienteRev)->headCompras, comprobante);
                    printf("Se elimino la compra\n");
                }
                else {
                    printf("No se pudo eliminar la compra ya que no existe\n");
                }
                break;
            case 4:
                printf("Escriba el numero comprobante de la compra\n");
                scanf("%d", &comprobante);
                buscado = busquedaCompraIngresoComprobante((*clienteRev)->headCompras, comprobante);
                if (buscado) {
                    modificarCompra(&buscado);
                } else {
                    printf("La compra no se encuentra en la lista\n");
                }
            default:
                printf("Opcion no esta disponible, intentelo de nuevo\n");
                break;
        }
    }
}

struct Cliente *busquedaClienteIngresoRut(struct NodoCliente *head){
    int rutBusc;
    struct Cliente *buscado;
    scanf("%d", &rutBusc);
    buscado = buscarCliente(head, rutBusc);
    if (buscado) {
        printf("Se encontro el cliente!\n");
        return buscado;
    } else {
        printf("No se encontro el cliente\n");
        return NULL;
    }
}

//Implementar a futuro Funcion verOpcionesClientes ya que nunca es llamada

void verOpcionesClientes(struct NodoCliente **head, int *totalClientes){
    int i;
    int opcion;
    int rutBusc;
    struct Cliente *buscado;
    if (*head == NULL){
        for (i = 0; i < (*totalClientes); i++){
            agregarCliente(head, crearNodoCliente(crearCliente()));
        }
    }
    else {

        printf("Escriba el numero de la opcion que desea usar.\n");
        printf("Opcion 1: Mostrar Clientes\n");
        printf("Opcion 2: Buscar un Cliente\n");
        printf("Opcion 3: Agregar un Cliente\n");
        printf("Opcion 4: Eliminar un Cliente\n");
        printf("Opcion 5: Modificar un Cliente\n");
        printf("Opcion 6: Revisar las compras de un cliente\n");
        printf("Ingrese un 0 para terminar la ejecucion\n");
        while (true) {
            scanf("%d", &opcion);
            switch (opcion) {
                case 0:
                    return;
                case 1:
                    mostrarClientes(*head);
                    break;
                case 2:
                    printf("Ingrese el rut del cliente que quiere buscar\n");
                    buscado= busquedaClienteIngresoRut(*head);
                    break;
                case 3:
                    (*totalClientes) += agregarCliente(head, crearNodoCliente(crearCliente()));
                    break;
                case 4:
                    printf("Escriba el rut del cliente que desea eliminar\n");
                    scanf("%d", &rutBusc);
                    (*totalClientes) -= eliminarCliente(head, rutBusc);
                    break;
                case 5:
                    printf("Escriba el rut del cliente que quiere modificar\n");
                    buscado= busquedaClienteIngresoRut(*head);
                    if(buscado){
                        modificarMailCliente(&buscado);
                    }
                    break;
                case 6:
                    printf("Ingrese el rut del cliente con las compras que desea ver\n");
                    buscado= busquedaClienteIngresoRut(*head);
                    if(buscado){
                        revisarCompras(&buscado);
                    }
                    break;
                default:
                    printf("Opcion no esta disponible, intentelo de nuevo\n");
                    break;
            }
        }
    }
}


void verCatalogo(struct NodoProducto **raiz, int *totalProductos) {
    char desicion[2];
    if (*raiz == NULL) {
        printf("Al parecer, el catalogo de productos esta vacio, desea aÃ±adir un producto? SI/NO\n");
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        while (true) {
            if (strcmp(desicion, "SI") == 0) {
                if(insertarProducto(raiz, rellenarDatosProducto()) == 1)
                {
                    (*totalProductos) ++;
                    printf("Producto fue agregado de manera satisfactoria a nuestro catalogo");
                }
                else printf("Error al agregar el producto");
                break;
            }
            if (strcmp(desicion, "NO") == 0) break;
            printf("La opcion que ingreso no es valida, por favor intentelo nuevamente.\n");
        }
    }
    else
        trabajarcatalogo(raiz,totalProductos);
}



void modificarRegion(struct Region *region){
    int opcion;
    int RUTBuscado;
    struct Cliente *buscado;
    printf("Que datos desea modificar?\n");
    printf("Opcion 1: Modificar la sucursal.\n");
    printf("Opcion 2: Modificar los clientes.\n");
    printf("Ingresar un 0: Salir.\n");
    while (1){
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;
            case 1:
                modificarDatosSucursal(&(region -> headSucursales));
                break;
            case 2:
                printf("Introduzca el RUT del cliente que desea modificar:");
                scanf("%d", &RUTBuscado);
                buscado = buscarCliente(region ->headClientes, RUTBuscado);
                if (buscado) {
                    printf("Cliente se encuentra en la region! \n");
                    modificarMailCliente(&buscado);
                }
                else{
                    printf("Cliente no se encuentra en la region\n");
                }
            default:
                printf("Lo sentimos, la opcion que usted ingreso no esta disponible, intentelo de nuevo\n");
                break;
        }
    }
}



void elegirOpcionSucursal(struct Region **region, struct NodoProducto *raiz){
    int opcion;
    char comuna[100], direccion[100];
    struct Sucursal *buscado;
    struct Producto *autoMasVendido;
    printf("Elija una opcion\n");
    printf("Opcion 1: Buscar una sucursal\n");
    printf("Opcion 2: Agregar una sucursal\n");
    printf("Opcion 3: Eliminar una sucursal\n");
    printf("Opcion 4: Mostrar Recalls\n");
    printf("Opcion 5: Comprar un automovil\n");
    printf("Opcion 6: Comprar un repuesto.\n");
    printf("Opcion 7: Comprar un accesorio.\n");
    printf("Opcion 8: Agregar un Recall.\n");
    printf("Opcion 9: Auto mas vendido.\n");
    printf("Ingrese un 0 para salir\n");
    while (true){
        scanf("%d", &opcion);
        switch (opcion) {
            case 0: return;
            case 1:
                printf("Ingrese la comuna y direccion de la sucursal que esta buscando:");
                scanf(" %[^\n]", comuna);
                scanf(" %[^\n]",direccion);
                buscado = buscarSucursal(((*region) -> headSucursales), comuna, direccion);
                if (buscado != NULL){
                    printf("La sucursal si se encuentra en nuestra base de datos\n");
                }
                else{
                    printf("La sucursal no se encuentra en nuestra base de datos\n");
                }
                break;

            case 2:
                (*region) -> cantSucursales += agregarSucursal(&(*region) -> headSucursales, crearNodoSucursal(rellenarDatosSucursal(raiz)));
                break;

            case 3:
                printf("Ingrese la comuna y direccion de la sucursal que desea eliminar:");
                scanf(" %[^\n]", comuna);
                scanf(" %[^\n]",direccion);
                (*region) -> cantSucursales -= eliminarSucursal(&(*region) ->headSucursales, comuna, direccion);
                break;

            case 4:
                printf("\"Ingrese la comuna y direccion de la sucursal que desea ver los recalls:\"");
                scanf(" %[^\n]", comuna);
                scanf(" %[^\n]",direccion);
                buscado = buscarSucursal((*region) -> headSucursales, comuna, direccion);
                if (buscado) {
                    if (buscado -> headRecalls)
                        mostrarRecalls((*region)->headSucursales ->sucursal ->headRecalls);
                    else{
                        printf("Lo sentimos, esta sucursal no tiene recalls.\n");
                    }
                }

                else{
                    printf("No se encontro la sucursal que usted deseaba");
                }
                break;

            case 5:
                comprarAuto(&((*region)->headSucursales),&((*region)->headClientes));
                break;

            case 6:
                comprarRepuesto(&((*region)->headSucursales),&((*region)->headClientes));
                break;

            case 7:
                comprarAccesorio(&((*region)->headSucursales),&((*region)->headClientes));
                break;

            case 8:
                agregarRecallOpciones(&((*region)->headSucursales),&((*region)->headClientes));
                break;

            case 9:
                autoMasVendido = autoMasVendidoEnSucursal((*region)->headSucursales->sucursal->headRecalls);
                if(autoMasVendido == NULL)
                    printf("No se han encontrado un auto vendido en esta sucursal");
                else printf("Auto mas vendido en sucursal: %s", autoMasVendido->modelo);
                break;

            default:
                printf("Opcion que eligio no es valida, intentelo nuevamente\n");
                break;
        }
    }
}


void menuModificarRegion(struct Region **regiones, int maxRegiones)
{
    int numRegion;
    struct Region* buscado;
    char desicion[2];

    printf("Ingrese el numero de la region que busca:");
    scanf("%d", &numRegion);
    buscado = buscarRegion(regiones, maxRegiones, numRegion);
    if (buscado) {
        printf("Se encontro region, desea modificarla? SI/NO");
        scanf(" %[^\n]", desicion);
        AMayusculas(desicion);
        while (true) {
            if (strcmp(desicion, "SI") == 0) {
                modificarRegion(buscado);
            }
            if (strcmp(desicion, "NO") == 0) {
                break;
            }
            printf("Opcion que ingreso no esta disponible, intentelo nuevamente\n");
        }
    } else {
        printf("La region que pedia no se encontro en el arreglo\n");
    }
}
void menuActualizarRegion(struct Region **regiones,int maxRegiones, int *totalActualRegiones)
{
    struct Region *buscado;
    if ((*totalActualRegiones) < maxRegiones) {
        buscado = crearRegion();
        (*totalActualRegiones) += agregarRegion(regiones, maxRegiones, buscado);
    } else {
        printf("Lo sentimos, no tenemos espacio para agregar la region que desea\n");
    }
}
void menuEliminarRegion(struct Region **regiones, int maxRegiones,int *totalActualRegiones)
{
    int numRegion;
    while(1) {
        printf("Por favor, escriba el numero de la region que desea eliminar(asegurese que sea valido):");
        scanf("%d", &numRegion);
        if(numRegion <(*totalActualRegiones) || regiones[numRegion]!=NULL)
            break;
    }
    (*totalActualRegiones) -= eliminarRegion(regiones, maxRegiones, numRegion);
}

void menuMostrarRegionesMayorGanancia(struct Region **regiones, int maxRegiones)
{
    struct Region *buscado;
    int mayor;
    buscado = calcularRegionMayorGanancia(regiones, maxRegiones,&mayor);
    printf("La region que presento la mayor ganancia es la numero %d\n con una ganancia de %d", buscado->numRegion, mayor);
}
void menuMostrarRegionesMenorGanancia(struct Region **regiones, int maxRegiones)
{
    struct Region *buscado;
    int menor;
    buscado = calcularRegionMenorGanancia(regiones, maxRegiones, &menor);
    printf("La region con menor ganancias es la numero %d con una ganancia  de %d\n",buscado->numRegion,menor);
}

void trabajarRegiones(struct Region **regiones, int maxRegiones, int *totalActualRegiones)
{
    int opcion;

    printf("Usted ha deseado trabajar con las regiones, ahora seleccione una opcion:\n");
    printf("Opcion 1: Mostrar Regiones\n");
    printf("Opcion 2: Buscar Region\n");
    printf("Opcion 3: Agregar Region\n");
    printf("Opcion 4: Eliminar una Region\n");
    printf("Opcion 5: Mostrar la region con menos ganancias\n");
    printf("Opcion 6: Mostrar la region con mas ganancias\n");

    printf("Ingrese un 0 para salir.\n");
    while (true) {
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                return;
            case 1:
                mostrarRegiones(regiones, maxRegiones);
                break;
            case 2:
                menuModificarRegion(regiones, maxRegiones);
                break;
            case 3:
                menuActualizarRegion(regiones,maxRegiones,totalActualRegiones);
                break;
            case 4:
                menuEliminarRegion(regiones,maxRegiones,totalActualRegiones);
                break;
            case 5:
                menuMostrarRegionesMenorGanancia(regiones,maxRegiones);
                break;
            case 6:
                menuMostrarRegionesMayorGanancia(regiones,maxRegiones);
                break;
            default:
                printf("Opcion no disponible, intentelo nuevamente\n");
                break;
        }
    }
}

void verRegiones(struct Region **regiones, int *maxRegiones, int *totalActualRegiones) {
    char desicion[2];
    struct Region* buscado;
    if (regiones == NULL) {
        printf("Actualmente no hay regiones, desea agregar? SI/NO");
        while (true) {
            scanf(" %[^\n]", desicion);
            AMayusculas(desicion);
            if (strcmp(desicion, "SI") == 0) {
                printf("Ingrese el maximo de regiones:");
                scanf("%d", maxRegiones);
                (*totalActualRegiones) = 0;
                regiones = crearArrayRegiones((*maxRegiones));
                buscado = crearRegion();
                (*totalActualRegiones) += agregarRegion(regiones, *maxRegiones, buscado);
                break;
            }
            if(strcmp(desicion,"NO")==0)
                return;
            printf("Ingrese una opcion valida\n");
        }
    }
    else trabajarRegiones(regiones,*maxRegiones,totalActualRegiones);

}

void menuPrincipal(struct Derco **empresa){
    char desicion[2];
    int opcion;
    int numRegion;
    struct Region *buscado;
    while (true){
        if ((*empresa) == NULL){
            printf("Parece que la empresa no existe, desea crearla? SI/NO\n");
            while (true){
                scanf(" %[^\n]", desicion);
                AMayusculas(desicion);
                if (strcmp(desicion, "SI") == 0){
                    (*empresa) = crearEmpresa();
                    break;
                }
                if (strcmp(desicion, "NO") == 0) return;
                printf("La opcion que entrego no es valida, intentelo nuevamente\n");
            }
        }
        else{
            while (true){
                printf("\nPor favor seleccione una de las siguientes opciones:\n");
                printf("Opcion 1: Trabajar con el catalogo de productos.\n");
                printf("Opcion 2: Trabajar con las regiones.\n");
                printf("Opcion 3: Ver Sucursales en cada region\n");
                printf("Ingrese 0 si desea salir y finalizar.\n");
                scanf("%d",&opcion);
                switch (opcion){
                    case 0: return;

                    case 1:
                        verCatalogo(&((*empresa)->raizProductos), &((*empresa)->totalProductos));
                        break;

                    case 2:
                        if ((*empresa)->raizProductos==NULL){
                            printf("No existe un catalogo de productos actualmente por favor seleccione la opcion 1 antes de continuar.\n");
                        }
                        else{
                            verRegiones(((*empresa)->region), &((*empresa)->maxRegionesOperacion), &((*empresa)->regionesOperandoActualmente));
                        }
                        break;
                    case 3:
                        if ((*empresa) -> raizProductos == NULL){
                            printf("No hay catalago disponible para rellenar las sucursales, por favor seleccione la opcion 1 antes de continuar.\n");
                        }
                        else {
                            if ((*empresa) -> region == NULL){
                                printf("No hay regiones disponibles donde revisar las sucursales, por favor seleccione la opcion 2 antes de continuar.\n");
                            }
                            else {
                                printf("Ingrese el numero de la region con la que desea trabajar\n");
                                scanf("%d", &numRegion);
                                buscado = buscarRegion((*empresa) -> region, (*empresa) -> maxRegionesOperacion, numRegion);
                                if (buscado) {
                                    elegirOpcionSucursal(&buscado, (*empresa)->raizProductos);
                                }
                                else{
                                    printf("La region con la que desea trabajar no se encuentra en nuestra base de datos.\n");
                                }
                            }
                        }
                        break;
                    default:
                        printf("Opcion no valida, intentelo nuevamente.\n");
                        break;
                }
            }
        }
    }
}




#endif //DERCO_INTERFACESYMENUS_H
