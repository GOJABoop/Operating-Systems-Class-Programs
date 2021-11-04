#ifndef SORTEO_H_INCLUDED
#define SORTEO_H_INCLUDED
#include <ctime>
#include "constantes.h"

int siguienteTurno(){
    int valor, turno;
    srand(time(NULL));
    valor = rand() % (6-1+1) + 1; //aleatorio = rand()%(HASTA-DESDE+1)+DESDE;
    if(valor % 2 == 0 || valor == 3){
        turno = PRODUCTOR;
    }
    else {
        turno = CONSUMIDOR;
    }
    return turno;
}

int dameCantidad(){
    srand(time(NULL));
    return rand() % (6-3+1) + 3; //aleatorio = rand()%(HASTA-DESDE+1)+DESDE;
}

#endif // SORTEO_H_INCLUDED
