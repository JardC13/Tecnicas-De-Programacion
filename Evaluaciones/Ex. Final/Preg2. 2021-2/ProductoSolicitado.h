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
 * Creado el 27 de noviembre de 2022, 07:53 PM
 */

#ifndef PRODUCTOSOLICITADO_H
#define PRODUCTOSOLICITADO_H

struct ProductoSolicitado{
    char codigo[10]; //código producto
    char descripcion[100]; //descripción
    int cantidad; //cantidad
    double precioUnitario; //precio unitario
    double subTotal; //subtotal
};

#endif /* PRODUCTOSOLICITADO_H */

