/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   StockDeProductos.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 07:48 PM
 */

#ifndef STOCKDEPRODUCTOS_H
#define STOCKDEPRODUCTOS_H
struct StockProducto{
    char codigo[10]; //codigo del producto
    char descripcion[100]; //descripcion del producto
    int stock; //stock
    double precio; //precio
};

#endif /* STOCKDEPRODUCTOS_H */

