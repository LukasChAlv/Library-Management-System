#include "../include/fecha.h"

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    /*Escriba el código a continuación */
    delete fecha;
    fecha = NULL;
    /****** Fin de parte Parte 3.3 *****/
}

void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */
    printf("%u/%u/%u\n", fecha->dia, fecha->mes, fecha->anio);
    /****** Fin de parte Parte 3.5 *****/
}

TFecha copiarTFecha(TFecha fecha) {
    TFecha copia = new rep_fecha;
    copia->dia = fecha->dia;
    copia->mes = fecha->mes;
    copia->anio = fecha->anio;
    return copia;
}

/************ Parte 3.9 ************/
/*Escriba el código a continuación */
static nat diasMes(nat mes, nat anio) {
    if (mes == 2 && ((anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0))) {
        return 29;
    }
    else {
        switch(mes) {
            case 1: return 31;
            case 2: return 28;
            case 3: return 31;
            case 4: return 30;
            case 5: return 31;
            case 6: return 30;
            case 7: return 31;
            case 8: return 31;
            case 9: return 30;
            case 10: return 31;
            case 11: return 30;
            case 12: return 31;
            default: return 0;
        }

    }
}
/*Recuerde que las funciones auxiliares
  deben declararse antes de ser utilizadas*/


void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

/****** Fin de parte Parte 3.9 *****/

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
    if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia) {
        return 0;
    } else if ((fecha1->anio > fecha2->anio) || 
               (fecha1->anio == fecha2->anio && ( fecha1->mes > fecha2->mes ||
               (fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia)))) {
        return 1;
    } else return -1;
    /****** Fin de parte Parte 3.10 *****/
}