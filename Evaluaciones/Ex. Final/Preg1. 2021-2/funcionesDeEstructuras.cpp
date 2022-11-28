/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   funcionesDeEstructuras.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:32 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include <cstring>
#include <cstdlib>
#include "Productos.h"
#include "funcionesCadenas.h"
#include "funcionesDeEstructuras.h"
#include "Pedidos.h"
#define MAX_LINEA 90 //máxima cantidad de la linea
#define MAX_PROD 20 //máxima cantidad de productos
#define NO_ENCONTRADO -1

void llenarProductos(const char * nombArch, struct StockProd *productos,
    int & numProd){
    ifstream archDatos(nombArch, ios::in);
    if(not archDatos.is_open()){
        cout<<"ERROR: al abrir el archivo"<<endl;
        exit(1);
    }
    
    char * codigo, * auxNombre; //código y nombre
    char c; //para descartar la coma
    int auxStock; //stock
    double auxPrecio; //precio
    numProd = 0;
    while(true){
        codigo = leeCadenaExacta(archDatos);
        if (archDatos.eof()) break;
        productos[numProd].codigo = codigo;
        auxNombre = leeCadenaExacta(archDatos);
        productos[numProd].descripcion = auxNombre;
        archDatos>>auxStock>>c>>auxPrecio;
        archDatos.get(); //se descarta el cambio de línea
        productos[numProd].stock = auxStock;
        productos[numProd].precio = auxPrecio;
        numProd++;
    }
}

void probarllenarProductos(struct StockProd *productos, int numProd,
    const char *nombArch){
    ofstream archReporte(nombArch, ios::out);
    int tam;
    archReporte<<fixed;
    archReporte.precision(2);
    for(int i=0; i<numProd; i++){
        archReporte<<left<<setw(10)<<productos[i].codigo;
        tam = strlen(productos[i].descripcion);
        archReporte<<productos[i].descripcion;
        archReporte<<right<<setw(50-tam)<<" "<<setw(2)<<productos[i].stock;
        archReporte<<setw(15)<<productos[i].precio<<endl;
    }
}

void llenarPedidos(const char *nombArch, struct Pedidos* pedidos,
    int & numPed){
    char c; //para descartar caracteres no necesarios
    int dd, mm, aaaa, hor, min, seg, num, dni;
    ifstream archDatos(nombArch, ios::in);
    numPed = 0;
    while(true){
        archDatos>>dd;
        if (archDatos.eof()) break;
        archDatos>>c>>mm>>c>>aaaa;  
        archDatos>>hor>>c>>min>>c>>seg;
        archDatos>>num>>dni;
        pedidos[numPed].numero = num;
        pedidos[numPed].fecha = 10000*aaaa + 100*mm + dd; //aaaammdd
        pedidos[numPed].hora = 3600*hor + 60*min + seg; // en segundos
        pedidos[numPed].cliente = dni;
        pedidos[numPed].productosEntregados = new struct Entregado[MAX_PROD];
        pedidos[numPed].productosNoEntregados = new struct NoEntregado[MAX_PROD];
        pedidos[numPed].cantProdEnt=0;
        pedidos[numPed].cantProdNoEnt=0;
        numPed++;
    }
}

void probarPedidos(struct Pedidos* pedidos,int numPed,const char *nombArch){
    int dd, mm, aaaa, hor, min, seg;
    ofstream archReporte(nombArch, ios::out);
    for(int i=0; i<numPed; i++){
        fechaToDMA(pedidos[i].fecha, dd, mm, aaaa);
        segundosToHMS(pedidos[i].hora, hor, min, seg);
        archReporte<<setw(5)<<" "<<setfill('0')<<setw(2)<<dd<<"/"
        <<setw(2)<<mm<<"/"<<setw(4)<<aaaa<<setfill(' ');
        archReporte<<setw(10)<<" "<<setfill('0')<<setw(2)<<hor<<":"
        <<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
        archReporte<<setw(20)<<pedidos[i].numero;
        archReporte<<setw(20)<<pedidos[i].cliente<<endl;
    }
}

void fechaToDMA(int fecha, int & dd, int & mm, int & aaaa){
    aaaa = fecha/10000;
    fecha %= 10000;
    mm = fecha/100;
    dd = fecha%100;
 }

void segundosToHMS(int segundos, int & hor, int & min, int & seg){
    hor = segundos/3600;
    segundos %= 3600;
    min = segundos/60;
    seg = segundos%60;
}

void completarPedidos(const char *nombArch, struct Pedidos* pedidos,int numPed,
    struct StockProd *productos, int numProd){

    ifstream arch(nombArch, ios::in);
    int numPedido, posProd, posPed;
    int cantNoAsig; //cantidad del producto no asignada
    int cant; //cantidad del producto asignada
    char codigoProducto[10];
    while(1){
        arch>>numPedido;
        if (arch.eof()) break;
        arch>>codigoProducto>>cant;
        posPed = buscaPedido(numPedido,pedidos, numPed);
        if(posPed !=-1){
            posProd = buscaProducto(codigoProducto,productos,numProd);
            if(posProd != -1){
                if(productos[posProd].stock > 0){ //si tiene stock
                    if(productos[posProd].stock >= cant){//stock >= cantidad
                        productos[posProd].stock -= cant;//actualizo stock
                        cantNoAsig = 0; //todo se asignó, cantNoAsig es cero
                    }
                    else{ //Supera la cantidad
                        cantNoAsig = cant - productos[posProd].stock;//falta
                        cant = productos[posProd].stock; //todo el stock
                        productos[posProd].stock = 0; //actualizo stock
                    }
                }
                else { //no tiene nada de stock
                    cantNoAsig = cant; //todo pasa a no asignado
                    cant = 0; //cantidad de entregados es cero
                }
                if(cant > 0){ //productos entregados
                    asignarEntrega(pedidos[posPed].productosEntregados,
                    pedidos[posPed].cantProdEnt,
                    productos[posProd].descripcion,
                    productos[posProd].precio,
                    codigoProducto,cant);
                    pedidos[posPed].cantProdEnt++;
                }
                if(cantNoAsig > 0){//productos no entregados
                    asignarNoEntrega(pedidos[posPed].productosNoEntregados,
                    pedidos[posPed].cantProdNoEnt,
                    productos[posProd].descripcion,
                    codigoProducto,cantNoAsig);
                    pedidos[posPed].cantProdNoEnt++;
                }
            }
        }
    }
}
void asignarEntrega(struct Entregado *prodEnt,int cantPE, char *desc,
    double precio, char*codigo,int cant){
    int tam;
    tam = strlen(codigo);
    prodEnt[cantPE].codigo = new char[tam+1];
    strcpy(prodEnt[cantPE].codigo,codigo);
    tam = strlen(desc);
    prodEnt[cantPE].descripcion = new char[tam+1];
    strcpy(prodEnt[cantPE].descripcion,desc);
    prodEnt[cantPE].cantEntregada = cant;
    prodEnt[cantPE].precioUnitario = precio;
    prodEnt[cantPE].subtotal = precio*cant;
}

