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
 * Creado el 8 de noviembre de 2022, 12:29 AM
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

void llenarDatos(char**nombres,int*codigoTodos,int*codigoA,char**distritosA,char**especialidad,char**facultad,int*escala,
            double*vCredito,double*nCreditos,int&cAlumnos,struct DOCENTES *datosProf,int&cProf, int&cTotal){
    ifstream archDatos ("MiembrosDeTP.csv", ios::in);
    if (not archDatos.is_open()){
        cout<<"No se pudo abrir el archivo .csv";
        exit(1);
    }
    //General
    char nom[100], apellido1[100], apellido2[100], dist[100];
    int cod;
    char identificador;
   //Para alumnos
    char esp[100], facu[100];
    int esca;
    double vCre, nCre;
   //Para prof
    char cat[100], dedi[100], secc[100], grd[100];
    double suel;
    //Contadores
    cAlumnos = 0;
    cProf = 0;
    cTotal = 0;
    while(1){
        archDatos>>identificador;
        if (archDatos.eof()) break;
        archDatos.get();
        leerYOrdenarNombre(nom, apellido1, apellido2, archDatos);
        archDatos>>cod;
        archDatos.get();
        archDatos.getline(dist, 100, ',');
        nombres[cTotal] = new char [strlen(nom) + 1];
        strcpy(nombres[cTotal], nom);
        codigoTodos[cTotal] = cod;
        if (identificador == 'A'){
            leerAlumno(esp, facu, esca, vCre, nCre, archDatos);
            codigoA[cAlumnos] = cod;
            distritosA[cAlumnos] = new char [strlen(dist)+1];
            strcpy(distritosA[cAlumnos], dist);
            especialidad[cAlumnos] = new char [strlen(esp)+1];
            strcpy(especialidad[cAlumnos], esp);
            facultad[cAlumnos] = new char [strlen(facu)+1];
            strcpy(facultad[cAlumnos], facu);
            escala[cAlumnos] = esca;
            vCredito[cAlumnos] = vCre;
            nCreditos[cAlumnos] = nCre;
            cAlumnos++;
        }
        else{
            leerProf(cat, dedi, secc, grd, suel, archDatos);
            datosProf[cProf].categoria=new char [strlen(cat)+1];
            datosProf[cProf].dedicacion=new char [strlen(dedi)+1];
            datosProf[cProf].distritoD=new char [strlen(dist)+1];
            datosProf[cProf].grado=new char [strlen(grd)+1];
            datosProf[cProf].seccion=new char [strlen(secc)+1];
            datosProf[cProf].codigo=cod;
            datosProf[cProf].sueldo=suel;
            strcpy(datosProf[cProf].categoria,cat);
            strcpy(datosProf[cProf].dedicacion,dedi);
            strcpy(datosProf[cProf].distritoD,dist);
            strcpy(datosProf[cProf].grado,grd);
            strcpy(datosProf[cProf].seccion,secc);
            cProf++;
        }
        cTotal++;
    }
    
}

void leerYOrdenarNombre(char*nom,char*apellido1,char*apellido2,ifstream&archDatos){
    char car[] = " ";
    archDatos.getline(apellido1, 100, '/');
    archDatos.getline(apellido2, 100, '/');
    archDatos.getline(nom, 100, ',');
    strcat(nom, car); 
    strcat(nom, apellido1);
    strcat(nom, car); 
    strcat(nom, apellido2);
}
void leerAlumno(char*esp,char*facu,int&esca,double&vCre,double&nCre,ifstream&archDatos){
    archDatos.getline(esp, 100, ',');
    archDatos.getline(facu, 100, ',');
    archDatos>>esca;
    archDatos.get();
    archDatos>>vCre;
    archDatos.get();
    archDatos>>nCre;
    archDatos.unget();
    while(archDatos.get()!='\n');
}

void leerProf(char*cat,char*dedi,char*secc,char*grd,double&suel,ifstream&archDatos){
     archDatos.getline(cat, 100, ',');
    archDatos.getline(dedi, 100, ',');
    archDatos.getline(secc, 100, ',');
    archDatos.getline(grd, 100, ',');
    archDatos>>suel;
    archDatos.unget();
    while(archDatos.get()!='\n');
}

void ordenarAlumnos(int*codigoA,char**distritosA,char**especialidad,char**facultad,int*escala,double*vCredito,double*nCreditos,int&cAlumnos){
    for(int i =0; i<cAlumnos-1; i++){
        for(int j = i+1; j<cAlumnos; j++){
            if(strcmp(distritosA[i],distritosA[j])<0 or (strcmp(distritosA[i],distritosA[j])==0 and escala[i]>escala[j])){
                CambiarI(codigoA[i], codigoA[j]);
                CambiarC(distritosA[i],distritosA[j]);
                CambiarC(especialidad[i],especialidad[j]);
                CambiarC(facultad[i],facultad[j]);
                CambiarI(escala[i],escala[j]);
                CambiarD(vCredito[i],vCredito[j]);
                CambiarD(nCreditos[i],nCreditos[j]);
            }
        }
    }
}

