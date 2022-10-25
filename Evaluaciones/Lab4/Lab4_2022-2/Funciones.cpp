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
 * Creado el 24 de octubre de 2022, 06:58 PM
 */

#include <iostream>
#include <iomanip>        
#include <fstream>

using namespace std;
#include <cstring>
#include "funciones.h"
#define TAMLINEA 500
#define MAXCAR 100
void imprimirLinea(char c, int n, ofstream &archReporte){
    for(int i = 0; i <= n; i++)
        archReporte.put(c);
    archReporte.put('\n');
}

void procesarReporte(){
    int dd, mm, aa;
    char c;
    //declaramos los archivos de texto
    ifstream archComentarios("Comentarios.txt", ios::in);
    if(not archComentarios.is_open()){
        cout << "ERROR: Comentarios.txt" << endl;
        exit(1);
    }
    ifstream archUsuarios("Usuarios.txt", ios::in);
    if(not archUsuarios.is_open()){
        cout << "ERROR: Usuarios.txt" << endl;
        exit(1);
    }
    ofstream archReporte("Reporte.txt", ios::out);
    if(not archReporte.is_open()){
        cout << "ERROR: Reporte.txt" << endl;
        exit(1);
    }
    //llamada a funcion para imprimir la cabecera del reporte
    imprimirCabecera(archReporte);
    while(1){
        archComentarios>>dd;
        if(archComentarios.eof()) break;
        archComentarios>>c>>mm>>c>>aa;
        imprimirCabeceraTikTok(archReporte, dd, mm, aa);
        leerEImprimirComentariosYUsuarios(archReporte, archComentarios, archUsuarios);
        imprimirLinea('-', TAMLINEA, archReporte);
    }
}

void imprimirCabeceraTikTok(ofstream &archReporte, int dd, int mm, int aa){
    char extra = '/';
    archReporte.fill('0');
    archReporte << "Fecha del TikTok: " << setw(2) << dd << extra << setw(2)
            << mm << extra << aa << endl << endl;
    archReporte.fill(' ');
    archReporte << left << setw(130) << "Comentario" << setw(10) << "Long" << 
            setw(15) << "Autor" << setw(10) << "Long" << setw(130) << 
            "Transformacion 1" << setw(10) << "Long" << setw(20) << 
            "Transformacion 2" << setw(10) << "Long" << endl;
    //llamada a funcion que imprime una linea de -
    imprimirLinea('-', TAMLINEA, archReporte);
}

void imprimirCabecera(ofstream &archReporte){
    archReporte << setw(165) << " " << "@TikTok_tp" << endl;
    //llamada a funcion para imprimir una linea de =
    imprimirLinea('=', TAMLINEA, archReporte);
}

void leerEImprimirComentariosYUsuarios(ofstream&archReporte,ifstream&archComentarios,ifstream&archUsuarios){
    int id, cod, nLikes;
    char c, car = ' ', comentario[MAXCAR];
    while(1){
        archComentarios>>id>>c>>cod>>comentario>>nLikes;
        imprimirComentario1(archReporte, comentario);
        imprimirUsuario1(archReporte, archUsuarios, id, cod);
        imprimirComentario2(archReporte, comentario);
        imprimirUsuario2(archReporte, archUsuarios, id, cod);
        car = archComentarios.get();
        if(car == '\n') break;
    }
}

void imprimirComentario1(ofstream&archReporte,char * comentario){
    char copia[MAXCAR];
    int tam;
    strcpy(copia, comentario);
    eliminarSubGuion(copia);
    tam = strlen(copia);
    archReporte<<left<<setw(130)<<copia<<setw(10)<<tam;
}

void eliminarSubGuion(char * copia){
    for(int i=0; copia[i]; i++){
        if (copia[i] == '_'){
            copia[i] = ' ';
        }     
    }
}

void imprimirUsuario1(ofstream&archReporte,ifstream&archUsuarios,int id,int  cod){
    char  usuario[MAXCAR];
    int tam;
    buscarUsuario(archUsuarios, id, cod, usuario);
    tam = strlen(usuario);
    archReporte<<left<<setw(15)<<usuario<<setw(10)<<tam;
}

void buscarUsuario(ifstream&archUsuarios,int id,int cod,char * usuario){
    int id2, cod2, nS;
    char c;
    archUsuarios.clear();
    archUsuarios.seekg(0, ios::beg);
    while(1){
        archUsuarios>>id2;
        if (archUsuarios.eof()) break;
        archUsuarios>>c>>cod2;
        if(id == id2 and cod == cod2){
            archUsuarios>>usuario;
            break;
        }
        else{
            archUsuarios.ignore(100, '\n');
            archUsuarios>>ws;
        }
    }
}

void imprimirComentario2(ofstream&archReporte,char *comentario){
    char copia[MAXCAR];
    int tam;
    strcpy(copia, comentario);
    unirComentario(copia);
    tam = strlen(copia),
    archReporte<<left<<setw(130)<<copia<<setw(10)<<tam;        
}

void unirComentario(char * copia){
    int inicioP = 1, j = 0;
    char copia2[MAXCAR];
    for(int i = 0; copia[i]; i++){
        if (inicioP == 1){
            inicioP = 0;
            if ('a' <= copia[i] and copia[i] <= 'z'){
                copia2[j] = copia[i] - ('a'- 'A');
                j++;
            }
            else{
                copia2[j] = copia[i];
                j++;
            }
        }
        else{
            if (copia[i] != '_'){
                copia2[j] = copia[i];
                j++;
            }
            else{
                inicioP = 1;
            }
        }
    }
    strcpy(copia, copia2);
}

void imprimirUsuario2(ofstream&archReporte,ifstream&archUsuarios,int id,int cod){
    char copia[MAXCAR], usuario[MAXCAR];
    int tam;
    buscarUsuario(archUsuarios, id, cod, usuario);
    strcpy(copia, usuario);
    quitarArroba(copia);
    tam = strlen(copia);
    archReporte<<left<<setw(20)<<copia<<setw(10)<<tam<<endl;
    
}

void quitarArroba(char * copia){
    char copia2[MAXCAR];
   
    for(int i = 1, j=0; copia[i]; i++, j++){
        copia2[j] = copia[i];
        if ('a'<= copia[1] and copia[1]<='z'){
            copia2[0] = copia[1] - ('a'-'A');
        }
        
    }
    strcpy(copia, copia2);
}