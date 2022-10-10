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
 * Creado el 7 de octubre de 2022, 01:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Funciones.h"
#define N_PRO 300
#define N_PLA 100
int main(int argc, char** argv) {
//Apertura y validación de archivos de lectura y escritura
    ifstream archListPrec("ListaDePrecios.txt",ios::in);
    if(!archListPrec.is_open()) {
    cout<<"Error en el archivo Lista de precios";
    exit(1);
    }
    ifstream archPlatos("Platos.txt",ios::in);
    if(!archPlatos.is_open()) {
    cout<<"Error en el archivo de Platos";
    exit(1);
    }
    ifstream archPlatPrep("PlatosAPreparar.txt",ios::in);
    if(!archPlatPrep.is_open()) {
    cout<<"Error en el archivo Platos a preparar";
    exit(1);
    }
    ofstream archRep("Reporte.txt",ios::out);
    if(!archRep.is_open()) {
    cout<<"Error en el archivo Reporte";
    exit(1);
    }
 //Función que elabora el reporte final
    generarReporteCostos(archListPrec, archPlatos, archPlatPrep, archRep);
    return 0;
}

