/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   PRODUCTOS.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:18 PM
 */

#ifndef PRODUCTOS_H
#define PRODUCTOS_H

struct StockProd{
    char * codigo; //codigo del producto
    char * descripcion; //descripcion del producto
    int stock; //stock
    double precio; //precio
};

#endif /* PRODUCTOS_H */