void asignarNoEntrega(struct NoEntregado *prodNoEnt, int cantPNoE,
    char *desc,char*codigo,int cantNoAsig){
    int tam;
    tam = strlen(codigo);
    prodNoEnt[cantPNoE].codigo = new char[tam+1];
    strcpy(prodNoEnt[cantPNoE].codigo, codigo);
    tam = strlen(desc);
    prodNoEnt[cantPNoE].descripcion = new char[tam+1];
    strcpy(prodNoEnt[cantPNoE].descripcion,desc);
    prodNoEnt[cantPNoE].cantNoEntregada = cantNoAsig;
}

int buscaProducto(char *codigo,struct StockProd *productos,int numProd){
    for(int i=0; i<numProd; i++)
        if(strcmp(codigo,productos[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

int buscaPedido(int num,struct Pedidos *pedidos, int numPed){
    for(int i=0; i<numPed; i++)
    if(num == pedidos[i].numero) return i;
    return NO_ENCONTRADO;
}

void mostrarEncabezado(ofstream & archReporte){
    linea(archReporte, '=', MAX_LINEA);
    archReporte<<setw(60)<<"TIENDA VIRTUAL LA MAGNIFICA"<<endl;
    archReporte<<setw(56)<<"ATENCION DE PEDIDOS"<<endl;
    linea(archReporte, '=', MAX_LINEA);
}

void linea(ofstream & archReporte, const char car, int max){
    for(int i=0; i<max; i++){
        archReporte.put(car);
    }
    archReporte<<endl;
}

void reporteDePedidosFinal(struct Pedidos* pedidos,int numPed,
    const char *nombArch){
    ofstream archReporte(nombArch, ios::out);
    int dd,mm,aaaa, hor,min,seg;

    mostrarEncabezado(archReporte);

    for(int i=0; i<numPed; i++){
        fechaToDMA(pedidos[i].fecha, dd, mm, aaaa);
        segundosToHMS(pedidos[i].hora, hor, min, seg);
        archReporte<<setw(10)<<"Pedido No. "<<pedidos[i].numero;
        archReporte<<setw(20)<<"Fecha: "<<dd<<"/"<<mm<<"/"<<aaaa;
        archReporte<<setw(20)<<"Hora: "<<hor<<":"<<min<<":"<<seg<<endl;
        archReporte<<"Cliente: "<<endl<<"DNI: "<<setw(4)<<pedidos[i].cliente;
        archReporte<<endl<<endl;
        imprimirProdEnt(archReporte, pedidos[i].productosEntregados,
        pedidos[i].cantProdEnt);
        imprimirProdNoEnt(archReporte, pedidos[i].productosNoEntregados,
        pedidos[i].cantProdNoEnt);
        linea(archReporte,'=',MAX_LINEA);
    }
}

void imprimirProdEnt(ofstream & arch, struct Entregado *prodEnt, int cant){
    arch<<"Productos Entregados: "<<endl;
    arch<<"Código";
    arch<<setw(15)<<"Descripcion";
    arch<<setw(40)<<"Cantidad";
    arch<<setw(12)<<"Precio";
    arch<<setw(15)<<"Sub Total"<<endl;
    arch<<fixed;
    arch.precision(2);
    int tam;
    for(int i=0; i<cant; i++){
        arch<<left<<setw(10)<<prodEnt[i].codigo;
        tam = strlen(prodEnt[i].descripcion);
        arch<<prodEnt[i].descripcion;
        arch<<right<<setw(45-tam)<<" "<<setw(2)<<prodEnt[i].cantEntregada;
        arch<<setw(15)<<prodEnt[i].precioUnitario;
        arch<<setw(15)<<prodEnt[i].subtotal<<endl;
    }
    arch<<endl;
}

void imprimirProdNoEnt(ofstream & arch, struct NoEntregado *prodNoEnt,int cant){
    arch<<"Productos No Entregados: "<<endl;
    arch<<"Código";
    arch<<setw(15)<<"Descripcion";
    arch<<setw(40)<<"Cantidad"<<endl;
    int tam;
    for(int i=0; i<cant; i++){
        arch<<left<<setw(10)<<prodNoEnt[i].codigo;
        tam = strlen(prodNoEnt[i].descripcion);
        arch<<prodNoEnt[i].descripcion;
        arch<<right<<setw(45-tam)<<" "<<setw(2)
        <<prodNoEnt[i].cantNoEntregada<<endl;
    }
    arch<<endl;
}

