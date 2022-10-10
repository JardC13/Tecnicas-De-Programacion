/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   main.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 10 de octubre de 2022, 11:28 AM
 */

#include <iostream>
#include <iomanip>        
#include <fstream>
#include <cstdlib>
using namespace std;

#include "Funciones.h"
#define MAX_PRODUCTOS 300
#define MAX_PLATOS 100

int main(int argc, char** argv) {
   int arrCodProducto[MAX_PRODUCTOS];
   double arrCantProdAlm[MAX_PRODUCTOS]={};//inicializo las cantidades con cero
   double arrPreProducto[MAX_PRODUCTOS], arrSubTotalProd[MAX_PRODUCTOS],
   arrPrecioPlato[MAX_PLATOS], arrSubTotalPlato[MAX_PLATOS];
   int arrCodPlato[MAX_PLATOS], arrCantPlato[MAX_PLATOS], cantPlatos;
   int cantProductos = 0;

   ofstream archRep("Reporte.txt", ios::out);
   if(!archRep.is_open()){
   cout<<"Error al abrir el archivo de reporte"<<endl;
   exit(1);
   }
   //1ro cargar todos los productos de la lista de precios
   cargarTodosProductos(arrCodProducto, arrPreProducto, cantProductos);
   //Busco si el producto del almacén se malogró y obtengo la cantidad
   //y con ella calculo el subtotal
   cargarProductosAlmacenados(arrCodProducto, arrPreProducto, cantProductos,
   arrCantProdAlm, arrSubTotalProd);
   //ordenar en productos por subtotal de mayor a menor
   ordenarSubTotalProducto(arrCodProducto, arrPreProducto, arrCantProdAlm,
   arrSubTotalProd, cantProductos);
   //mostrar la primera parte del reporte
   generaPrimeraParteReporte(arrCodProducto, arrPreProducto, arrCantProdAlm,
   arrSubTotalProd, cantProductos, archRep);

   //cargar la relación de platos a preparar
   cargarPlatosPreparar(arrCodPlato, arrCantPlato, cantPlatos);
   //cargar los precios de los platos
   cargarPlatosPrecios(arrCodPlato, arrCantPlato, cantPlatos, arrCodProducto,
   arrPreProducto, cantProductos, arrPrecioPlato);
   //calcular los subtotales por plato
   actualizarSubTotalPlatos(arrCodPlato, arrCantPlato, cantPlatos,
   arrPrecioPlato, arrSubTotalPlato);
   //ordenar platos por cantidad de menor a mayor, y por sobtotal de mayor a menor
   ordenarSubTotalPlato(arrCodPlato, arrPrecioPlato, arrCantPlato,
   arrSubTotalPlato, cantPlatos);
   //mostrar la segunda parte del reporte
   generaSegundaParteReporte(arrCodPlato, arrCantPlato, arrPrecioPlato,
   arrSubTotalPlato, cantPlatos, archRep);
    return 0;
}

