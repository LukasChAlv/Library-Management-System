
#include "../include/agGeneros.h"
#include <assert.h>

  
struct rep_agGeneros {
  int idGenero;
  char nombreGenero[MAX_NOMBRE];
  TAGGeneros pH;
  TAGGeneros sH; 
};

TAGGeneros crearTAGGeneros(){
  return NULL;
}

//FUNCION AUXILIAR PARA BUSCAR IDS EN EL AG
TAGGeneros buscar(TAGGeneros arbolGeneros, int idpadre){
  if (arbolGeneros == NULL) 
    return NULL;

  if (arbolGeneros->idGenero == idpadre) 
    return arbolGeneros;

  TAGGeneros existe = buscar(arbolGeneros->pH, idpadre);
  if (existe != NULL)
    return existe;

  return buscar(arbolGeneros->sH, idpadre);
}


void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
  TAGGeneros nuevo = crearTAGGeneros();
  nuevo = new rep_agGeneros;
  nuevo->idGenero = idGenero;
  strcpy(nuevo->nombreGenero, nombreGenero);
  nuevo->pH = NULL;
  nuevo->sH = NULL;

  if (idGeneroPadre == -1) {
    arbolGeneros = nuevo;
    return;
  }

  TAGGeneros padre = buscar(arbolGeneros, idGeneroPadre);
  
  if (padre == NULL){
    delete nuevo;
    return;
  }
  nuevo->sH = padre->pH;
  padre->pH = nuevo;

}

//FUNCION AUXILIAR PARA PODER IMPRIMIR SIN REPETIR Y ERRORES DE ESPACIO
void imprimirTAGGenerosAUX(TAGGeneros arbolGeneros, int nivel) {
  if (arbolGeneros == NULL) return;

  for (int i = 0; i < nivel; i++) 
    printf("    ");

  printf("%d - %s\n", arbolGeneros->idGenero, arbolGeneros->nombreGenero);

  imprimirTAGGenerosAUX(arbolGeneros->pH, nivel + 1);
  imprimirTAGGenerosAUX(arbolGeneros->sH, nivel);
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros){
  printf("Árbol de géneros:\n");
  imprimirTAGGenerosAUX(arbolGeneros, 0);
}

void liberarTAGGeneros(TAGGeneros &arbolGeneros){
  if (arbolGeneros == NULL) return;

  liberarTAGGeneros(arbolGeneros->pH);
  liberarTAGGeneros(arbolGeneros->sH);

  delete arbolGeneros;
  arbolGeneros = NULL;
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  if (arbolGeneros == NULL) 
    return false;

  if (arbolGeneros->idGenero == idGenero) 
    return true;

  if (existeGeneroTAGGeneros(arbolGeneros->pH, idGenero))
    return true;
  
  return existeGeneroTAGGeneros(arbolGeneros->sH, idGenero);
}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  TAGGeneros aux = buscar(arbolGeneros, idGenero);
  if (aux == NULL)
    return NULL;
  return aux->nombreGenero;
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
  else { 
    nat altHijo = 1+alturaTAGGeneros(arbolGeneros->pH); 
    nat altHerm = alturaTAGGeneros(arbolGeneros->sH);
    
    if (altHijo > altHerm)
      return altHijo;
    else
      return altHerm;
  }
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
   
  return cantidadTAGGeneros(arbolGeneros->pH) + cantidadTAGGeneros(arbolGeneros->sH) + 1;
}

TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
  return buscar(arbolGeneros, idGenero);
}

//FUNCION AUXILIAR PARA OBTENER TODO EL SUBARBOL---
void subarbol(TAGGeneros arbol, TConjuntoGeneros conjunto) {
  if (arbol == NULL) return;

  insertarTConjuntoGeneros(conjunto, arbol->idGenero);

  subarbol(arbol->pH, conjunto);

  subarbol(arbol->sH, conjunto);
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
  TAGGeneros aux = buscar(arbolGeneros, idGenero);
  if (aux == NULL) return NULL;

  TConjuntoGeneros nuevo = crearTConjuntoGeneros(obtenerMaxTAGGeneros(aux) + 1);

  subarbol(aux, nuevo);

  return nuevo;
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
  if (arbolGeneros == NULL) return 0;

  int idHijo = obtenerMaxTAGGeneros(arbolGeneros->pH);
  int idHerm = obtenerMaxTAGGeneros(arbolGeneros->sH);

  int max;
  if (idHijo > idHerm) 
    max = idHijo;
  else
    max = idHerm;

  if (arbolGeneros->idGenero > max) 
    return arbolGeneros->idGenero;
  else 
    return max;
}

//FUNCION AUXILIAR PARA ELIMINAR TODO DEBAJO DE UN NODO
void eliminarSub(TAGGeneros &arbolGeneros) {
  if (arbolGeneros != NULL) {
    eliminarSub(arbolGeneros->pH);
    eliminarSub(arbolGeneros->sH);
    delete arbolGeneros;
    arbolGeneros = NULL;
  }
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero){
  if (arbolGeneros != NULL) {
    if (arbolGeneros->idGenero == idGenero) {
      TAGGeneros borrar = arbolGeneros;
      arbolGeneros = arbolGeneros->sH;
      eliminarSub(borrar->pH);
      delete borrar;
    }
    else {
      removerGeneroTAGGeneros(arbolGeneros->pH, idGenero);
      removerGeneroTAGGeneros(arbolGeneros->sH, idGenero);
    }
  } 
}
