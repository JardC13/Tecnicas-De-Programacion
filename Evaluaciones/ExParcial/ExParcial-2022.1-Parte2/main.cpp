/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   main.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 6 de octubre de 2022, 05:03 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Funciones.h"
#define MAXAL 25
#define MAXCUR 30

int main(int argc, char** argv) {
    int arrCodA [MAXAL]={0}, nAlu, arrCodC [MAXCUR]={0}, nCursos; 
    int arrCurApro [MAXAL] = {0}, arrCurDes [MAXAL] = {0};
    double arrVCre [MAXCUR] = {0.0}, arrCreA [MAXAL] = {0.0}, arrCreD [MAXAL] = {0.0}, arrCreN [MAXAL] = {0.0};
    llenarArregloAl(arrCodA, arrCreA, arrCreD, arrCreN, nAlu);
    llenarArregloCur(arrCodC, arrVCre, nCursos);
    actualizarArreglosConNotas(arrCodA, arrCreA, arrCreD, nAlu, arrCodC, arrVCre, nCursos, arrCurApro, arrCurDes);
    imprimirReporte(arrCodA, arrCurApro, arrCurDes, arrCreA, arrCreD, arrCreN, nAlu);
    return 0;
}

