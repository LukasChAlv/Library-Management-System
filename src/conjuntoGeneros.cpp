#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros{
  bool *generos;
  int cantMax;
  int cantidad;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  TConjuntoGeneros nuevo = new rep_conjuntogeneros;
  nuevo->generos = new bool[cantMax];
  nuevo->cantMax = cantMax;
  nuevo->cantidad = 0;

  for (int i = 0; i < cantMax; i++) 
    nuevo->generos[i] = false;

  return nuevo;    
}

bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantidad == 0;
}

void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (0 <= id && id < c->cantMax && !c->generos[id]) {
    c->generos[id] = true;
    c->cantidad++;  
  }
}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (0 <= id && id < c->cantMax && c->generos[id]){
    c->generos[id] = false;
    c->cantidad--;
  }
}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  if (0 <= id && id < c->cantMax)
    return c->generos[id];
  else
    return false;
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantidad;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantMax;
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c){
  int elementoImp = 0;

  for (int i = 0; i < c->cantMax; i++) {
    if (c->generos[i]) {
      printf("%d", i);
      elementoImp++;
      if (elementoImp < c->cantidad) 
        printf(" ");
    }
  }
  printf("\n");
}

void liberarTConjuntoGeneros(TConjuntoGeneros &c){
  delete []c->generos;
  c->generos = NULL;

  delete c;
  c = NULL;
}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros nuevo = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->generos[i] || c2->generos[i]) 
      insertarTConjuntoGeneros(nuevo, i);
  }
  return nuevo;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros nuevo = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->generos[i] && c2->generos[i]) 
      insertarTConjuntoGeneros(nuevo, i);
  }
  return nuevo;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros nuevo = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->generos[i] && !c2->generos[i]) 
      insertarTConjuntoGeneros(nuevo, i);
  }
  return nuevo;
}
