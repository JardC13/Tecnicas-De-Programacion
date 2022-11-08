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
 * Creado el 8 de noviembre de 2022, 12:29 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void llenarDatos(char**,int*,int*,char**,char**,char**,int*,double*,double*,int&,struct DOCENTES *,int&, int&);
void leerYOrdenarNombre(char*,char*,char*,ifstream&);   
void leerAlumno(char*,char*,int&, double&, double&, ifstream&);
void leerProf(char*,char*,char*,char*,double&,ifstream&);
void llenar(struct DOCENTES*,int&,int ,char*,char*,char*,char*,char*,double&);
void ordenarAlumnos(int*,char**,char**,char**,int*,double*,double*,int&);
void CambiarI (int&, int&);
void CambiarD (double&, double&);
void CambiarC (char*&, char*&);
void imprimirReporte(char**,int*,int*,char**,char**,char**,int*,double*,double*,int&,struct DOCENTES *,int&, int&);
void imprimirLinea(ofstream&,char ,int );
void escribirNombre(int , int*, char**, int&,ofstream&);
#endif /* FUNCIONES_H */

