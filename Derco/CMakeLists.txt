cmake_minimum_required(VERSION 3.24)
project(Derco C)

set(CMAKE_C_STANDARD 99)

add_executable(Derco main.c FuncionesProductosArbol.h FuncionesAccesoriosLista.h FuncionesSucursalListaCircular.h FuncionesClientesListaSimple.h FuncionesCompraListaSimple.h FuncionesRecallsListaSimple.h FuncionesRepuestosListaSimple.h FuncionesParteArreglo.h Structs.h FuncionesaAccesoriosArreglo.h FuncionesProductosArreglo.h FuncionesRegionesArreglo.h FuncionesDerco.h InterfacesYMenus.h InterfacesExtras.h Helpers.h FuncionAMayusculas.h)
