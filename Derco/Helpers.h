//
// Created by gerar on 6/23/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Structs.h"
#include "FuncionesProductosArbol.h"
#include "FuncionesCompraListaSimple.h"
#include "FuncionesClientesListaSimple.h"
#include "FuncionesSucursalListaCircular.h"
#include "FuncionesRecallsListaSimple.h"

///// Catalogo productos

#ifndef DERCO_HELPERS_H
#define DERCO_HELPERS_H

void menuModificarUnProducto(struct NodoProducto **raiz)
{
    int numeroBuscado;
    printf("Escriba el numero de chasis del producto\n");
    scanf("%d", &numeroBuscado);
    modificarProducto(raiz, numeroBuscado);
}
void menuEliminarUnProducto(struct NodoProducto **raiz, int *totalProductos)
{
    int numeroBuscado;
    printf("Escriba el numero de chasis del producto que quiere eliminar\n");
    scanf("%d", &numeroBuscado);
    if (buscarProducto(*raiz, numeroBuscado) != NULL) {
        if (eliminarProductoArbol(raiz, numeroBuscado) == 1) {
            printf("El producto fue eliminado!\n");
            (*totalProductos)--;
        } else {
            printf("No se pudo eliminar el producto\n");
        }
    } else {
        printf("El producto no existe, entonces no se elimino");
    }
}
void menuCrearUnProducto(struct NodoProducto **raiz, int *totalProductos)
{
    struct Producto *nuevoProd;
    nuevoProd = rellenarDatosProducto();
    if (nuevoProd) {


        if(insertarProducto(raiz, nuevoProd) == 1) {
            (*totalProductos)++;
            printf("Producto fue agregado de manera satisfactoria a nuestro catalogo");
        }
        else printf("Error al agregar el producto");

    } else {
        printf("No se pudo agregar el producto ya que no fue creado propiamente\n");
    }
}
void mostrarBuscarUnProducto(struct NodoProducto *raiz)
{
    int numeroBuscado;
    printf("Ingrese el numero de chasis\n");
    scanf("%d", &numeroBuscado);
    if (buscarProducto(raiz, numeroBuscado) != NULL) {
        printf("Este producto si se encuentra en nuestro catalogo!\n");
    } else {
        printf("Este producto no se encuentra en nuestro catalogo\n");

    }
}
void trabajarcatalogo(struct NodoProducto **raiz, int *totalProductos)
{
    printf("Usted ha seleccionado trabajar con los productos de nuestro catalogo.\n");
    int opcionElegida;
    while (true)
    {
        printf("Por favor, seleccione la operacion que desea realizar sobre nuestro catalogo:\n");
        printf("Opcion 1: Mostrar los productos\n");
        printf("Opcion 2: Buscar un producto\n");
        printf("Opcion 3: Agregar un producto\n");
        printf("Opcion 4: Eliminar un producto\n");
        printf("Opcion 5: Modificar un producto\n");
        printf("Ingrese un 0 si quiere salir\n");
        scanf("%d", &opcionElegida);

        switch (opcionElegida) {
            case 0:
                return;
            case 1:
                mostrarProductos(*raiz);
                break;
            case 2:
                mostrarBuscarUnProducto(*raiz);
                break;
            case 3:
                menuCrearUnProducto(raiz,totalProductos);
                break;
            case 4:
                menuEliminarUnProducto(raiz,totalProductos);
                break;
            case 5:
                menuModificarUnProducto(raiz);
                break;
            default:
                printf("La opcion que usted ingreso no es valida, intentelo nuevamente.\n");
        }
    }
}

void comprarAuto(struct NodoSucursal **sucursales,struct NodoCliente **clientes){
    struct NodoSucursal* recSucursal=NULL;
    struct NodoCliente *recClientes=NULL;
    struct Producto *elegido=NULL;
    struct Cliente *comprador=NULL;
    int id,RUTBuscado;
    printf("Ingrese el numero de chasis del producto a comprar:");
    scanf("%d", &id);
    recSucursal = *sucursales;

    if (recSucursal == NULL){
        printf("Lo sentimos, no existen sucursales en esta region.\n");
    }

    else{

        do {
            elegido = buscarProductoArray(recSucursal ->sucursal->almacenamiento->autosEnVenta, recSucursal ->sucursal->almacenamiento->maxProductos, id);
            recSucursal = recSucursal -> sig;
        }while (recSucursal != *sucursales && elegido == NULL);

        if (elegido == NULL){
            printf("Producto no esta disponible en ninguna sucursal.\n");
        }

        else{
            printf("Ingrese el RUT del Cliente:");
            scanf("%d", &RUTBuscado);

            if (clientes) {
                recClientes = *clientes;

                while (recClientes && comprador == NULL) {
                    comprador = buscarCliente(recClientes, RUTBuscado);
                    recClientes = recClientes -> sig;
                }

                if (comprador != NULL) {
                    agregarCompra(&comprador -> headCompras, crearNodoCompra(crearCompra(&comprador, elegido)));
                    recSucursal ->sucursal ->almacenamiento ->totalProductos -= eliminarProductoArray(recSucursal ->sucursal ->almacenamiento -> autosEnVenta, recSucursal ->sucursal ->almacenamiento -> maxProductos, id);
                }
            }

            else{
                printf("Lo sentimos, la region no tiene clientes disponibles.\n");
            }
        }
    }
}

