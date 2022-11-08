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
 * Creado el 8 de noviembre de 2022, 12:25 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "Funciones.h"
#include "DOCENTES.h"

#define M_ALUM 100
#define M_PROF 100

int main(int argc, char** argv) {
    char *nombres[M_ALUM + M_PROF], *distritosA[M_ALUM];
    char *especialidad[M_ALUM], *facultad[M_ALUM];
    int codigoA[M_ALUM], escala[M_ALUM];
    int codigoTodos[M_ALUM + M_PROF];
    double vCredito[M_ALUM], nCreditos[M_ALUM];
    int cAlumnos, cProf, cTotal;
    struct DOCENTES datosProf[M_PROF];
    
    llenarDatos(nombres, codigoTodos, codigoA, distritosA, especialidad, facultad, escala, vCredito, nCreditos, cAlumnos, datosProf, cProf, cTotal);
    ordenarAlumnos(codigoA,distritosA, especialidad, facultad, escala, vCredito, nCreditos, cAlumnos);
    imprimirReporte(nombres, codigoTodos, codigoA, distritosA, especialidad, facultad, escala, vCredito, nCreditos, cAlumnos, datosProf, cProf, cTotal);
    return 0;
}

