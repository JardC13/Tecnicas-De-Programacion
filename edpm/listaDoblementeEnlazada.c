#include <stdio.h>
#include <stdlib.h>

typedef int ElementoLista;

typedef struct nodo
{
    struct nodo *ant;
    ElementoLista elemento;
    struct nodo *sig;
} Nodo;

typedef struct listaDE
{
    Nodo *cabeza;
} ListaDE;

void construirLista( ListaDE *pL )
{
    pL->cabeza = NULL;
}

int esListaVacia( ListaDE L )
{
    return L.cabeza == NULL;
}

Nodo* crearNuevoNodo( Nodo *ant, ElementoLista elemento, Nodo *sig )
{
    Nodo *pNuevoNodo;
    pNuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    pNuevoNodo->ant = ant;
    pNuevoNodo->elemento = elemento;
    pNuevoNodo->sig = sig;
    return pNuevoNodo;
}

void insertarComienzo( ListaDE *pL, ElementoLista elemento )
{
    Nodo *pNuevoNodo, *pPrimero;
    pNuevoNodo = crearNuevoNodo( NULL,elemento, pL->cabeza);
    if ( !esListaVacia(*pL) )
    {
        pPrimero = pL->cabeza;
        pPrimero->ant = pNuevoNodo;
    }
    pL->cabeza = pNuevoNodo;
}

void mostrar( ListaDE L )
{
    Nodo *pNodo;
    if ( esListaVacia( L) )
        printf("La lista esta vacia\n");
    else
    {
        pNodo = L.cabeza;
        while ( pNodo != NULL )
        {
            printf("%d ", pNodo->elemento);
            pNodo = pNodo->sig;
        }
        printf("\n");
    }
}

Nodo* obtenerUltimoNodo( ListaDE L )
{
    Nodo *pNodo, *pUltimo;
    pUltimo = NULL;
    pNodo = L.cabeza;
    while( pNodo != NULL )
    {
        pUltimo = pNodo;
        pNodo = pNodo->sig;
    }
    return pUltimo;
}

void mostrarReves( ListaDE L )
{
    Nodo *pNodo;
    if ( esListaVacia( L) )
        printf("La lista esta vacia\n");
    else
    {
        pNodo = obtenerUltimoNodo(L);
        while ( pNodo != NULL )
        {
            printf("%d ", pNodo->elemento);
            pNodo = pNodo->ant;
        }
        printf("\n");
    }
}

void insertarFinal(ListaDE *pL, ElementoLista elemento )
{
    Nodo *pNuevoNodo, *pUltimo;
    pUltimo = obtenerUltimoNodo(*pL);
    pNuevoNodo = crearNuevoNodo( pUltimo,elemento, NULL);
    if ( pUltimo == NULL )
        pL->cabeza = pNuevoNodo;
    else
        pUltimo->sig = pNuevoNodo;
}

Nodo* obtenerNodo(ListaDE L, ElementoLista valor)
{
    Nodo *pNodo;
    pNodo = L.cabeza;
    while ( pNodo != NULL )
    {
        if (valor == pNodo->elemento)
            break;
        pNodo = pNodo->sig;
    }
    return pNodo;
}

void eliminarNodo( ListaDE *pL, ElementoLista valor )
{
    Nodo *pNodoEliminar, *pAnterior, *pSiguiente;
    pNodoEliminar = obtenerNodo( *pL, valor);
    if ( pNodoEliminar == NULL )
        printf("%d no esta en la lista\n",valor);
    else
    {
        pAnterior = pNodoEliminar->ant;
        pSiguiente = pNodoEliminar->sig;
        if ( pAnterior == NULL )
            pL->cabeza = pSiguiente;
        else
            pAnterior->sig = pSiguiente;
        if ( pSiguiente != NULL )
            pSiguiente->ant = pAnterior;
        free(pNodoEliminar);
        printf("El nodo fue eliminado\n");
    }
}

void destruirLista( ListaDE *pL )
{
    Nodo *pNodo, *pAux;
    pNodo = pL->cabeza;
    while ( pNodo != NULL )
    {
        pAux = pNodo->sig;
        free(pNodo);
        pNodo = pAux;
    }
    pL->cabeza = NULL;
    printf("Todos los nodos han sido eliminados\n");
}

int main()
{
    ListaDE LD;
    construirLista(&LD);
    mostrar(LD);
    mostrarReves(LD);
    insertarComienzo( &LD, 56);
    mostrar(LD);
    mostrarReves(LD);
    insertarComienzo( &LD, 22);
    mostrar(LD);
    mostrarReves(LD);
    insertarComienzo( &LD, 83);
    mostrar(LD);
    mostrarReves(LD);
    insertarFinal( &LD, 91);
    mostrar(LD);
    mostrarReves(LD);
    insertarFinal( &LD, 32);
    mostrar(LD);
    mostrarReves(LD);
    eliminarNodo( &LD, 56 );
    mostrar(LD);
    mostrarReves(LD);
    eliminarNodo( &LD, 83 );
    mostrar(LD);
    mostrarReves(LD);
    eliminarNodo( &LD, 32 );
    mostrar(LD);
    mostrarReves(LD);
    destruirLista( &LD);
    mostrar(LD);
    mostrarReves(LD);
    return 0;
}
