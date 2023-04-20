/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include <cstring>
#include "Funciones.h"
#define TAM_LINE 500
#define MAX_CAR 200
void elaborarReporte(){
    int dd, mm, aa;
    char c;
    ofstream archRep ("ReportePreprocesamiento.txt", ios::out); 
    if(not archRep.is_open()){
        cout<<"ERROR: ReportePreprocesamineto.txt";
        exit(1);
    }
    ifstream archCom ("Comentarios.txt", ios::in);
    if(not archCom.is_open()){
        cout<<"ERROR: Comentarios.txt";
        exit(1);
    }
    ifstream archPais ("Paises.txt", ios::in); 
    if(not archPais.is_open()){
        cout<<"ERROR: Paises.txt";
        exit(1);
    }
    archRep<<setw(250)<<"@TikTok_tp"<<endl;
    imprimirLinea(archRep, '=', TAM_LINE);
    while(true){
        archCom>>dd;
        if(archCom.eof()) break;
        archCom>>c>>mm>>c>>aa;
        imprimirCabecera(archRep, dd, mm, aa);
        leerEImprimirComentariosYUsuarios(archRep, archCom, archPais);
        imprimirLinea(archRep, '=', TAM_LINE);
    }
}

void imprimirLinea(ofstream&arch, char c, int cant){
    for(int i=0; i<=cant; i++){
        arch<<c;
    }
    arch<<endl;
}

void imprimirCabecera(ofstream&archRep,int dd,int mm,int aa){
    char c = '/';
    archRep.fill('0');
    archRep<<"Fecha del TikTok: "<<setw(2)<<dd<<c<<setw(2)<<mm<<c<<aa<<endl<<endl;
    archRep.fill(' ');
    archRep<<left<<setw(130)<<"Comentario"<<setw(10)<<"long"
            <<setw(25)<<"Pais"<<setw(15)<<"Long"<<setw(130)<<"Transformacion 1"
            <<setw(10)<<"Long"<<setw(20)<<"Transformacion 2"<<setw(15)<<"long"<<endl;
    imprimirLinea(archRep, '-', TAM_LINE);
}

void leerEImprimirComentariosYUsuarios(ofstream&archRep, ifstream&archCom,ifstream&archPais){
    int pais, cod, nLikes;
    char c, car, comentario[MAX_CAR];
    while(true){
        archCom>>pais>>c>>cod>>comentario>>nLikes;
        imprimirComentario1(archRep, comentario);
        imprimirPais1(archRep, archPais, pais);
        imprimirComentario2(archRep, comentario);
        imprimriPais2(archRep, archPais, pais);
        car = archCom.get();
        if(car == '\n') break;
    }
}

void imprimirComentario1(ofstream&archRep,char*comentario){
    char copia[MAX_CAR];
    int tam;
    strcpy(copia, comentario);
    eliminarSubGuion(copia);
    tam = strlen(copia);
    archRep<<left<<setw(130)<<copia<<setw(10)<<tam;
}
void eliminarSubGuion(char*copia){
    for(int i=0; copia[i]; i++){
        if(copia[i] == '_'){
            copia[i]=' ';
        }
    }
}

void imprimirPais1(ofstream&archRep,ifstream&archPais,int pais){
    char nombrePais[MAX_CAR];
    int tam;
    buscarPais(archPais, pais, nombrePais);
    tam = strlen(nombrePais);
    archRep<<left<<setw(25)<<nombrePais<<setw(15)<<tam;
    
}

void buscarPais(ifstream&archPais,int pais, char*nombrePais){
    int codPais;
    archPais.clear();
    archPais.seekg(0, ios::beg);
    while(1){
        archPais>>codPais;
        if(codPais == pais){
            archPais>>nombrePais;
            break;
        }
        else{
            archPais.ignore(100, '\n');
            archPais>>ws;
        }
    }
}

void imprimirComentario2(ofstream&archRep,char*comentario){
    char copia[MAX_CAR];
    int tam;
    strcpy(copia, comentario);
    eliminarSegundaPalabra(copia);
    tam = strlen (copia);
    archRep<<left<<setw(130)<<copia<<setw(10)<<tam;
}

void eliminarSegundaPalabra(char * copia){
    char  auxiliar[MAX_CAR];
    bool identificadorSegPal=1;
    int i=0, j=0, tam;
    tam = strlen(copia);
    while(i<=tam){
        if (copia[i] == '_' and identificadorSegPal == 1){
            i++;
            while(1){
                if(copia[i] == '_') break;
                i++;
            }
            auxiliar[j]='*';
            j++;
            identificadorSegPal=0;
            i++;
        }
        auxiliar[j] = copia[i];
        i++;
        j++;
    }
    strcpy(copia, auxiliar);
}

void imprimriPais2(ofstream&archRep,ifstream&archPais,int pais){
    char nombrePais[MAX_CAR];
    int tam;
    buscarPais(archPais, pais, nombrePais);
    reducirNombrePais(nombrePais);
    tam = strlen(nombrePais);
    archRep<<left<<setw(20)<<nombrePais<<setw(15)<<tam<<endl;
}

void reducirNombrePais(char*nombrePais){
    char auxiliar[MAX_CAR], c;
    //solo consideramos hasta 3 caracteres porque se nos indica en el ejercicio 
    for (int i=0; i<3; i++){
        if('A' <= nombrePais[i] and nombrePais[i]<= 'Z'){
            auxiliar[i] = nombrePais[i] + ('a'-'A');
        }
        else{
            auxiliar[i] = nombrePais[i];
        }
    }
    strcpy(nombrePais, auxiliar);
}