#include <stdio.h>
#include <stdlib.h>

typedef int ElementoLista;

typedef struct nodo
{
    ElementoLista elemento;
    struct nodo *sig;
} Nodo;

typedef struct listaC
{
    Nodo *cabeza;
} ListaC;

void construirLista( ListaC *pL )
{
    pL->cabeza = NULL;
}

int esListaVacia( ListaC L )
{
    return L.cabeza == NULL;
}

Nodo* crearNuevoNodo( ElementoLista elemento, Nodo *sig )
{
    Nodo *pNuevoNodo;
    pNuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    pNuevoNodo->elemento = elemento;
    pNuevoNodo->sig = sig;
    return pNuevoNodo;
}


Nodo* obtenerUltimoNodo( ListaC L )
{
    Nodo *pNodo, *pUltimo;
    pUltimo = NULL;
    if ( !esListaVacia(L) )
    {
        pNodo = L.cabeza;
        do
        {
            pUltimo = pNodo;
            pNodo = pNodo->sig;
        } while ( pNodo != L.cabeza );
    }
    return pUltimo;
}

void insertarComienzo( ListaC *pL, ElementoLista elemento )
{
    Nodo *pNuevoNodo, *pUltimo;
    pNuevoNodo = crearNuevoNodo( elemento, pL->cabeza);
    pUltimo = obtenerUltimoNodo( *pL);
    if ( pUltimo == NULL )
        pNuevoNodo->sig = pNuevoNodo;
    else
        pUltimo->sig = pNuevoNodo;     
    pL->cabeza = pNuevoNodo;
}

void mostrar( ListaC L )
{
    Nodo *pNodo;
    if ( esListaVacia( L) )
        printf("La lista esta vacia\n");
    else
    {
        pNodo = L.cabeza;
        do
        {
            printf("%d ", pNodo->elemento);
            pNodo = pNodo->sig;
        } while ( pNodo != L.cabeza );
        printf("\n");
    }
}

void insertarFinal(ListaC *pL, ElementoLista elemento )
{
    Nodo *pNuevoNodo, *pUltimo;
    pNuevoNodo = crearNuevoNodo( elemento, pL->cabeza);
    pUltimo = obtenerUltimoNodo(*pL);
    if ( pUltimo == NULL )
    {
        pL->cabeza = pNuevoNodo;
        pNuevoNodo->sig = pNuevoNodo;
    }
    else
        pUltimo->sig = pNuevoNodo;
}

Nodo* obtenerNodo(ListaC L, ElementoLista valor)
{
    Nodo *pNodo;
    if ( !esListaVacia(L) )
    {
        pNodo = L.cabeza;
        do
        {
            if (valor == pNodo->elemento)
                return pNodo;
            pNodo = pNodo->sig;
        } while ( pNodo != L.cabeza );
    }
    return NULL;
}

Nodo* obtenerNodoAnterior( ListaC L, ElementoLista valor)
{
    Nodo *pNodo, *pAnterior;
    pAnterior = NULL;
    pNodo = L.cabeza;
    do
    {
        if ( pNodo->elemento == valor )
            break;
        pAnterior = pNodo;
        pNodo = pNodo->sig;
    } while ( pNodo != L.cabeza );
    return pAnterior;
}

void eliminarNodo( ListaC *pL, ElementoLista valor )
{
    Nodo *pNodoEliminar, *pAnterior, *pUltimo;
    pNodoEliminar = obtenerNodo( *pL, valor);
    if ( pNodoEliminar == NULL )
        printf("%d no esta en la lista\n",valor);
    else
    {
        pAnterior = obtenerNodoAnterior(*pL, valor);
        if ( pAnterior == NULL ) // se elimina el primero
        {
            if ( pNodoEliminar == pNodoEliminar->sig ) // solo hay un nodo
                pL->cabeza = NULL;
            else
            {   // hay varios nodos
                pUltimo = obtenerUltimoNodo(*pL);
                pUltimo->sig = pNodoEliminar->sig;
                pL->cabeza = pNodoEliminar->sig;
            }
        }
        else
            pAnterior->sig = pNodoEliminar->sig;
        free(pNodoEliminar);
        printf("El nodo fue eliminado\n");
    }
}

void destruirLista( ListaC *pL )
{
    Nodo *pNodo, *pAux;
    if ( !esListaVacia( *pL) )
    {
        pNodo = pL->cabeza;
        do
        {
            pAux = pNodo->sig;
            free(pNodo);
            pNodo = pAux;
        } while ( pNodo != pL->cabeza );
        pL->cabeza = NULL;
        printf("Todos los nodos han sido eliminados\n");
    }
}

int main()
{
    ListaC LC;
    construirLista( &LC);
    mostrar( LC);
    insertarComienzo( &LC, 56);
    mostrar( LC );
    insertarComienzo( &LC, 45);
    mostrar( LC );
    insertarFinal( &LC, 80);
    mostrar( LC );
    insertarFinal( &LC, 34);
    mostrar( LC );
    /*eliminarNodo( &LC, 45);
    mostrar(LC);
    eliminarNodo( &LC, 80);
    mostrar(LC);
    eliminarNodo( &LC, 34);
    mostrar(LC);
    eliminarNodo( &LC, 56);
    mostrar(LC);*/
    destruirLista( &LC);
    mostrar(LC);
    return 0;
}
