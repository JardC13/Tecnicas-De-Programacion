/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Clientes.h"


using namespace std;

void crearLista(Lista &pL)
{
    pL.cabeza = NULL;
    pL.longitud = 0;
};

bool esListaVacia(Lista L)
{
    if(L.longitud == 0) return true;
    return false;
};

Nodo* crearNodo(char tipoCliente, int dni, const char *nombre, double saldo, Nodo *nS)
{
    Nodo *p;
    p = new Nodo;
    p->per.tipoCliente = tipoCliente;
    p->per.dni = dni;
    strcpy(p->per.nombre,nombre);
    p->per.saldo = saldo;
    p->sig = nS;
    return p;
};

void anhadirInicio(char tipoCliente, int dni, const char *nombre, double saldo, Lista &L)
{
    Nodo *p;
    p = crearNodo(tipoCliente, dni, nombre,  saldo, L.cabeza);
    L.cabeza = p;
    L.longitud++;
};

Nodo* buscarUltNodo (Lista L)
{
    Nodo *p;
    if(esListaVacia(L) == true) return NULL;
    p = L.cabeza;
    for(int i=0; i<L.longitud-1;i++)
    {
        p=p->sig;
    }
    return p;
};

void anhadirFinal(char tipoCliente, int dni, const char *nombre, double saldo, Lista &L)
{
    Nodo *p, *pUlt;
    p = crearNodo(tipoCliente, dni, nombre, saldo, NULL);
    if(esListaVacia(L) == true)
    {
        L.cabeza = p;
    }
    else
    {
        pUlt = buscarUltNodo(L);
        pUlt->sig = p;
    }
    L.longitud++;
};

void ordenarLista(Lista &L)
{
    Nodo *pI, *pJ;
    persona aux;
    if(esListaVacia(L) == true) cout << "La lista no posee elementos que ordenar"<<endl;
    else
    {
       pI = L.cabeza; 
       for(int i=1; i<=L.longitud-1;i++)
       {
           pJ = pI->sig;
           for(int j = i+1; j<=L.longitud; j++){
               if(pI->per.saldo > pJ->per.saldo)
               {
                   aux = pI->per;
                   pI->per = pJ->per;
                   pJ->per = aux;
               }
               pJ = pJ->sig;
           }
           pI = pI->sig;
       }
    }  
};

Nodo* buscarPersona(Lista L, int dni)
{
    Nodo *p;
    if(esListaVacia(L))return NULL;
    p=L.cabeza;
    for(int i=0;i<L.longitud;i++){
        if(p->per.dni == dni)return p;
        p=p->sig;
    }
    return NULL;
};

void actualizarSaldo(Lista L, double dni, double saldoActualizar)
{
    Nodo *p;
    p = buscarPersona(L, dni);
    if(p = NULL) cout<<"El cliente del cual se busca actualizar su saldo no se encuentra en nuestros datos"<<endl;
    else
    {
        p->per.saldo = saldoActualizar;
    }
};

Nodo* ubicarAnteriorNodo(Lista L, int dni)
{
    Nodo*p, *pA;
    pA= NULL;
    p=L.cabeza;
    for (int i=1;i<=L.longitud;i++){
        if(p->per.dni == dni)return pA;
        pA=p;
        p=p->sig;
    }
    return NULL;
};

void eliminarcliente(Lista &L,int dni)
{
    Nodo *p, *pA;
    p = buscarPersona(L,dni);
    if (p==NULL) cout<<"El dato a eliminar no existe y no se puede eliminar: "<<endl;
    else
    {
        pA = ubicarAnteriorNodo(L,dni);
        if(pA == NULL){
            L.cabeza=p->sig;
        }else{
            pA->sig = p->sig;
         }
        L.longitud--;
        delete p;
    }
};

void mostrarLista(Lista L)
{
    Nodo *p;
    p = L.cabeza;
    if(esListaVacia(L)){
        cout<<"Lista Vacia"<<endl;
    }else{
        while(true){
            if(p==NULL)break;
            cout<<"Informacion del cliente: "<<endl;
            cout<<"DNI: "<<p->per.dni<<endl;
            cout<<"Nombre: "<<p->per.nombre<<endl;
            cout<<"Tipo cliente: "<<p->per.tipoCliente<<endl;
            cout<<"Saldo: "<<p->per.saldo<<endl;
            p=p->sig;
        }
    }
};



