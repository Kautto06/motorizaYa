//
// Created by gerar on 6/23/2023.
//

#ifndef DERCO_STRUCTS_H
#define DERCO_STRUCTS_H

struct Parte{
    char *nombre;
    int costo;
    int idParte;
    int numeroDeChasisAsociado;
};

struct Accesorio{
    char *nombre;
    int costo;
    int idAccesorio;
    int numeroDeChasisAsociado;
};

struct NodoAccesorio{
    struct Accesorio *accesorio;
    struct NodoAccesorio *sig;
};

struct Producto /*(automovil)*/{
    int numeroDeChasis;
    int yearFabricado;
    char *marca, *modelo;
    int totalPartes;
    struct Parte **partes;
    int totalAccesorios;
    struct NodoAccesorio *headAccesorios; //Todos los accesorios disponibles del automovil.
    int costeTotal; //Precio base + Precio de cada parte sin considerar accesorios.
};

struct NodoProducto{
    struct Producto *automovil; //Arbol Binario de Busqueda se ordena con el numero de Chasis de cada automovil.
    struct NodoProducto *izq, *der;
};

struct NodoParte{
    struct Parte *repuesto;
    struct NodoParte *sig;
};

struct Compra{
    int RutComprador;
    int numeroComprobante;
    struct Producto *detalles; //NodoAccesorio se deja NULL, este almacenara los accesorios que compres
    struct NodoParte *headRepuestos;
};

struct NodoCompra{
    struct Compra *datos; //darle memoria, necesita nueva memoria para que no se cambie lo pagado
    struct NodoCompra *sig;
};

struct Cliente{
    int RUT, numRegion; //numRegion se implementara despues
    char *nombre, *direccion, *comuna, *email;
    struct NodoCompra *headCompras;
    int totalGastado;
};

struct NodoCliente{
    struct Cliente *cliente;
    struct NodoCliente *sig;
};

struct Stock{
    int maxProductos; //Se cambia dependiendo de la cantidad real de espacios ocupados en el arreglo
    int totalProductos; //No se cambia
    struct Producto **autosEnVenta;

    int maxRepuestos;
    int totalRepuestos;
    struct Parte **repuestosEnVenta;

    int maxAccesorios; //Unidades totales que puedo almacenar
    int totalAccesorios; //Unidades almacenadas actualmente
    struct Accesorio **accesoriosDisponibles; //Accesorios en general que tiene la sucursal.
};

struct Sucursal{
    char *director, *comuna, *direccion;
    struct Stock *almacenamiento;
    struct NodoCompra *headRecalls;
};

struct NodoSucursal{
    struct Sucursal *sucursal;
    struct NodoSucursal *ant, *sig;
};

struct Region{
    int numRegion;
    int cantClientes;
    int cantSucursales;
    struct NodoCliente *headClientes;
    struct NodoSucursal *headSucursales; //Doblemente Circular
};

struct Derco{
    char *jefe;
    int ganancias;
    int maxRegionesOperacion; //Max de regiones para operar
    int regionesOperandoActualmente; //Numero de regiones donde Derco opera actualmente
    struct Region **region;
    int totalProductos;
    struct NodoProducto *raizProductos;
};

#endif //DERCO_STRUCTS_H


