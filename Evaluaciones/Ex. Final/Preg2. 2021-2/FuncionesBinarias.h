/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   FuncionesBinarias.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 07:55 PM
 */

#ifndef FUNCIONESBINARIAS_H
#define FUNCIONESBINARIAS_H
void crearStockBin(const char * , const char * );
void mostrarStockBin(const char * );
void leerStockProducto(ifstream & , struct StockProducto &);
void crearPedidosBin(const char *, const char *);
void leerPedido(ifstream & , struct Pedido &);
void mostrarPedidosBin(const char *);
void fechaToDMA(int , int &, int &, int &);
void segundosToHMS(int , int &, int &, int &);
void actualizarPedido(const char * , const char *, const char *);
void leerDetalleProducto(ifstream & , int & , char * , int & );
int buscaPedido(fstream & , int );
int buscarProducto(fstream & , char * );
void datosArchivo(fstream & , int , int , int &);
void datosArchivo(ifstream & , int , int , int &);
void actualizaProductoPedido(struct ProductoSolicitado *, int & ,
struct StockProducto, int );
void mostrarReporte(const char*, const char *);
void muestraProductos(struct ProductoSolicitado *, int , ofstream & );
void imprimirEncabezado(ofstream & );
void mostrarLinea(ofstream & , const char , int );

#endif /* FUNCIONESBINARIAS_H */

