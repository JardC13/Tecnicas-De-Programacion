/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   ENTREGADO.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:19 PM
 */

#ifndef ENTREGADO_H
#define ENTREGADO_H

struct Entregado{ //estructura que guarda un producto entregado
    char *codigo; //codigo del producto
    char *descripcion; //descripción del producto
    int cantEntregada; //cantidad entregada
    double precioUnitario; //precio del producto
    double subtotal; //precio * cantidad
};

#endif /* ENTREGADO_H */

