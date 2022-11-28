/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   ProductoSolicitado.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 07:49 PM
 */

#ifndef PEDIDOSINTERNET_H
#define PEDIDOSINTERNET_H

#include "ProductoSolicitado.h"
struct Pedido{ //estructura que guarda un pedido
    int numero;  //numero de Pedido
    int fecha;  //fecha del pedido aaaammdd
    int hora;  //la hora la guarda en segundos
    int cliente;  //dni del cliente
    struct ProductoSolicitado productosPedidos[20]; //arreglo prod Pedidos
    int cantProdPed; //cant de producto pedido
};



#endif /* PEDIDOSINTERNET_H */

