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
 * Creado el 6 de octubre de 2022, 05:03 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>        
#include <fstream>
using namespace std;

#include "Funciones.h"
#define TAMLINEA 200

void imprimirLinea(ofstream&arch,char c,int cant){
    for(int i = 0; i <= cant; i++){
        arch<<c;
    }
    arch<<endl;
}

void llenarArregloAl(int*arrCodA,double*arrCreA,double*arrCreD,double*arrCreN,int&nAlu){
    int codA;
    double creA, creD, creN;
    ifstream archAlu ("alumnos.txt", ios::in);
    if (not archAlu.is_open()){
        cout<<"No se pudo abrir el archivo alumnos.txt"<<endl;
        exit(1);
    }
    nAlu = 0;
    while (true){
        archAlu>>codA;
        if (archAlu.eof()) break;
        archAlu>>ws;
        while(archAlu.get() != ' ');
        archAlu>>creA>>creD>>creN;
        arrCodA[nAlu] = codA;
        arrCreA[nAlu] = creA;
        arrCreD[nAlu] = creD;
        arrCreN[nAlu] = creN;
        nAlu++;
    }
}

void llenarArregloCur(int*arrCodC, double*arrVCre,int&nCursos){
    int codC;
    double vCre;
   ifstream archCur ("cursos.txt", ios::in);
    if (not archCur.is_open()){
        cout<<"No se pudo abrir el archivo cursos.txt"<<endl;
        exit(1);
    }
   nCursos=0;
    while(1){
        archCur>>codC;
        if(archCur.eof()) break;
        archCur>>ws;
        while(archCur.get() != '}');
        archCur>>vCre;
        arrCodC[nCursos] = codC;
        arrVCre[nCursos] = vCre;
        nCursos++;
    }
}

void actualizarArreglosConNotas(int*arrCodA,double*arrCreA,double*arrCreD,int&nAlu,int*arrCodC,double*arrVCre,int&nCursos,int*arrCurApro,int*arrCurDes){
    char c;
    int codCur, i,  j, codAl, nota;
    ifstream archNot ("notas.txt", ios::in);
    if (not archNot.is_open()){
        cout<<"No se pudo abrir el archivo notas.txt"<<endl;
        exit(1);
    }
    while(1){
        archNot>>codCur;
        if (archNot.eof()) break;
        i = encontrarCodCur(codCur, arrCodC, nCursos);
        if(i>=0){
            while(1){
                archNot>>codAl>>nota;
                c = archNot.get();
                j = encontrarAl(codAl, arrCodA, nAlu);
                if (j>=0){
                    if (11<=nota){
                        arrCurApro[j] ++;
                        arrCreA[j] = arrCreA[j] + arrVCre[i];
                    }
                    else{
                        arrCurDes[j]++;
                        arrCreD[j] = arrCreD[j]  + arrVCre[i];
                    }
                }
                if (c =='\n') break;
            }
        }    
    }
}

int encontrarCodCur(int codCur,int*arrCodC,int&nCursos){
    for(int i=0; i<nCursos; i++){
        if(arrCodC[i] == codCur){ 
            return i;
        }
    }
    return -1;
}

int encontrarAl(int codAl,int*arrCodA,int&nAlu){
    for(int j=0; j<nAlu; j++){
        if(arrCodA[j] == codAl){
            return j;
        }
    }
    return -1;
}

void imprimirReporte(int*arrCodA,int*arrCurApro,int*arrCurDes,double*arrCreA,double*arrCreD,double*arrCreN, int&nAlu){
    double diferencia;
    int nAluA=0, nAluD=0;
    ofstream archRep ("ReportedeConsolidadoResultados.txt", ios::out);
    if (not archRep.is_open()){
        cout<<"No se pudo abrir el archivo ReportedeConsolidadoResultados.txt"<<endl;
        exit(1);
    }
    archRep<<setw(90)<<"INSTITUCION EDUCATIVA LIMA"<<endl;
    archRep<<setw(85)<<"NOTAS POR ALUMNO"<<endl;
    imprimirLinea(archRep, '=', TAMLINEA);
    archRep<<"CODIGO"<<setw(30)<<"CURSOS APROB."<<setw(25)<<"CURSOS DESA."
            <<setw(25)<<"CRED. APROB."<<setw(25)<<"CRED. DESA."<< setw(30)<<"OBSERVACION"<<endl;
    imprimirLinea(archRep, '-', TAMLINEA);
    archRep<<fixed;
    archRep.precision(2);
    for (int i = 0; i<nAlu; i++){
        archRep<<setw(3)<<i+1 <<")  "<<arrCodA[i]<<setw(15)<<arrCurApro[i]<<setw(25)<<arrCurDes[i]
                <<setw(25)<<arrCreA[i]<<setw(25)<<arrCreD[i]<<setw(40);
        if(arrCreN[i] <= arrCreA[i]){
            archRep<<"Pasara a facultad"<<endl;
            nAluA++;
        }
        else{
            diferencia = arrCreN[i] - arrCreA[i];
            archRep<<"No pasara a facultad, faltan "<<diferencia<<" creditos"<<endl;
            nAluD++;
        }
    }
    imprimirLinea(archRep, '-', TAMLINEA);
    archRep<<"Cantidad de alumnos que pasaran a Facultad:    "<<nAluA<<endl;
    archRep<<"Cantidad de alumnos que no pasaran a Facultad:  "<<nAluD<<endl;
    imprimirLinea(archRep, '=', TAMLINEA);
    archRep<<"TOTAL DE ALUMNOS MATRICULADOS EN EL CICLO:     "<<nAlu<<endl;
    imprimirLinea(archRep, '=', TAMLINEA);
}