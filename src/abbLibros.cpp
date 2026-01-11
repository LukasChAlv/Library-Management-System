
#include "../include/abbLibros.h"

struct rep_abbLibros {
    TLibro libro;
    TABBLibros izq, der;
};

TABBLibros crearTABBLibrosVacio(){
    return NULL;
}

void insertarLibroTABBLibros(TABBLibros &abbLibros, TLibro libro){
    if (abbLibros == NULL) {
        abbLibros = new rep_abbLibros;
        abbLibros->libro = libro;
        abbLibros->izq = NULL;
        abbLibros->der = NULL;
        return;
    }
    if (isbnTLibro(libro) < isbnTLibro(abbLibros->libro)) {
        insertarLibroTABBLibros(abbLibros->izq, libro);
    } else if (isbnTLibro(libro) > isbnTLibro(abbLibros->libro)) {
        insertarLibroTABBLibros(abbLibros->der, libro);
    }
}

void imprimirTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) return;
    imprimirTABBLibros(abbLibros->izq);
    imprimirTLibro(abbLibros->libro);
    imprimirTABBLibros(abbLibros->der);
}

void liberarTABBLibros(TABBLibros &abbLibros){
    if (abbLibros == NULL) return;

    liberarTABBLibros(abbLibros->izq);
    liberarTABBLibros(abbLibros->der);

    liberarTLibro(abbLibros->libro);
    delete abbLibros;
    abbLibros = NULL;
}

bool existeLibroTABBLibros(TABBLibros abbLibros, int isbn){
    // CASOS BASE
    if (abbLibros == NULL) return false;
    if (isbnTLibro(abbLibros->libro) == isbn) return true;

    //BUSCAMOS IZQUIERDA Y DERECHA
    if (existeLibroTABBLibros(abbLibros->izq, isbn)) return true;
    return existeLibroTABBLibros(abbLibros->der, isbn);
}

TLibro obtenerLibroTABBLibros(TABBLibros abbLibros, int isbn){  
    if (abbLibros == NULL) return NULL;

    int libroIsbn = isbnTLibro(abbLibros->libro);
    
    if (isbn == libroIsbn) 
        return abbLibros->libro;
    else if (isbn < libroIsbn) 
        return obtenerLibroTABBLibros(abbLibros->izq, isbn);
    else 
        return obtenerLibroTABBLibros(abbLibros->der, isbn);
}

nat alturaTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) return 0;
    nat alturaIzq = alturaTABBLibros(abbLibros->izq);
    nat alturaDer = alturaTABBLibros(abbLibros->der);
    if (alturaIzq > alturaDer) 
        return 1 + alturaIzq;
    else 
        return 1 + alturaDer; 
}

TLibro maxISBNLibroTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) return NULL;
    if (abbLibros->der == NULL) return abbLibros->libro;

    return maxISBNLibroTABBLibros(abbLibros->der);
}

void removerLibroTABBLibros(TABBLibros &abbLibros, int isbn){
    if (abbLibros == NULL) return;

    // BUSCAR IZQUIERDA O DERECHA
    if (isbn < isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->izq, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->der, isbn);
    } 
            // CASOS CON 0 o 1 HIJO
    else {
        if (abbLibros->izq == NULL || abbLibros->der == NULL) {
            TABBLibros borrar = abbLibros;
            if (abbLibros->izq != NULL) {
                abbLibros = abbLibros->izq;
            } else {
                abbLibros = abbLibros->der;
            }
            liberarTLibro(borrar->libro);
            delete borrar;
        } 
            //CASO CON 2 HIJOS
        else { 
            TABBLibros subizq = abbLibros->izq;
            while (subizq->der != NULL) {
                subizq = subizq->der;
            }

            liberarTLibro(abbLibros->libro);
            abbLibros->libro = copiarTLibro(subizq->libro);

            removerLibroTABBLibros(abbLibros->izq, isbnTLibro(subizq->libro));
        }
    }
}

int cantidadTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) 
        return 0; 
    else { 
        return 1 + cantidadTABBLibros(abbLibros->izq) + cantidadTABBLibros(abbLibros->der); 
    }
}

void obtenerNesimoLibroTABBLibrosAux(TABBLibros abbLibros, int n, int &k, TLibro &res){

}

TLibro obtenerNesimoLibroTABBLibros(TABBLibros abbLibros, int n){
    if (abbLibros == NULL) return NULL;

    int cantIzq = cantidadTABBLibros(abbLibros->izq);
    
    if (n == cantIzq + 1) {
        return abbLibros->libro;
    } else if (n <= cantIzq) {
        return obtenerNesimoLibroTABBLibros(abbLibros->izq, n);
    } else {
        return obtenerNesimoLibroTABBLibros(abbLibros->der, n - cantIzq - 1);
    }
}

// FUNCION AUXILIAR PARA CREAR OTRO ARBOL CON LOS GENEROS BUSCADOS-----------------------------------
void filtradoPorGeneroTABBLibrosAux(TABBLibros abbLibros, int genero, TABBLibros &nueva) {
    // CASO BASE 
    if (abbLibros == NULL) return;

    // BUSCAMOS IZQUIERDA
    filtradoPorGeneroTABBLibrosAux(abbLibros->izq, genero, nueva);

    // SI EL GENERO ES IGUAL LO AGREGO
    if (idGeneroTLibro(abbLibros->libro) == genero) {
        insertarLibroTABBLibros(nueva, copiarTLibro(abbLibros->libro));
    }
    
    // BUSCAMOS DERECHA
    filtradoPorGeneroTABBLibrosAux(abbLibros->der, genero, nueva);
}
// -------------------------------------------------------------------------------------------------

TABBLibros filtradoPorGeneroTABBLibros(TABBLibros abbLibros, int genero) { 
    TABBLibros nueva = crearTABBLibrosVacio();             
    filtradoPorGeneroTABBLibrosAux(abbLibros, genero, nueva);
    return nueva; 
}