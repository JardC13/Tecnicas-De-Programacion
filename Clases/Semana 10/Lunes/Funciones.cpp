/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   Funciones.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 22 de octubre de 2022, 12:39 PM
 */

#include <iostream>
#include <iomanip>        
#include <fstream>
using namespace std;
#include "Funciones.h"
#define NO_ENCONTRADO -1

void leerDatos(int *dni,int *telef,double *sueldo, int &numDat){
    ifstream arch("Personas.txt", ios::in);
    if(not arch.is_open()) {
        cout<<"ERROR: No sze pudo abrir Personas.txt"<<endl;
        exit(1);
    }
    int d,t;
    double s;
    numDat=0;
    while(true){
        arch>>d;
        if(arch.eof())break;
        arch>>t>>s;
        dni[numDat] = d;
        telef[numDat] = t;
        sueldo[numDat] = s;
        numDat++;
    }
}

void ordenar(int *dni,int *telef,double *sueldo, int numDat){
    for(int i=0; i<numDat-1; i++)
        for(int k= i+1; k<numDat; k++)
            if(dni[i]>dni[k]) {
                cambiarI(dni[i],dni[k]);
                cambiarI(telef[i],telef[k]);
                cambiarD(sueldo[i],sueldo[k]);
            }
}

void cambiarI(int &datoI,int &datoK){
    int aux;
    aux = datoI;
    datoI = datoK;
    datoK = aux;
}

void cambiarD(double &datoI,double &datoK){
    double aux;
    aux = datoI;
    datoI = datoK;
    datoK = aux;
}

void imprimirDatos(int *dni,int *telef,double *sueldo, int numDat){
    for(int i=0; i<numDat; i++)
        cout<<setw(10)<<dni[i]<<setw(10)<<telef[i]<<setw(10)<<sueldo[i]<<endl;
}

int busquedaBinaria(int d,int*dni,int numDat){
    int limiteInferior, limiteSuperior,puntoMedio;
    limiteInferior = 0;
    limiteSuperior =numDat-1;
    while(true){
        if(limiteInferior>limiteSuperior) return NO_ENCONTRADO;
        puntoMedio = (limiteInferior+limiteSuperior)/2;
        if (d == dni[puntoMedio]) return puntoMedio;
        if (d < dni[puntoMedio])
            limiteSuperior = puntoMedio -1;
        else
            limiteInferior = puntoMedio+1;
    }
}