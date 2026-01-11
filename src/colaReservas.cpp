#include "../include/colaReservas.h"
 
struct nodo {
  TReserva reserva;
  nodo *sig;
};

struct rep_colaReservas {
  nodo *primero;
  nodo *final;
  int cantidad;
};

TColaReservas crearTColaReservas(){
  TColaReservas nuevo = new rep_colaReservas;
  nuevo->primero = NULL;
  nuevo->final = NULL;
  nuevo->cantidad = 0;
  return nuevo;
}

void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva){
  nodo *nuevo = new nodo;
  nuevo->reserva = reserva;
  nuevo->sig = NULL;

  if (colaReservas->primero == NULL) 
    colaReservas->primero = nuevo;
  else
    colaReservas->final->sig = nuevo;

  colaReservas->final = nuevo;
  colaReservas->cantidad++;
}

void desencolarTColaReservas(TColaReservas &colaReservas) {
  nodo *quitar = colaReservas->primero;
  colaReservas->primero = colaReservas->primero->sig;

  if (colaReservas->primero == NULL)
    colaReservas->final = NULL;

  liberarTReserva(quitar->reserva);
  delete quitar;
  colaReservas->cantidad--;
}

TReserva frenteTColaReservas(TColaReservas colaReservas) {
    return colaReservas->primero->reserva;
}

nat cantidadTColaReservas(TColaReservas colaReservas){
    return colaReservas->cantidad;
}

void imprimirTColaReservas(TColaReservas colaReservas){
  printf("Cola de Reservas:\n");
  
  nodo *aux = colaReservas->primero;
  while (aux != NULL){
    imprimirTReserva(aux->reserva);
    aux = aux->sig;
  }

}

void liberarTColaReservas(TColaReservas &colaReservas){
  if (colaReservas != NULL) {
    nodo *aux = colaReservas->primero;
    while (aux != NULL) {
      nodo *borrar = aux;
      aux = aux->sig;
      liberarTReserva(borrar->reserva);
      delete borrar;
    }

    delete colaReservas;
    colaReservas = NULL;
  }
}

void liberarTColaReservasSoloEstructura(TColaReservas &colaReservas){
  if (colaReservas != NULL) {
    nodo *aux = colaReservas->primero;
    while (aux != NULL) {
      nodo *borrar = aux;
      aux = aux->sig;
      delete borrar;
    }

    delete colaReservas;
    colaReservas = NULL;
  }
}

TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas) {
  nodo *quitar = colaReservas->primero;
  TReserva reserva = quitar->reserva;
  colaReservas->primero = colaReservas->primero->sig;

  if (colaReservas->primero == NULL)
    colaReservas->final = NULL;

  delete quitar;
  colaReservas->cantidad--;

  return reserva;
}
