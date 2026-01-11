 
#include "../include/reserva.h"

struct rep_reserva {
  TSocio socio;
  TLibro libro;
};

TReserva crearTReserva(TSocio socio, TLibro libro){
  TReserva nuevo = new rep_reserva;
  nuevo->socio = socio;
  nuevo->libro = libro;
  return nuevo;
}

void imprimirTReserva(TReserva reserva){
  char *titulo = tituloTLibro(reserva->libro);
  char *socioN = nombreTSocio(reserva->socio);
  char *socioA = apellidoTSocio(reserva->socio);
  printf("Reserva de libro %s por %s %s.\n", titulo, socioN, socioA);
}

void liberarTReserva(TReserva &reserva){
  if (reserva != NULL) {

    liberarTSocio(reserva->socio);
    liberarTLibro(reserva->libro);

    delete reserva;
    reserva = NULL;
  }
}

TSocio socioTReserva(TReserva reserva){
  return reserva->socio;
}

TLibro libroTReserva(TReserva reserva){
  return reserva->libro;
}

TReserva copiarTReserva(TReserva reserva){
  TReserva copia = new rep_reserva;
  copia->socio = copiarTSocio(reserva->socio);
  copia->libro = copiarTLibro(reserva->libro);
  return copia;
}

void liberarTReservaSoloEstructura(TReserva &reserva) {
  delete reserva;
  reserva = NULL;
}
