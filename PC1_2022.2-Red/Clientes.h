/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Clientes.h
 * Author: 51953
 *
 * Created on 20 de abril de 2023, 12:44 AM
 */

#ifndef CLIENTES_H
#define CLIENTES_H
#include "Clientes.h"

struct persona
{
    char tipoCliente;
    int dni;
    char nombre[100];
    double saldo;
};

typedef struct nodo
{
    persona per;
    struct nodo *sig;
}Nodo;

typedef struct 
{
    Nodo *cabeza;
    int longitud;
}Lista;

void crearLista(Lista);
bool esListaVacia(Lista);
Nodo* crearNodo(char tipoCliente, int dni, const char *nombre, double saldo, Nodo *nS);
void anhadirInicio(char tipoCliente, int dni, const char *nombre, double saldo, Lista &L);
Nodo* buscarUltNodo (Lista L);
void anhadirFinal(char tipoCliente, int dni, const char *nombre, double saldo, Lista &L);
void ordenarLista(Lista &L);
Nodo* buscarPersona(Lista L, int dni);
void actualizarSaldo(Lista L, double dni, double saldoActualizar);
Nodo* ubicarAnteriorNodo(Lista L, int dni);
void eliminarcliente(Lista &L,int dni);
void mostrarLista(Lista L);

#endif /* CLIENTES_H */

