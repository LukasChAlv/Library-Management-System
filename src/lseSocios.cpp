
#include "../include/lseSocios.h"

struct rep_lseSocios {
	TSocio socio;
	TLSESocios sig;
};

TLSESocios crearTLSESociosVacia(){
    return NULL;
}

bool esVaciaTLSESocios(TLSESocios lseSocios){
	return lseSocios == NULL;
}

void imprimirTLSESocios(TLSESocios lseSocios){
	printf("Lista de Socios:\n");
	if (lseSocios != NULL) {
		while (lseSocios != NULL) {
			imprimirTSocio(lseSocios->socio);
			lseSocios = lseSocios->sig;
		}
	}		
}

void liberarTLSESocios(TLSESocios &lseSocios){
	TLSESocios borrar;
	if (lseSocios != NULL) {
			while (lseSocios != NULL) {
				liberarTSocio(lseSocios->socio);
				borrar = lseSocios;
				lseSocios = lseSocios->sig;
				delete borrar;
			}
	}
}

void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio){
	TLSESocios nuevo = new rep_lseSocios; 
	nuevo->socio = socio;
	nuevo->sig = NULL;

	// SI LA LISTA ESTA VACIA
	if (lseSocios == NULL || compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(lseSocios->socio)) < 0) {  
		nuevo->sig = lseSocios;
		lseSocios = nuevo;
		return;
	}

	// INSERTAR AL MEDIO O AL FINAL
	TLSESocios aux = lseSocios;
	while (aux->sig != NULL && compararTFechas(fechaAltaTSocio(aux->sig->socio), fechaAltaTSocio(socio)) <= 0) {
		aux = aux->sig;
	} 

	// INSERTAR EL NODO
	nuevo->sig = aux->sig;
	aux->sig = nuevo;

}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci){
	while (lseSocios != NULL && ciTSocio(lseSocios->socio) != ci) {
		lseSocios = lseSocios->sig;
	}
	return lseSocios != NULL;
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci){
	while (lseSocios != NULL && ciTSocio(lseSocios->socio) != ci) {
		lseSocios = lseSocios->sig;
	}
    return lseSocios->socio;
}

TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n){
	for (int i = 1; i < n; i++){
		lseSocios = lseSocios->sig;
	}
	return lseSocios->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios){
	int i = 0;
	while (lseSocios != NULL) {
		i++;
		lseSocios = lseSocios->sig;
	}
	return i;
}

void removerSocioTLSESocios(TLSESocios &lseSocios, int ci){
	TLSESocios borrar;

	// SI EL SOCIO A BORRAR ESTA AL PRINCIPIO
	if (ciTSocio(lseSocios->socio) == ci) {    
		borrar = lseSocios;
		lseSocios = lseSocios->sig;
		liberarTSocio(borrar->socio);
		delete borrar;
		return;
	}

	// SI ESTA EN EL MEDIO O FINAL
	TLSESocios aux = lseSocios;
	while (aux->sig != NULL && ciTSocio(aux->sig->socio) != ci) {
		aux = aux->sig;
	}

	// BORRAR EL NODO
	borrar = aux->sig;
	aux->sig = aux->sig->sig;
	liberarTSocio(borrar->socio);
	delete borrar;
	return;
}