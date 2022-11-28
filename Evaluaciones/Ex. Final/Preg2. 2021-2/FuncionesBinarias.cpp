/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   FuncionesBinarias.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 07:58 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "StockDeProductos.h"
#include "FuncionesBinarias.h"
#include "PedidosInternet.h"
#include "ProductoSolicitado.h"
#define NO_ENCONTRADO -1
#define MAX_LINEA 120

void crearStockBin(const char * nombreDatos, const char * nombreBin){
    ifstream archDatos(nombreDatos, ios::in);
    if(not archDatos.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreDatos<<endl;
        exit(1);
    }
    
    ofstream archBin(nombreBin, ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreBin<<endl;
        exit(1);
    }

    struct StockProducto stockProducto;
    while(true){
        leerStockProducto(archDatos, stockProducto);
        if(archDatos.eof()) break;
        archBin.write(reinterpret_cast<const char*>(&stockProducto),
        sizeof(struct StockProducto));
    }
}

void leerStockProducto(ifstream & archDatos, struct StockProducto & stockProducto){

    archDatos.getline(stockProducto.codigo,10,',');
    if(archDatos.eof()) return;
    archDatos.getline(stockProducto.descripcion,100,',');
    archDatos>>stockProducto.stock;
    archDatos.get(); //para la coma
    archDatos>>stockProducto.precio;
    archDatos.get();//salto el cambio de línea
}

void mostrarStockBin(const char * nombreBin){
    
    ifstream archBin(nombreBin, ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error en el archivo: No se pudo abrir: "<<nombreBin<<endl;
        exit(1);
    }

    ofstream archReporte("ReporteStock.txt", ios::out);
    if(not archReporte.is_open()){
        cout<<"Error en el archivo: No se pudo abrir: "<<"ReporteStock"<<endl;
        exit(1);
    }
    int tam;
    archReporte<<fixed;
    archReporte.precision(2);
    struct StockProducto stockProducto;
    
    while(true){
        archBin.read(reinterpret_cast<char *> (&stockProducto),
        sizeof(struct StockProducto));
        if(archBin.eof()) break;
        archReporte<<left<<setw(10)<<stockProducto.codigo;
        tam = strlen(stockProducto.descripcion);
        archReporte<<stockProducto.descripcion;
        archReporte<<right<<setw(50-tam)<<' '<<setw(2)<<stockProducto.stock;
        archReporte<<setw(15)<<stockProducto.precio<<endl;
    }
}

void crearPedidosBin(const char * nombreDatos, const char * nombreBin){

    ifstream archDatos(nombreDatos, ios::in);
    if(not archDatos.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreDatos<<endl;
        exit(1);
    }

    ofstream archBin(nombreBin, ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreBin<<endl;
        exit(1);
    }

    struct Pedido pedido;
    while(true){
        leerPedido(archDatos, pedido);
        if(archDatos.eof()) break;
        archBin.write(reinterpret_cast<const char*>(&pedido), sizeof(struct Pedido));
    }
    
 }

void leerPedido(ifstream & archDatos, struct Pedido & pedido){
    int dd, mm, aaaa, hor, min, seg;
    char c;
    archDatos>>dd;
    if(archDatos.eof()) return;
    archDatos>>c>>mm>>c>>aaaa;
    pedido.fecha = aaaa*10000 + mm*100 + dd;
    archDatos>>hor>>c>>min>>c>>seg;
    pedido.hora = hor*3600 + min*60 + seg;
    archDatos>>pedido.numero;
    archDatos>>pedido.cliente;
    pedido.cantProdPed = 0;
}

void mostrarPedidosBin(const char * nombreBin){

    ifstream archBin(nombreBin, ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error en el archivo: No se pudo abrir: "<<nombreBin<<endl;
        exit(1);
    }
    ofstream archReporte("ReportePedidos.txt", ios::out);
    if(not archReporte.is_open()){
        cout<<"Error en el archivo: No se pudo abrir: "<<"ReporteStock"<<endl;
        exit(1);
    }
    int dd, mm, aaaa, hor, min, seg;
    archReporte<<fixed;
    archReporte.precision(2);
    struct Pedido pedido;

    while(true){
        archBin.read(reinterpret_cast<char *> (&pedido), sizeof(struct Pedido));
        if(archBin.eof()) break;
        fechaToDMA(pedido.fecha, dd, mm, aaaa);
        segundosToHMS(pedido.hora, hor, min, seg);
        archReporte<<setw(5)<<' '<<setfill('0')<<setw(2)<<dd<<'/'
        <<setw(2)<<mm<<'/'<<setw(4)<<aaaa<<setfill(' ');
        archReporte<<setw(10)<<' '<<setfill('0')<<setw(2)<<hor<<':'
        <<setw(2)<<min<<':'<<setw(2)<<seg<<setfill(' ');
        archReporte<<setw(20)<<pedido.numero;
        archReporte<<setw(20)<<pedido.cliente<<endl;    
    }
}

