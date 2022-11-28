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
 * Creado el 27 de noviembre de 2022, 07:47 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "FuncionesBinarias.h"

int main(int argc, char** argv) {
    crearStockBin("StockDeProductos.csv", "StockDeProductos.bin");
    mostrarStockBin("StockDeProductos.bin");
    crearPedidosBin("Pedidos.txt", "PedidosPorInternet.bin");
    mostrarPedidosBin("PedidosPorInternet.bin");
    actualizarPedido("DetalleDeLosPedidos.txt", "StockDeProductos.bin",
    "PedidosPorInternet.bin");
    mostrarReporte("PedidosPorInternet.bin", "ReporteDePedidos.txt");
    return 0;
}


