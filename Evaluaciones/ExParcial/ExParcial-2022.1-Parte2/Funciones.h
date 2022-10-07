/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   Funciones.h
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283 
 * Horario: 0432
 * Creado el 6 de octubre de 2022, 05:03 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Funciones.h"

void imprimirLinea(ofstream&,char,int);
void llenarArregloAl(int*,double*,double*,double*,int&);
void llenarArregloCur(int*, double*,int&);
void actualizarArreglosConNotas(int*,double*,double*,int&,int*, 
            double*,int&,int*,int*);
int encontrarCodCur(int ,int*,int&);
int encontrarAl(int ,int*,int&);
void imprimirReporte(int*,int*,int*,
        double*,double*,double*, int&);

#endif /* FUNCIONES_H */