void comprarRepuesto(struct NodoSucursal **sucursales,struct NodoCliente **clientes){
    struct NodoSucursal*recSucursal=NULL;
    struct NodoCliente *recClientes=NULL;
    struct Parte *repuesto=NULL;
    struct Cliente *comprador=NULL;
    int id,RUTBuscado;
    printf("Ingrese el numero de chasis del producto a comprar:");
    scanf("%d", &id);
    recSucursal = *sucursales;

    if (recSucursal == NULL){
        printf("Lo sentimos, no existen sucursales en esta region.\n");
    }

    else{
        do {
            repuesto = buscarParteArray(recSucursal ->sucursal->almacenamiento->repuestosEnVenta, recSucursal ->sucursal->almacenamiento->maxRepuestos, id);
            recSucursal = recSucursal -> sig;
        }while (recSucursal != *sucursales && repuesto == NULL);

        if (repuesto == NULL){
            printf("Producto no esta disponible en ninguna sucursal.\n");
        }

        else{
            printf("Ingrese el RUT del Cliente:");
            scanf("%d", &RUTBuscado);

            if (clientes) {
                recClientes = *clientes;
                while (recClientes && comprador == NULL) {
                    comprador = buscarCliente(recClientes, RUTBuscado);
                    recClientes = recClientes -> sig;
                }

                if (comprador != NULL) {
                    agregarParteLista(&comprador -> headCompras ->datos->headRepuestos, repuesto);
                    comprador -> totalGastado += repuesto -> costo;
                    eliminarParteArray(recSucursal ->sucursal ->almacenamiento ->repuestosEnVenta, recSucursal ->sucursal ->almacenamiento ->maxRepuestos, id);
                }
            }

            else{
                printf("Lo sentimos, la region no tiene clientes disponibles.\n");
            }
        }
    }
}

void comprarAccesorio(struct NodoSucursal **sucursales,struct NodoCliente **clientes){
    struct NodoSucursal*recSucursal=NULL;
    struct NodoCliente *recClientes=NULL;
    struct Accesorio *accesorioComprado=NULL;
    struct Cliente *comprador=NULL;
    int id,RUTBuscado;
    printf("Ingrese el numero de chasis del producto a comprar:");
    scanf("%d", &id);
    recSucursal = *sucursales;
    if (recSucursal == NULL){
        printf("Lo sentimos, no existen sucursales en esta region.\n");
    }
    else{
        do {
            accesorioComprado = buscarAccesorioArray(recSucursal ->sucursal->almacenamiento->accesoriosDisponibles, recSucursal ->sucursal->almacenamiento->maxRepuestos, id);
            recSucursal = recSucursal -> sig;
        }while (recSucursal != *sucursales && accesorioComprado == NULL);
        if (accesorioComprado == NULL){
            printf("Producto no esta disponible en ninguna sucursal.\n");
        }
        else{
            printf("Ingrese el RUT del Cliente:");
            scanf("%d", &RUTBuscado);
            if (clientes) {
                recClientes = *clientes;
                while (recClientes && comprador == NULL) {
                    comprador = buscarCliente(recClientes, RUTBuscado);
                    recClientes = recClientes -> sig;
                }
                if (comprador != NULL) {
                    comprador -> headCompras ->datos-> detalles ->totalAccesorios+= agregarAccesorioLista(&comprador -> headCompras ->datos-> detalles ->headAccesorios, crearNodoAccesorio(accesorioComprado));
                    comprador -> totalGastado += accesorioComprado->costo;
                    recSucursal ->sucursal ->almacenamiento ->totalAccesorios-= eliminarAccesorioArray(recSucursal ->sucursal ->almacenamiento ->accesoriosDisponibles, recSucursal ->sucursal ->almacenamiento ->maxAccesorios, id);
                }
            }
            else{
                printf("Lo sentimos, la region no tiene clientes disponibles.\n");
            }
        }
    }
}

void agregarRecallOpciones(struct NodoSucursal **sucursales,struct NodoCliente **clientes){
    char comuna[100],direccion[100];
    struct Sucursal *buscado=NULL;
    int RUTBuscado,comprobante;
    struct NodoCliente *recClientes;
    struct Cliente *comprador=NULL;
    struct Compra *compraARecall=NULL;
    printf("Ingrese la comuna y la direccion de la sucursal que pidio el Recall:");
    scanf(" %[^\n]", comuna);
    scanf(" %[^\n]",direccion);
    buscado = buscarSucursal(*sucursales, comuna, direccion);
    if (buscado){
        printf("Ingrese el RUT del dueño del Recall");
        scanf("%d", &RUTBuscado);
        if (*clientes) {
            recClientes = *clientes;
            while (recClientes && comprador == NULL) {
                comprador = buscarCliente(recClientes, RUTBuscado);
                recClientes = recClientes -> sig;
            }
            if (comprador != NULL) {
                printf("Ingrese el numero de comprobante del auto a Recall:");
                scanf("%d", &comprobante);
                compraARecall = buscarCompra(comprador ->headCompras, comprobante);
                if (compraARecall){
                    agregarRecall(&(buscado) -> headRecalls, compraARecall);
                }
            }
            else{
                printf("Lo sentimos, el cliente del recall no existe");
            }
        }
        else{
            printf("Lo sentimos, la region no tiene clientes disponibles.\n");
        }
    }
    else{
        printf("Lo sentimos, no existe la sucursal que pidio el Recall");
    }
}


#endif //DERCO_HELPERS_H
