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
 * Creado el 24 de octubre de 2022, 06:58 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Funciones.h"
void imprimirLinea(char , int , ofstream &);
void imprimirCabeceraTikTok(ofstream &, int , int , int );
void imprimirCabecera(ofstream &);
void procesarReporte();
void leerEImprimirComentariosYUsuarios(ofstream&archReporte,ifstream&archComentarios,ifstream&archUsuarios);
void imprimirComentario1(ofstream&,char * );
void eliminarSubGuion(char *);
void imprimirUsuario1(ofstream&,ifstream&,int ,int  );
void buscarUsuario(ifstream&,int ,int, char * );
void imprimirComentario2(ofstream&,char *);
void unirComentario(char * );
void imprimirUsuario2(ofstream&,ifstream&,int ,int );
void quitarArroba(char * );
#endif /* FUNCIONES_H */