void actualizarPedido(const char * nombreDetalleProd, const char * nombreStockBin,
    const char * nombrePedidosBin){
    int posPedido, posProd;
    ifstream archDetalle(nombreDetalleProd, ios::in);
    if(not archDetalle.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreDetalleProd<<endl;
        exit(1);
    }
    
    fstream archStockBin(nombreStockBin, ios::in|ios::out|ios::binary);
    if(not archStockBin.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombreStockBin<<endl;
        exit(1);
    }

    fstream archPedidosBin(nombrePedidosBin, ios::in|ios::out|ios::binary);
    if(not archPedidosBin.is_open()){
        cout<<"Error en el archivo, no se pudo abrir: "<<nombrePedidosBin<<endl;
        exit(1);
    }
    int nroPedido, cantSolic;   
    char codProd[10];
    struct Pedido pedido;
    struct StockProducto stockProducto;

    while(true){
        leerDetalleProducto(archDetalle, nroPedido, codProd, cantSolic);
        if(archDetalle.eof()) break;
        posPedido = buscaPedido(archPedidosBin, nroPedido);
        if (posPedido != NO_ENCONTRADO){
            posProd = buscarProducto(archStockBin, codProd);
            if(posProd != NO_ENCONTRADO){
                archStockBin.seekg(posProd*sizeof(struct StockProducto),ios::beg);
                archStockBin.read(reinterpret_cast<char *>(&stockProducto),
                sizeof(struct StockProducto));
                archPedidosBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
                archPedidosBin.read(reinterpret_cast<char *>(&pedido),
                sizeof(struct Pedido));
                if(stockProducto.stock>0){ //se atiende si hay estock
                    if(stockProducto.stock>=cantSolic){
                        actualizaProductoPedido(pedido.productosPedidos,
                        pedido.cantProdPed,
                        stockProducto, cantSolic);
                        stockProducto.stock -= cantSolic;
                    }
                    else{
                        actualizaProductoPedido(pedido.productosPedidos,
                        pedido.cantProdPed,
                        stockProducto, stockProducto.stock);
                        stockProducto.stock = 0;
                    }

                    archStockBin.seekg(posProd*sizeof(struct StockProducto),ios::beg);
                    archStockBin.write(reinterpret_cast<const char *>(&stockProducto),
                    sizeof(struct StockProducto));
                    archPedidosBin.seekg(posPedido*sizeof(struct Pedido),ios::beg);
                    archPedidosBin.write(reinterpret_cast<const char *>(&pedido),
                    sizeof(struct Pedido));
                    archStockBin.flush();
                    archPedidosBin.flush();
                }
            }
        }
    }
}

void leerDetalleProducto(ifstream & archDetalle, int & nroPedido,
    char * codProd, int & cantSolic){
    char cadena[10];
    archDetalle>>nroPedido;
    if(archDetalle.eof()) return;
        archDetalle>>cadena;
        strcpy(codProd, cadena);
        archDetalle>>cantSolic;
}

void actualizaProductoPedido(struct ProductoSolicitado * productosPedidos,
    int & cant, struct StockProducto stockProducto, int cantSolic){
    strcpy(productosPedidos[cant].codigo, stockProducto.codigo);
    strcpy(productosPedidos[cant].descripcion, stockProducto.descripcion);
    productosPedidos[cant].cantidad = cantSolic;
    productosPedidos[cant].precioUnitario = stockProducto.precio;
    productosPedidos[cant].subTotal = stockProducto.precio * cantSolic;
    cant++;
}

int buscaPedido(fstream & archPedidosBin, int nroPedido){
    struct Pedido pedido;
    int tamArch, tamReg, numReg;
    tamReg = sizeof(struct Pedido);
    datosArchivo(archPedidosBin, tamArch, tamReg, numReg);
    for(int i=0; i<numReg; i++){
        archPedidosBin.seekg(i*tamReg, ios::beg);
        archPedidosBin.read(reinterpret_cast<char *>(&pedido),
        sizeof(struct Pedido));
        if(pedido.numero == nroPedido) return i;
    }
    return NO_ENCONTRADO;
}

