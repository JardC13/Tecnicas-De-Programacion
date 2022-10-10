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
 * Creado el 7 de octubre de 2022, 01:53 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>        
#include <fstream>
#include <valarray>

using namespace std;

#include "Funciones.h"
#define MAX_CAR_LIN 90
#define MAX_CAR_PLATO 25

void generarReporteCostos(ifstream & archListPrec, ifstream & archPlatos,
    ifstream & archPlatPrep, ofstream & archRep){
     int codigoPlato, cantPlato; // codigo y cantidad del plato
    int nroPlato = 1; //contador para mostrar en reporte
    double costoTotal = 0.0; //acumulador de costo

 //imprimir encabezado
    imprimirEncabezado(archListPrec, archRep);
    imprimirLinea(archRep, '-', MAX_CAR_LIN);

 //Primero leer el archivo de los platos a preparar
    while(true){
        archPlatPrep>>codigoPlato; //leer codigo
        archPlatPrep>>cantPlato; //leer cantidad
        if (archPlatPrep.eof()) break; //Validar el fin de archivo
        //acumular los costos de los platos
        costoTotal += calcularCostoEImprPlato(archPlatos, archListPrec, archRep,
        nroPlato, codigoPlato, cantPlato);
        nroPlato++;
        }
    imprimirLinea(archRep, '-', MAX_CAR_LIN);
    archRep<<"Costo total: "<<costoTotal<<endl; //Total final
    imprimirLinea(archRep, '=', MAX_CAR_LIN);
 }

 void imprimirEncabezado(ifstream & archListPrec, ofstream & archRep){
    archRep<<"COSTOS DE LOS PLATOS OFRECIDOS"<<endl;
    imprimirLinea(archRep, '=', MAX_CAR_LIN);
    imprimirProveedor(archListPrec, archRep);
    imprimirLinea(archRep, '-', MAX_CAR_LIN);
    archRep<<setw(10)<<"Plato"
    <<setw(33)<<"Cantidad a elaborar"
    <<setw(22)<<"Costo por plato"
    <<setw(18)<<"Costo Total"<<endl;
 }

 void imprimirProveedor(ifstream & archListPrec, ofstream & archRep){
    char c;
     while(true){
    c = archListPrec.get();
    archRep.put(c);
    if (c == '\n') break; //terminar en el cambio de línea
    }
 }

 double calcularCostoEImprPlato(ifstream & archPlatos, ifstream & archListPrec,
    ofstream & archRep, int nroPlato, int codigoPlatoBusco, int cant){
    int codPlato;
    double costo = 0.0;
    //Seguidamente leer del archivo de Platos
    //Como va recorrer varias veces el archivo
    archPlatos.clear(); //restablece el fin de archivo para la siguiente entrada
    archPlatos.seekg(0, ios::beg); //colocar el cursos en el inicio del archivo
    while(true){
        archPlatos>>codPlato; //leer codigo del plato
        if(archPlatos.eof()) break; //valida el fin de archivo
        if (codPlato == codigoPlatoBusco){ //son iguales
            imprimirPlato(nroPlato, archPlatos, archRep); //mostrar nombre
            //calcular el precio e imprimir los datos respectivos
            costo = calcularPrecioEImprDatos(cant, archPlatos, archListPrec,
            archRep);
            break;
        }
        else while(archPlatos.get() !='\n');
    }
 return costo;
 }

 void imprimirPlato(int nroPlato, ifstream & archPlatos, ofstream & archRep){
    char c;
    int n = 0, numBlancos;

    archRep<<setw(2)<<nroPlato<<".- "; //numeración del plato
    while(archPlatos.get() != '('); //avanzo hasta el inicio de '('
    while(true) {
        c = archPlatos.get(); //leo el caracter
        if (c == ')') break; //si llegue a ')' salgo
        archRep.put(c); //imprimo caracter en el reporte
        n++; //cuenta la cantidad de dígitos que imprime
    }
    numBlancos = MAX_CAR_PLATO - n; //número de blancos que debe colocar
    for(int i=0; i<numBlancos; i++) archRep.put(' '); //imprime los blancos
 }

 double calcularPrecioEImprDatos(int cant, ifstream & archPlatos,
    ifstream & archListPrec, ofstream & archRep){
    int codIngrediente;
    double cantRequerida, precioIngrediente, costoPorPlato = 0.0;

    while(true){
        archPlatos>>codIngrediente; //leer el codigo del ingrediente
        archPlatos>>cantRequerida; //leer la cantidad requerida
        precioIngrediente = buscarPrecio(codIngrediente, archListPrec);
        if (precioIngrediente < 0){//no lo encontró
        //mostrar mensaje
             archRep<<"No se puede calcular por falta de producto: "
            <<codIngrediente<<endl;
            return 0.0;//retornar cero si la búsqueda no fue exitosa
        }
        else costoPorPlato += precioIngrediente*cantRequerida; //acumula el
        //costo de cada ingrediente
        if(archPlatos.get() == '\n') break; //valida el cambio de línea
    }

    archRep<<fixed; // obliga a mostrar un número de dígitos después
    //del punto flotante
    archRep.precision(2); //dígitos a mostrar
    archRep<<setw(5)<<cant
    <<setw(25)<<costoPorPlato
    <<setw(20)<<cant*costoPorPlato<<endl;
    return cant*costoPorPlato;
 }

 double buscarPrecio(int codIngredienteBusco, ifstream & archListPrec){

    int codigoIngrediente;
    double precio;
 //Tercero leo del archivo de lista de Precios
 //Como va recorrer varias veces el archivo
    archListPrec.clear();//restablece el fin de archivo para la siguiente entrada
    archListPrec.seekg(0, ios::beg);//colocar el cursos en el inicio del archivo

    while(archListPrec.get() !='\n');//Avanzo hasta el cambio de línea para
 //saltar el nombre de la bodega
    while(true){
        archListPrec>>codigoIngrediente;//leer el codigo del ingrediente
        if(archListPrec.eof()) break;
        if(codigoIngrediente == codIngredienteBusco){// son iguales
            while(archListPrec.get() != ']'); //salta la lectura del ingrediente
            archListPrec>>precio;//lee el precio
            return precio;
        }
        else while(archListPrec.get() !='\n'); //avanza hasta el cambio de línea
    }
    return -1;//retornar -1 si la búsqueda no fue exitosa
 }

 void imprimirLinea(ofstream & archRep, char car, int maxCar){
    for(int i=0; i<maxCar; i++){
        archRep.put(car);
        }
    archRep<<endl;
 }