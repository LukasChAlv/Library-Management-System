 
#include "../include/prestamo.h"
 
struct rep_prestamo {
  TSocio socio;
  TLibro libro;
  TFecha fechaRetiro;
  TFecha fechaDevolucion;
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro){
  TPrestamo nuevo = new rep_prestamo;
  nuevo->socio = socio;
  nuevo->libro = libro;
  nuevo->fechaRetiro = fechaRetiro;
  nuevo->fechaDevolucion = NULL;
  return nuevo;
}
 
void imprimirTPrestamo(TPrestamo prestamo){
  printf("Préstamo de libro %s a %s %s.\n", tituloTLibro(prestamo->libro), 
                                           nombreTSocio(prestamo->socio), 
                                           apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolucion == NULL) {
    printf("No retornado\n");
  } else {
    imprimirTFecha(prestamo->fechaDevolucion);
  }
}

void liberarTPrestamo(TPrestamo &prestamo){
  if (prestamo != NULL) {
    liberarTSocio(prestamo->socio);

    liberarTLibro(prestamo->libro);

    liberarTFecha(prestamo->fechaRetiro);

    if (prestamo->fechaDevolucion != NULL) {
      liberarTFecha(prestamo->fechaDevolucion);
    }

    delete prestamo;
    prestamo = NULL;
  }
}

TSocio socioTPrestamo(TPrestamo prestamo){
  return prestamo->socio;
}
 
TFecha fechaRetiroTPrestamo(TPrestamo prestamo){
  return prestamo->fechaRetiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo){
  return prestamo->fechaDevolucion;
}

TLibro libroTPrestamo(TPrestamo prestamo){
  return prestamo->libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo){
  return prestamo->fechaDevolucion != NULL;
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion){
  if (prestamo->fechaDevolucion != NULL) {
    liberarTFecha(prestamo->fechaDevolucion);
  }
  prestamo->fechaDevolucion = fechaDevolucion;
}

TPrestamo copiarTPrestamo(TPrestamo prestamo){
  TPrestamo copia = new rep_prestamo;
  copia->socio = copiarTSocio(prestamo->socio);
  copia->libro = copiarTLibro(prestamo->libro);
  copia->fechaRetiro = copiarTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolucion != NULL) {
    copia->fechaDevolucion = copiarTFecha(prestamo->fechaDevolucion);
  } else {
    copia->fechaDevolucion = NULL;
  }
  return copia;
} 

void liberarTPrestamoSoloEstructura(rep_prestamo* &prestamo){
  if (prestamo != NULL) {
    liberarTFecha(prestamo->fechaRetiro);

    if (prestamo->fechaDevolucion != NULL) {
      liberarTFecha(prestamo->fechaDevolucion);
    }

    delete prestamo;
    prestamo = NULL;
  }
}