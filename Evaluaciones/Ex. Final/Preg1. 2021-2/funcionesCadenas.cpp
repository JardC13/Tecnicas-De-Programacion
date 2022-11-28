/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   funcionesCadenas.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:59 PM
 */

#include <iostream>
#include <iomanip>        
#include <fstream>
#include <cstring>
using namespace std;

char *leeCadenaExacta(ifstream&arch){
    
    char palabra[100], *cad;
    arch.getline(palabra, 500, ',');
    cad = new char[strlen(palabra)+1];
    strcpy(cad, palabra);
    return cad;
}