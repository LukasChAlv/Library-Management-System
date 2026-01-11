#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.
 
struct rep_colaDePrioridadReservas {
    TReserva *heap;
    nat cant;
    nat tam;
    bool prioridadMenor;
};

//-------------------FUNCIONES AUXILIARES--------------------------
void swap (TReserva &reserva1, TReserva &reserva2){
    TReserva aux = reserva1;
    reserva1 = reserva2;
    reserva2 = aux;
}

bool masPrioritario(TColaDePrioridadReservas cp, nat hijo, nat padre){
    if (hijo > cp->cant) return false;
    if (cp->prioridadMenor)
        return rangoTSocio(socioTReserva(cp->heap[hijo])) < rangoTSocio(socioTReserva(cp->heap[padre]));
    else    
        return rangoTSocio(socioTReserva(cp->heap[hijo])) > rangoTSocio(socioTReserva(cp->heap[padre]));
}
//-----------------------------------------------------------------
TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    TColaDePrioridadReservas nuevo = new rep_colaDePrioridadReservas;
    nuevo->heap = new TReserva[N+1];
    nuevo->cant = 0;
    nuevo->tam = N;
    nuevo->prioridadMenor = true;
    return nuevo;
}

void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    cp->prioridadMenor = !cp->prioridadMenor;
    TColaDePrioridadReservas aux = crearTColaDePrioridadReservas(cp->tam);
    aux->prioridadMenor = cp->prioridadMenor;

    for (nat i = 1; i <= cp->cant; i++){
        insertarTColaDePrioridadReservas(aux, copiarTReserva(cp->heap[i]));
    }

    liberarTColaDePrioridadReservas(cp);
    cp = aux;
}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    int i = cp->cant;
    while (i > 0) {
        liberarTReserva(cp->heap[i]);
        i--;
    }
    delete[] cp->heap;
    delete cp;
    cp = NULL;
}


void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {
    cp->cant++;
    nat i = cp->cant;
    cp->heap[i] = reserva;
//------------------------INSERTAR-----------------------------------------
    while (i > 1) {
        nat a = rangoTSocio(socioTReserva(cp->heap[i]));
        nat b = rangoTSocio(socioTReserva(cp->heap[i/2]));

        if (cp->prioridadMenor){
            if (a < b){
                swap(cp->heap[i], cp->heap[i/2]);
                i = i/2;
            } else 
                return;
        } else {
            if (a > b){
                swap(cp->heap[i], cp->heap[i/2]);
                i = i/2;
            } else 
                return;
        }
    }
//-----------------------------------------------------------------------
}

bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp->cant == 0;
}

TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp->heap[1];
}

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp->cant == 0) return;

    liberarTReserva(cp->heap[1]);
    cp->heap[1] = cp->heap[cp->cant];
    cp->cant--;
    nat i = 1;
    //----------------------ELIMINAR------------------------
    while (true){   
        nat a = i*2;
        nat b = i*2+1;
        nat mayorP = i;

        if (masPrioritario(cp, a, mayorP))
            mayorP = a;
        if (masPrioritario(cp, b, mayorP))
            mayorP = b;

        if (mayorP == i) return;
        swap(cp->heap[i], cp->heap[mayorP]);
        i = mayorP;
    }
    //-----------------------------------------------------
}

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    for (nat i = 1; i <= cp->cant; i++){
        if ((ciTSocio(socioTReserva(cp->heap[i]))) == ciSocio && 
            isbnTLibro(libroTReserva((cp->heap[i]))) == isbnLibro)
            return true;
    }
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    for (nat i = 1; i <= cp->cant; i++){
        if ((ciTSocio(socioTReserva(cp->heap[i]))) == ciSocio && 
            isbnTLibro(libroTReserva((cp->heap[i]))) == isbnLibro)
            return rangoTSocio(socioTReserva(cp->heap[i]));
    }
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    TColaDePrioridadReservas copia = crearTColaDePrioridadReservas(cp->tam);
    copia->prioridadMenor = cp->prioridadMenor;
    copia->cant = cp->cant;

    for (nat i = 1; i <= cp->cant; i++) {
        copia->heap[i] = copiarTReserva(cp->heap[i]);
    }
    return copia;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {
    TColaDePrioridadReservas aux = copiarTColaDePrioridadReservas(cp);

    while (!estaVaciaTColaDePrioridadReservas(aux)){
        TReserva auxReserva = prioritarioTColaDePrioridadReservas(aux);
        imprimirTReserva(auxReserva);
        eliminarPrioritarioTColaDePrioridadReservas(aux);
    }
    
    liberarTColaDePrioridadReservas(aux);
}


