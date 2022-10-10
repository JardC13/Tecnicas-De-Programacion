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
 * Creado el 7 de octubre de 2022, 01:52 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Funciones.h"

void generarReporteCostos(ifstream &, ifstream &, ifstream &, ofstream &);
void imprimirLinea(ofstream &, char, int);
void imprimirEncabezado(ifstream &, ofstream &);
void imprimirProveedor(ifstream &, ofstream &);
double calcularCostoEImprPlato(ifstream &, ifstream &,ofstream &,int, int, int);
void imprimirPlato(int, ifstream &, ofstream &);
double calcularPrecioEImprDatos(int, ifstream &, ifstream &, ofstream &);
double buscarPrecio(int, ifstream &);

#endif /* FUNCIONES_H */

