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
 * Creado el 22 de octubre de 2022, 12:38 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Funciones.h"
#define NO_ENCONTRADO -1

int main(int argc, char** argv) {
    int dni[50], telef[50],numDat,d, pos;
    double sueldo[50];
    cout.precision(2);
    cout<<fixed;
    leerDatos(dni,telef,sueldo,numDat);
    ordenar(dni,telef,sueldo,numDat);
    imprimirDatos(dni,telef,sueldo,numDat);
    while(1){
        cout<<"Ingrese el DNI: ";
        cin>>d;
        if(d==0)break;
        pos = busquedaBinaria(d,dni,numDat);
        if (pos != NO_ENCONTRADO){
            cout<<"Sus datos son:"<<endl;
            cout<<"DNI :"<<setw(10)<<dni[pos]<<endl;
            cout<<"Telefono:"<<setw(10)<<telef[pos]<<endl;
            cout<<"Sueldo :"<<setw(19)<<sueldo[pos]<<endl<<endl;
        }
        else cout<<"No se encontro el DNI"<<endl<<endl;
    }
    return 0;
}


