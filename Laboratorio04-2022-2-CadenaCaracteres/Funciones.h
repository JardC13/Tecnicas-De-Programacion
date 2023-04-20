/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Funciones.h
 * Author: aml
 *
 * Created on 25 de octubre de 2022, 11:09 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Funciones.h"

void elaborarReporte();
void imprimirLinea(ofstream&, char, int);
void imprimirCabecera(ofstream&,int ,int ,int );
void leerEImprimirComentariosYUsuarios(ofstream&, ifstream&,ifstream&);
void imprimirComentario1(ofstream&,char*);
void eliminarSubGuion(char*);
void imprimirPais1(ofstream&,ifstream&,int );
void buscarPais(ifstream&,int , char*);
void imprimirComentario2(ofstream&,char*);
void eliminarSegundaPalabra(char * );
void imprimriPais2(ofstream&,ifstream&,int );
void reducirNombrePais(char*);
#endif /* FUNCIONES_H */

