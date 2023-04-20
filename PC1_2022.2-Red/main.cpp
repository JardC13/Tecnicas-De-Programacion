/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: 51953
 *
 * Created on 20 de abril de 2023, 12:40 AM
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Clientes.h"
using namespace std;


int main(int argc, char** argv) {
    Lista L1;
    crearLista(L1);
    anhadirInicio('C', 233123, "Felipe_Fernandez", 3213.45, L1);
    anhadirInicio('V', 124454, "Jared_Juarez", 3973.90, L1);
    anhadirInicio('C', 123785, "Carlos_Caceda", 213.87, L1);
    anhadirInicio('V', 876568, "Marco_Mendoza", 97886.92, L1);
    anhadirInicio('C', 256775, "Luis_Li", 6765.9, L1);
    mostrarLista(L1);
    ordenarLista(L1);
    mostrarLista(L1);
    return 0;   
}