int buscarProducto(fstream & archStockBin, char * codProd){

    struct StockProducto stockProducto;
    int tamArch, tamReg, numReg;
    tamReg = sizeof(struct StockProducto);
    datosArchivo(archStockBin, tamArch, tamReg, numReg);
    for(int i=0; i<numReg; i++){
        archStockBin.seekg(i*tamReg, ios::beg);
        archStockBin.read(reinterpret_cast<char *>(&stockProducto),
        sizeof(struct StockProducto));
        if(strcmp(stockProducto.codigo, codProd) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void mostrarReporte(const char * nombreBin, const char * nombreReporte){
    //solo necesitamos que se aperture como lectura
    ifstream archBin(nombreBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"Error al abrir el archivo"<<nombreBin<<endl;
        exit(1);
    }
    ofstream archReporte(nombreReporte,ios::out);
    if(not archReporte.is_open()){
        cout<<"ERROR AL ABRIR "<<nombreReporte<<endl;
        exit(1);
    }
    struct Pedido pedido;
    int tamArch, tamReg, numReg, dd, mm, aaaa, hor, min, seg;
    tamReg = sizeof(struct Pedido);
    datosArchivo(archBin, tamArch, tamReg, numReg);
    mostrarLinea(archReporte, '=', MAX_LINEA);
    imprimirEncabezado(archReporte);
    
    for(int i=0; i<numReg; i++){
        archBin.read(reinterpret_cast<char*>(&pedido),sizeof(struct Pedido));
        mostrarLinea(archReporte, '=', MAX_LINEA);
        archReporte<<"Pedido No. "<<setw(10)<<pedido.numero<<setw(20);
        fechaToDMA(pedido.fecha, dd, mm, aaaa);
        segundosToHMS(pedido.hora, hor, min, seg);
        archReporte<<setw(20)<<"Fecha: "<<setw(5)<<' '<<setfill('0')<<setw(2)
        <<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aaaa<<setfill(' ');
        archReporte<<setw(20)<<"Hora: "<<' '<<setfill('0')<<setw(2)<<hor<<':'
        <<setw(2)<<min<<':'<<setw(2)<<seg<<setfill(' ')<<endl;
        archReporte<<"Cliente: "<<endl<<"DNI:"<<setw(4)<<pedido.cliente;
        archReporte<<endl<<endl;
        muestraProductos(pedido.productosPedidos, pedido.cantProdPed, archReporte);
    }
}

void muestraProductos(struct ProductoSolicitado * productosPedidos,int cantProd,
    ofstream & archRep){
    archRep<<"Productos: "<<endl;
    archRep<<setw(11)<<"Código"<<setw(30)<<"Descripcion"
    <<setw(25)<<"Cantidad"<<setw(25)<<"Precio Unitario"
    <<setw(25)<<"Sub Total"<<endl;
    archRep<<fixed;
    archRep.precision(2);
    for(int i=0; i<cantProd; i++){
        archRep<<right<<setw(10)<<productosPedidos[i].codigo<<setw(5)
        <<' '<<left<<setw(40)<<productosPedidos[i].descripcion
        <<right<<setw(7)<<productosPedidos[i].cantidad
        <<setw(25)<<productosPedidos[i].precioUnitario
        <<setw(25)<<productosPedidos[i].subTotal<<endl;
    }
}

void datosArchivo(fstream & archBin, int tamArch, int tamReg, int & numReg){

    archBin.seekg(0,ios::end); //avanzo hasta el final
    tamArch = archBin.tellg(); //obtengo el tamaño
    archBin.seekg(0,ios::beg); //coloco el indicador al inicio
    numReg = tamArch/tamReg; //obtengo la cant de registros
}

void datosArchivo(ifstream & archBin, int tamArch, int tamReg, int & numReg){

    archBin.seekg(0,ios::end); //avanzo hasta el final
    tamArch = archBin.tellg(); //obtengo el tamaño
    archBin.seekg(0,ios::beg); //coloco el indicador al inicio
    numReg = tamArch/tamReg; //obtengo la cant de registros
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

void imprimirEncabezado(ofstream & archRep){
    archRep<<setw(75)<<"TIENDA VIRTUAL LA MAGNIFICA"<<endl;
    archRep<<setw(70)<<"ATENCION DE PEDIDOS"<<endl;
}

void mostrarLinea(ofstream & archRep, const char car, int max){
    for(int i=0; i<max; i++){
        archRep.put(car);
    }
    archRep<<endl;
}
