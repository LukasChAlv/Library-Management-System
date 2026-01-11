#include "../include/tablaReserva.h"

// Se debe implementar mediante una tabla de dispersión abierta (hash)
 
struct nodoHash{
    int isbn;
    TColaDePrioridadReservas reservas;
    nodoHash* sig;
};

struct rep_tablaTablaReserva {
    nodoHash** tablaHash;
    int cantidad;
    int tope;
    int topeC;
};

//-----------------FUNCIONES AUXILIARES--------------
int hash(int isbn, int tamañoTabla){
    return isbn % tamañoTabla;
}
//--------------------------------------------------

 
TTablaReserva crearTTablaReserva(int max, int N){
    TTablaReserva nuevo = new rep_tablaTablaReserva;
    nuevo->tablaHash = new nodoHash* [max];
    for (int i = 0; i < max; i++){
        nuevo->tablaHash[i] = NULL;
    }
    nuevo->cantidad = 0;
    nuevo->tope = max;
    nuevo->topeC = N;
    return nuevo;
}


void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva){
    int pos = hash(isbn, tabla->tope);
    nodoHash* lista = tabla->tablaHash[pos];
    while (lista != NULL && lista->isbn != isbn)
        lista = lista->sig;
    if (lista == NULL){
        nodoHash* nuevo = new nodoHash;
        nuevo->isbn = isbn;
        nuevo->reservas = crearTColaDePrioridadReservas(tabla->topeC);
        nuevo->sig = tabla->tablaHash[pos];
        tabla->tablaHash[pos] = nuevo;
        tabla->cantidad++;
        lista = nuevo;
    }
    insertarTColaDePrioridadReservas(lista->reservas, reserva);
}


bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro) {
    int pos = hash(isbnLibro, tabla->tope);
    nodoHash* lista = tabla->tablaHash[pos];
    while (lista != NULL && lista->isbn != isbnLibro)
        lista = lista->sig;
    return (lista != NULL && estaTColaDePrioridadReservas(lista->reservas, ciSocio, isbnLibro));
}


TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn){
    int pos = hash(isbn, tabla->tope);
    nodoHash* lista = tabla->tablaHash[pos];
    while (lista != NULL && lista->isbn != isbn)
        lista = lista->sig;
    return lista->reservas;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn){
    int pos = hash(isbn, tabla->tope);
    nodoHash* lista = tabla->tablaHash[pos];
    while (lista != NULL && lista->isbn != isbn)
        lista = lista->sig;

    return prioritarioTColaDePrioridadReservas(lista->reservas);
}

void liberarTTablaReserva(TTablaReserva &tabla){
    for (int i = 0; i < tabla->tope; i++){
        nodoHash *aux = tabla->tablaHash[i];
        while (aux != NULL){
            nodoHash* sig = aux->sig;
            liberarTColaDePrioridadReservas(aux->reservas);
            delete aux;
            aux = sig;
        }
    }
    delete[] tabla->tablaHash;
    tabla->tablaHash = NULL;

    delete tabla;
    tabla = NULL;
}