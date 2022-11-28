/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   funcionesDeEstructuras.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:23 PM
 */

#ifndef FUNCIONESDEESTRUCTURAS_H
#define FUNCIONESDEESTRUCTURAS_H

void llenarProductos(const char *, struct StockProd *, int &);
void probarllenarProductos(struct StockProd *, int , const char *);

void llenarPedidos(const char *, struct Pedidos* , int &);
void probarPedidos(struct Pedidos* ,int ,const char *);

void fechaToDMA(int , int &, int &, int &);
void segundosToHMS(int , int &, int &, int &);

void completarPedidos(const char *, struct Pedidos* ,int ,struct StockProd *,
int );

void asignarEntrega(struct Entregado *,int , char *, double , char*, int );
void asignarNoEntrega(struct NoEntregado *, int, char*, char*,int);

int buscaProducto(char *,struct StockProd *,int );
int buscaPedido(int ,struct Pedidos *, int );

void reporteDePedidosFinal(struct Pedidos*, int, const char*);
void imprimirProdEnt(ofstream &, struct Entregado *, int );
void imprimirProdNoEnt(ofstream & ,struct NoEntregado *, int );

void linea(ofstream & archReporte, const char car, int);
 void mostrarEncabezado(ofstream & archReporte);

#endif /* FUNCIONESDEESTRUCTURAS_H */

