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
 * Creado el 10 de octubre de 2022, 11:28 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Funciones.h"

void cargarTodosProductos(int *, double *, int &);
void cargarProductosAlmacenados(int *, double *, int, double *, double *);
int buscarIdProducto(int, int *, int);
void ordenarSubTotalProducto(int *, double *, double *, double *, int);
void cambiarInt(int *,int ,int );
void cambiarDouble(double *,int,int );
void generaPrimeraParteReporte(int *, double *, double *, double *, int, ofstream &);
void mostrarCabeceraParte1(ofstream &);
void mostrarLinea(ofstream &, char , int);
void cargarPlatosPreparar(int *, int *, int &);
void cargarPlatosPrecios(int *, int *, int, int *, double *, int, double *);
int buscarIdPlato(int *, int, int);
void actualizarSubTotalPlatos(int *, int *, int, double *, double *);
void ordenarSubTotalPlato(int *, double *, int *, double *, int);
void generaSegundaParteReporte(int *, int *, double *, double *, int, ofstream &);
void mostrarCabeceraParte2(ofstream &);

#endif /* FUNCIONES_H */

