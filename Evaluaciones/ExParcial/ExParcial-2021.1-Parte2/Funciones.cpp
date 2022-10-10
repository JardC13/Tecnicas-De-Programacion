/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   Funciones.cpp
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
#define MAX_CAR_LIN 90
#define NO_ENCONTRADO -1

void cargarTodosProductos(int * arrCodProducto, double * arrPreProducto,
    int & cantProductos){
    int codigo, i = 0;
    double precio;
    ifstream archListaPrecios("ListaDePrecios.txt", ios::in);
    if (!archListaPrecios.is_open()){
        cout<<"No se puede abrir el archivo de Lista de precios";
        exit(1);
    }
    while(archListaPrecios.get()!='\n');
    while(true){
        archListaPrecios>>codigo; //leo el código
        if(archListaPrecios.eof()) break; //pregunto por el fin de archivo
        while(archListaPrecios.get()!=']'); // salto el nombre del produto
        arrCodProducto[i] = codigo; //guardo en el arreglo elcodigo
        archListaPrecios>>precio; //leo el precio
        arrPreProducto[i] = precio; //guardo en el arreglo el precio
        i++;
    }
    cantProductos = i;
}
void cargarProductosAlmacenados(int * arrCodProducto, double * arrPreProducto,
    int cantProductos, double * arrCantProdAlm, double * arrSubTotProd){

    int codigo, idProd;
    double cantidad;

    ifstream archProdAlmace("productosAlmacenados.txt", ios::in);
    if (!archProdAlmace.is_open()){
        cout<<"No se puede abrir el archivo de productos almacenados";
    exit(1);
    }

    while(true){
        archProdAlmace>>codigo;
        if(archProdAlmace.eof()) break;
        archProdAlmace>>cantidad;
 //Buscar id en la lista de productos
        idProd = buscarIdProducto(codigo, arrCodProducto, cantProductos);
        if (idProd>0){
            arrCantProdAlm[idProd] = cantidad; //guardo la cantidad
            arrSubTotProd[idProd] = arrCantProdAlm[idProd] * arrPreProducto[idProd];
        }
        else
            cout<<"No se encontró el producto"<<endl;
    }
}
int buscarIdProducto(int codigo, int * arrCodProducto, int cantProductos){
    for (int i = 0; i < cantProductos; i++){
        if (codigo == arrCodProducto[i]) return i;
    }
    return NO_ENCONTRADO; //retorna -1
}
void ordenarSubTotalProducto(int * arrCodProducto, double * arrPreProducto,
 double * arrCantProdAlm, double * arrSubTotalProd, int cantProductos){

    for (int i = 0; i < cantProductos-1; i++)
        for (int j = i+1; j < cantProductos; j++){
            if (arrSubTotalProd[i] < arrSubTotalProd[j]){ //de mayor a menor
                cambiarInt(arrCodProducto, i, j);
                cambiarDouble(arrPreProducto, i, j);
                cambiarDouble(arrCantProdAlm, i, j);
                cambiarDouble(arrSubTotalProd, i, j);
            }
        }
}
void cambiarInt(int *arreglo, int i, int j){
    int aux = arreglo[i];
    arreglo[i] = arreglo[j];
    arreglo[j] = aux;
}
void cambiarDouble(double *arreglo, int i, int j){
    double aux = arreglo[i];
    arreglo[i] = arreglo[j];
    arreglo[j] = aux;
}
void generaPrimeraParteReporte(int * arrCodProducto, double * arrPreProducto,
    double * arrCantProdAlm, double * arrSubTotalProd, int cantProductos,
    ofstream & archRep){
    
    int num = 1;
    double costoTotalProdPerdidos = 0.0;

    mostrarCabeceraParte1(archRep);
    archRep.precision(2);
    archRep<<fixed;
    for(int i=0; i<cantProductos; i++){
        if (arrCantProdAlm[i] > 0){ //solo muestro los mayores a cero
            archRep<<setfill(' ')<<setw(3)<<num<<")"<<setfill(' ')<<setw(10)<<arrCodProducto[i]
                <<setw(20)<<arrCantProdAlm[i]<<setw(20)<<arrPreProducto[i]<<setw(30)<<arrSubTotalProd[i]<<endl;
            costoTotalProdPerdidos += arrSubTotalProd[i];
            num++;
        }
    }
    mostrarLinea(archRep, '-', MAX_CAR_LIN);
    archRep<<"Costo total de productos perdidos: "<<costoTotalProdPerdidos<<endl;
    mostrarLinea(archRep, '=', MAX_CAR_LIN);
}
void mostrarCabeceraParte1(ofstream & archRep){
    mostrarLinea(archRep, '=', MAX_CAR_LIN);
    archRep<<"PRODUCTOS PERDIDOS"<<endl;
    mostrarLinea(archRep, '-', MAX_CAR_LIN);
    archRep<<setw(15)<<"Producto"<<setw(20)<<"Cantidad"<<setw(30)
    <<"Precio unitario(S/.)"<<setw(25)<<"Sub-total(S/.)"<<endl;
}
void mostrarLinea(ofstream & archRep, char car, int max){
    for (int i = 0; i < max; i++){
        archRep.put(car);
    }
    archRep<<endl;
}
//Todos los productos se malograron por eso se leen todos los platos a preparar
void cargarPlatosPreparar(int * arrCodPlato, int * arrCantPlato, int & cantPlatos){
 int codigo, i = 0, cantidad;
 ifstream archPlatosAPreparar("platosApreparar.txt", ios::in);
 if (!archPlatosAPreparar.is_open()){
 cout<<"No se puede abrir el archivo de Platos a preparar";
 exit(1);
 }
 while(true){
 archPlatosAPreparar>>codigo; //leo el código
 if(archPlatosAPreparar.eof()) break; //pregunto por el fin de archivo
 archPlatosAPreparar>>cantidad; //leo el precio
 arrCodPlato[i] = codigo; //guardo en el arreglo elcodigo
 arrCantPlato[i] = cantidad; //guardo en el arreglo el precio
 i++;
 }
 cantPlatos = i;
}
//cargar todos los platos
void cargarPlatosPrecios(int * arrCodPlato, int * arrCantPlato, int cantPlatos,
    int * arrCodProducto, double * arrPreProducto, int cantProductos,
    double * arrPrecioPlato){

    int codPlato, idPlato, idProducto, codProd;
    double cantidad;

    ifstream archPlatos("Platos.txt", ios::in);
    if(!archPlatos.is_open()){
        cout<<"Error al abrir el archivo de platos"<<endl;
        exit(1);
    }

    while (true){
        archPlatos>>codPlato;
        if (archPlatos.eof()) break;
        //Busco el plato en los platos a preparar
        idPlato = buscarIdPlato(arrCodPlato, cantPlatos, codPlato);
        if (idPlato > 0){
 /*descartar nombre*/
            while(archPlatos.get() != ')');
 //leer dupla codigo y cantidad
            while(true){
                archPlatos>>codProd>>cantidad;
 //Busco el producto
                idProducto = buscarIdProducto(codProd, arrCodProducto,
                cantProductos);
                if (idProducto > 0)
                    arrPrecioPlato[idPlato]+=arrPreProducto[idProducto]*cantidad;
                else
                    arrPrecioPlato[idPlato] = 0; //condicion del problema
                if (archPlatos.get()=='\n') break;
            }
        }
        else{
            cout<<"El plato "<<codPlato <<" no se encuentra en platosapreparar.txt"<<endl;
 /*descartar la linea*/
            while(archPlatos.get()!='\n');
        }
    }
}

