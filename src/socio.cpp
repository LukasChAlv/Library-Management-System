#include "../include/socio.h"

struct rep_socio {
    int ci;
    char nombre[MAX_NOMBRE_SOCIO];
    char apellido[MAX_APELLIDO_SOCIO];
    TFecha FechaAlta;
    int idGenero[MAX_GENEROS_FAVORITOS];
    nat rango;
};
 
TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta, nat rango){
    TSocio nuevo = new rep_socio;

    nuevo->ci = ci;
 
    // copiar nombre y apellido
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->apellido, apellido);

    for (int i = 0; i < MAX_GENEROS_FAVORITOS; i++) 
        nuevo->idGenero[i] = 0;

    nuevo->FechaAlta = crearTFecha(diaAlta, mesAlta, anioAlta);

    nuevo->rango = rango;
    
    return nuevo;
}

void imprimirTSocio(TSocio socio){
        printf("Socio %d: %s %s\n", socio->ci, socio->nombre, socio->apellido); // CI

        printf("Fecha de alta: ");        //FECHA DE ALTA 
        imprimirTFecha(socio->FechaAlta);

        printf("Géneros favoritos: ");    // GENEROS FAVORITOS     
        for (int n = 0; n < MAX_GENEROS_FAVORITOS; n++) {
                if (socio->idGenero[n] != 0) {
                    printf("%d ", socio->idGenero[n]);
                }
        }
        
        printf("\n");  
}

void liberarTSocio(TSocio &socio) {
    if (socio != NULL) {
        liberarTFecha(socio->FechaAlta);
        delete socio;
        socio = NULL;
    }
}

int ciTSocio(TSocio socio){
    return socio->ci;
}

nat rangoTSocio(TSocio socio){
    return socio->rango;
}

char* nombreTSocio(TSocio socio){
    return socio->nombre;
}

char* apellidoTSocio(TSocio socio){
    return socio->apellido;
}

TFecha fechaAltaTSocio(TSocio socio){
    return socio->FechaAlta;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
    int i = 0;
    while (i < MAX_GENEROS_FAVORITOS && socio->idGenero[i] != 0) {
        i++;
    }
    if (i != MAX_GENEROS_FAVORITOS) {
        socio->idGenero[i] = idGenero;
    } else {
        return;
    }
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    int i = 0;
    while (i < MAX_GENEROS_FAVORITOS && socio->idGenero[i] != idGenero) {
        i++;
    }
    return i < MAX_GENEROS_FAVORITOS;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){
    int cant = 0;
    int i = 0;
    while (i < MAX_GENEROS_FAVORITOS && socio->idGenero[i] != 0) {
        cant++;
        i++;
    }
    return cant;
}

TSocio copiarTSocio(TSocio socio){
    TSocio copia = new rep_socio;
    copia->ci = socio->ci;
    strcpy(copia->nombre, socio->nombre);
    strcpy(copia->apellido, socio->apellido);
    copia->FechaAlta = copiarTFecha(socio->FechaAlta);
    for (int i = 0; i < MAX_GENEROS_FAVORITOS; i++) 
        copia->idGenero[i] = socio->idGenero[i];
    copia->rango = socio->rango;
    return copia;
}