void CambiarI(int &datoi,int &datoj){
    int aux=datoi;
    datoi=datoj;
    datoj=aux;
}
void CambiarD(double &datoi,double &datoj){
    double aux=datoi;
    datoi=datoj;
    datoj=aux;
}
void CambiarC(char * &datoi,char * &datoj){
    char *aux=datoi;
    datoi=datoj;
    datoj=aux;
}

void imprimirReporte(char**nombres,int*codigoTodos,int*codigoA,char**distritosA,char**especialidad,char**facultad,int*escala,
            double*vCredito,double*nCreditos,int&cAlumnos,struct DOCENTES *datosProf,int&cProf, int&cTotal){
    double  ingreso, ingresoTotal=0.0, egreso, egresoTotal=0.0, balanceFinal;
    ofstream archRep ("Balance_de_Ingresos.txt", ios::out); 
    if (not archRep.is_open()){
        cout<<"no se puedo abrir el archivo .txt";
        exit(1);
    }
    archRep<<setw(120)<<"Universidad TP"<<endl;
    imprimirLinea(archRep, '=', 300);
    archRep<<"RECAUDACION POR MATRICULAS:"<<endl;
    imprimirLinea(archRep, '-', 300);
    archRep<<left<<setw(20)<<"CODIGO"<<setw(70)<<"NOMBRE"<<setw(50)<<"DISTRITO"
            <<setw(30)<<"ESPECIALIDAD"<<setw(15)<<"FACULTAD"<<setw(15)<<"ESCALA"<<setw(20)
            <<"VCRED"<<setw(20)<<"CREDMAT"<<setw(30)<<"PAGO"<<endl;
    imprimirLinea(archRep, '-', 300);
    for (int i=0; i<cAlumnos; i++){
        ingreso = vCredito[i]*nCreditos[i];
        archRep<<left<<setw(20)<<codigoA[i]<<setw(70);
        escribirNombre(codigoA[i], codigoTodos, nombres, cTotal, archRep);
        archRep<<left<<setw(50)<<distritosA[i]<<setw(30)<<especialidad[i]<<setw(15)
                <<facultad[i]<<setw(15)<<escala[i]<<setw(20)<<vCredito[i]<<setw(20)
                <<nCreditos[i]<<setw(30)<<ingreso<<endl; 
        ingresoTotal = ingresoTotal +  ingreso;
    }
    imprimirLinea(archRep, '-', 300);
    archRep<<"Total de ingresos por matriculas: "<<ingresoTotal<<endl;
    imprimirLinea(archRep, '=', 300);
    archRep<<"PAGO A LOS DOCENTES:"<<endl;
    imprimirLinea(archRep, '-', 300);
    archRep<<left<<setw(20)<<"CODIGO"<<setw(70)<<"NOMBRE"<<setw(50)<<"DISTRITO"
            <<setw(30)<<"CATEGORIA"<<setw(30)<<"DEDICACION"<<setw(30)<<"SECCION"<<setw(30)
            <<"GRADO"<<setw(30)<<"PAGOS"<<endl;
    for (int j=0; j<cProf; j++){
         egreso=datosProf[j].sueldo*8.0;
         archRep<<left<<setw(20)<<datosProf[j].codigo<<setw(70);
         escribirNombre(datosProf[j].codigo, codigoTodos, nombres, cTotal, archRep);
         archRep<<left<<setw(50)<<datosProf[j].distritoD<<setw(30)<<datosProf[j].categoria
                 <<setw(30)<<datosProf[j].dedicacion<<setw(30)<<datosProf[j].seccion<<setw(30)<<datosProf[j].grado
                 <<egreso<<endl;
         egresoTotal = egresoTotal + egreso;
    }
    imprimirLinea(archRep, '-', 300);
    archRep<<"Total de egresos por Sueldos: "<<egresoTotal<<endl;
    imprimirLinea(archRep, '=', 300);
    balanceFinal = ingresoTotal - egresoTotal;
    archRep<<"Estado de las ganancias o perdidas: "<<balanceFinal<<endl;
    archRep<<"REcomendaciones: ";
    if (balanceFinal > 0){
        archRep<<"DEBE INVERTIR SUS GANANCIAS"<<endl;
    }
    else{
         archRep<<"DEBE CERRAR LA INSTITUCIÓN"<<endl;
    }
}

void imprimirLinea(ofstream&arch,char c,int cant){
    for(int i=0; i<=cant; i++){
        arch<<c;
    }
    arch<<endl;
}

void escribirNombre(int cod, int*codigoTodos, char**nombres, int&cTotal,ofstream&archRep){
    for(int i = 0; i<cTotal; i++){
        if(cod == codigoTodos[i]){
            archRep<<left<<nombres[i];
            break;
        }
    }
}
