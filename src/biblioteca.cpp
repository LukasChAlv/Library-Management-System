#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
  TABBLibros libros;
  TLSESocios socios;
  TLDEPrestamos prestamos;
  TAGGeneros generos;
  TColaReservas reservas;
};

TBiblioteca crearTBiblioteca(){
  TBiblioteca nuevo = new rep_biblioteca;
  nuevo->libros = crearTABBLibrosVacio();
  nuevo->socios = crearTLSESociosVacia();
  nuevo->prestamos = crearTLDEPrestamosVacia();
  nuevo->generos = crearTAGGeneros();
  nuevo->reservas = crearTColaReservas();
  return nuevo;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){
  insertarLibroTABBLibros(biblioteca->libros, libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){
  insertarTLSESocios(biblioteca->socios, socio);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
  TSocio socio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);

  TPrestamo prestamo = crearTPrestamo(socio, libro, fechaPrestamo);

  insertarTLDEPrestamos(biblioteca->prestamos, prestamo);
} 

bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
  if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro))
    return false;

  int cant = cantidadTLDEPrestamos(biblioteca->prestamos);
  for (int i = 1; i <= cant; i++) {
    TPrestamo prestamo = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);
    TLibro libro = libroTPrestamo(prestamo);

    if (isbnTLibro(libro) == isbnLibro  && !fueRetornadoTPrestamo(prestamo)) 
      return false;
  }
  return true;
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){
  if (disponibleLibroTBiblioteca(biblioteca, isbnLibro)) return;

  TSocio socio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TSocio copiaS = copiarTSocio(socio);

  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);
  TLibro copiaL = copiarTLibro(libro);

  TReserva reserva = crearTReserva(copiaS, copiaL);

  encolarTColaReservas(biblioteca->reservas, reserva);
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
 nat cantPrestamos = cantidadTLDEPrestamos(biblioteca->prestamos);

 for (nat i = 1; i <= cantPrestamos; i++){
  TPrestamo prestamo = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);
  TSocio socio = socioTPrestamo(prestamo);
  TLibro libro = libroTPrestamo(prestamo);
  if (ciTSocio(socio) == ciSocio && isbnTLibro(libro) == isbnLibro && !fueRetornadoTPrestamo(prestamo)) {
    actualizarFechaDevolucionTPrestamo(prestamo, fechaDevolucion);
    return;
  }
 }
}  


void imprimirSociosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLSESocios(biblioteca->socios);
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){
  imprimirTABBLibros(biblioteca->libros);
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
  imprimirTColaReservas(biblioteca->reservas);
}

void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLDEPrestamos(biblioteca->prestamos);
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
  insertarGeneroTAGGeneros(biblioteca->generos, idGeneroPadre, idGenero, nombreGenero);
}


TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
  TABBLibros librosF = crearTABBLibrosVacio();
  TConjuntoGeneros generos = obtenerConjuntoGeneros(biblioteca->generos, idGenero);

  int cantLibros = cantidadTABBLibros(biblioteca->libros);
  for (int i = 1; i <= cantLibros; i++){
    TLibro libro = obtenerNesimoLibroTABBLibros(biblioteca->libros, i);

    if (perteneceTConjuntoGeneros(generos, idGeneroTLibro(libro)))
      insertarLibroTABBLibros(librosF, copiarTLibro(libro));
  }

  liberarTConjuntoGeneros(generos);

  return librosF;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
  liberarTABBLibros(biblioteca->libros);
  liberarTLSESocios(biblioteca->socios);
  liberarTLDEPrestamosSoloEstructura(biblioteca->prestamos);
  liberarTAGGeneros(biblioteca->generos);
  liberarTColaReservas(biblioteca->reservas);

  delete biblioteca;
  biblioteca = NULL;
}
