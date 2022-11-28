/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   PEDIDOS.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:21 PM
 */

#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "Entregado.h"
#include "NoEntregado.h"
    
struct Pedidos{ //estructura que guarda un pedido
    int numero; //numero de Pedido
    int fecha; //fecha del pedido aaaammdd
    int hora; //la hora la guarda en segundos
    int cliente; //dni del cliente
    struct Entregado * productosEntregados; //arreglo dinámico prod Entregados
    int cantProdEnt; //cant de producto entregado
    struct NoEntregado * productosNoEntregados; //arreglo dinámico prod no
    //entregados
    int cantProdNoEnt; //cant de productos no entregados
};

#endif /* PEDIDOS_H */