int buscarIdPlato(int * arrCodPlato, int cantPlatos, int codPlato){
    for(int i=0; i<cantPlatos; i++){
        if(arrCodPlato[i]==codPlato) return i;
    }
 return -1;
}
void actualizarSubTotalPlatos(int * arrCodPlato, int * arrCantidadPlato,
    int cantPlatos, double * arrPrecioPlato, double * arrSubTotalPlato){
    for (int i = 0; i < cantPlatos; i++)
         arrSubTotalPlato[i] = arrPrecioPlato[i] * arrCantidadPlato[i];
}
void ordenarSubTotalPlato(int * arrCodPlato, double * arrPrePlato,
    int * arrCantPlato, double * arrSubTotalPlato, int cantPlatos){
 //ordenar por doble criterio
    for (int i = 0; i < cantPlatos-1; i++)
        for (int j = i+1; j < cantPlatos; j++){
            if ( arrCantPlato[i] > arrCantPlato[j] || //de menor a mayor
                (arrCantPlato[i] == arrCantPlato[j] &&
                arrSubTotalPlato[i] < arrSubTotalPlato[j]) ){
                cambiarInt(arrCodPlato,i,j);
                cambiarInt(arrCantPlato,i,j);
                cambiarDouble(arrPrePlato,i,j);
                cambiarDouble(arrSubTotalPlato,i,j);
            }
        }
}

void generaSegundaParteReporte(int * arrCodPlato, int * arrCantPlato,
    double * arrPrecioPlato, double * arrSubTotalPlato, int cantPlatos,
    ofstream & archRep){

    int num = 1;
    double totalPedidosSinPreparar = 0.0;

    mostrarCabeceraParte2(archRep);
    for(int i = 0; i < cantPlatos; i++){
        archRep<<setfill(' ')<<setw(3)<<num<<")"<<setfill(' ')
        <<setw(10)<<arrCodPlato[i]
        <<setw(16)<<arrCantPlato[i]
        <<setw(24)<<arrPrecioPlato[i]
        <<setw(30)<<arrSubTotalPlato[i]<<endl;
        totalPedidosSinPreparar += arrSubTotalPlato[i];
        num++;
    }
    mostrarLinea(archRep, '-', MAX_CAR_LIN);
    archRep<<"Monto total de pedidos sin preparar: "<<totalPedidosSinPreparar<<endl;
    mostrarLinea(archRep, '=', MAX_CAR_LIN);
}
void mostrarCabeceraParte2(ofstream & archRep){
    mostrarLinea(archRep, '=', MAX_CAR_LIN);
    archRep<<"PLATOS QUE NO SE PODRAN PREPARAR"<<endl;
    mostrarLinea(archRep, '-', MAX_CAR_LIN);

    archRep<<setw(14)<<"Pedido"<<setw(19)<<"Cantidad"<<setw(30)
    <<"Precio Productos(S/.)"<<setw(25)<<"Sub-total(S/.)"<<endl;
}
