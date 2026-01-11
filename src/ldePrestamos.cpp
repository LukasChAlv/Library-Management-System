#include "../include/ldePrestamos.h"

struct nodoDoble{
    TPrestamo prestamo;
    nodoDoble *sig;
    nodoDoble *ant;
};

struct rep_ldePrestamos {
    nodoDoble *inicio;
    nodoDoble *final;
};

void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos){
    nodoDoble *borrar = ldePrestamos->inicio;

    while (borrar != NULL) {
        nodoDoble *aux = borrar->sig;
        liberarTPrestamoSoloEstructura(borrar->prestamo);
        delete borrar;
        borrar = aux;
    }

    ldePrestamos->inicio = NULL;
    ldePrestamos->final = NULL;

    delete ldePrestamos;
}

 
TLDEPrestamos crearTLDEPrestamosVacia(){
    TLDEPrestamos nuevo = new rep_ldePrestamos;
    nuevo->inicio = NULL;
    nuevo->final = NULL;
    return nuevo;
}

void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo){
    // CREAMOS EL NODO
    nodoDoble *nuevo = new nodoDoble;
    nuevo->prestamo = prestamo;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    // INSERTAMOS AL PRINCIPIO
    if (ldePrestamos->inicio == NULL) {
        ldePrestamos->inicio = nuevo;
        ldePrestamos->final = nuevo;
        return;
    } else if (compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(ldePrestamos->inicio->prestamo)) < 0) {
        nuevo->sig = ldePrestamos->inicio;
        ldePrestamos->inicio->ant = nuevo;
        ldePrestamos->inicio = nuevo;
        return;
    }

    // INSERTAR EN EL MEDIO
    nodoDoble *aux = ldePrestamos->inicio;
    while (aux->sig != NULL && compararTFechas(fechaRetiroTPrestamo(aux->sig->prestamo), fechaRetiroTPrestamo(prestamo)) <= 0) {
        aux = aux->sig;
    }
    if (aux->sig != NULL) {
        nuevo->ant = aux;
        nuevo->sig = aux->sig;
        aux->sig->ant = nuevo;
        aux->sig = nuevo;
        return;
    } 
    // INSERTAR AL FINAL
    else if (aux->sig == NULL){
        aux->sig = nuevo;
        nuevo->ant = aux;
        ldePrestamos->final = nuevo;
        return;
    }
}

void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos){
    nodoDoble *borrar = ldePrestamos->inicio;

    while (borrar != NULL) {
        nodoDoble *aux = borrar->sig;
        liberarTPrestamo(borrar->prestamo);
        delete borrar;
        borrar = aux;
    }

    ldePrestamos->inicio = NULL;
    ldePrestamos->final = NULL;

    delete ldePrestamos;
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos){
    nodoDoble *aux = ldePrestamos->inicio;

    printf("LDE Préstamos:\n");
    while (aux != NULL) {
        imprimirTPrestamo(aux->prestamo);
        aux = aux->sig;
    }

    return;
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    nodoDoble *aux = ldePrestamos->final;

    printf("LDE Préstamos:\n");
    while (aux != NULL) {
        imprimirTPrestamo(aux->prestamo);
        aux = aux->ant;
    }

    return;
}

nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos){
    int i = 0;
    nodoDoble *aux = ldePrestamos->inicio;
    while (aux != NULL) {
        i++;
        aux = aux->sig;
    }
    return i;
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->inicio->prestamo;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->final->prestamo;
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n){
    nodoDoble *aux = ldePrestamos->inicio;
    for (int i = 1; i < n; i++) {
        aux = aux->sig;
    }
    return aux->prestamo;
}
 
// criterio = 0 -> prestamos retornados (tienen fecha de devolucion)
// criterio = 1 -> prestamos no retornados (NO tienen fecha de devolucion)
TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio){
    TLDEPrestamos nueva = crearTLDEPrestamosVacia();
    nodoDoble *aux = ldePrestamos->inicio;
    // PRESTAMOS RETORNADOS
    if (criterio == 0) {        
        while (aux != NULL) {  
            if (fueRetornadoTPrestamo(aux->prestamo)) {
                insertarTLDEPrestamos(nueva, copiarTPrestamo(aux->prestamo));
            }
            aux = aux->sig;
        }
    // PRESTAMOS NO RETORNADOS
    } else {
        while (aux != NULL) {
            if (fueRetornadoTPrestamo(aux->prestamo) != true) {
                insertarTLDEPrestamos(nueva, copiarTPrestamo(aux->prestamo));
            }
            aux = aux->sig;
        }
    }
    return nueva;
}