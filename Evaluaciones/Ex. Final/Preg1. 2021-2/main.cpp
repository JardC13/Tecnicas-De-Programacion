/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   main.cpp
 * Autor: Jared Dalmiro Chávez Pozo
 * Código: 20213283
 * Horario: 0432
 * Creado el 27 de noviembre de 2022, 09:17 PM
 */

#include <iostream>
#include <fstream> 
#include <iomanip>
using namespace std;
#include <cstring>
#include "Productos.h" 
#include "Pedidos.h"
#include "funcionesCadenas.h"
#include "funcionesDeEstructuras.h"
#define MAX_PRODUCTOS 50
#define MAX_PEDIDOS 50

int main(int argc, char** argv) {
    struct StockProd * productos = new struct StockProd[MAX_PRODUCTOS];
    struct Pedidos * pedidos = new struct Pedidos[MAX_PEDIDOS];
    int numProd, numPed;
    
    llenarProductos("StockDeProductos.csv", productos, numProd);
    probarllenarProductos(productos, numProd, "ReportePruebaProductos.txt");
    
    llenarPedidos("Pedidos.txt", pedidos, numPed);
    probarPedidos(pedidos, numPed,"ReportePruebaPedidos.txt");
    
    completarPedidos("DetalleDeLosPedidos.txt", pedidos, numPed, productos,
            numProd);
    reporteDePedidosFinal(pedidos,numPed,"ReporteDePedidos.txt");
    return 0;
}
