#ifndef CONTENEDOR_H_INCLUDED
#define CONTENEDOR_H_INCLUDED
#include "constantes.h"

class Contenedor{
private:
    bool elementos[CAPACIDAD_CONTENEDOR];
    int cuentaElementos;
    int indiceConsumidor;
    int indiceProductor;
public:
    Contenedor(){
        for(int i = 0; i < CAPACIDAD_CONTENEDOR ;i++){
            elementos[i] = false;
        }
        cuentaElementos = 0;
        indiceConsumidor = 0;
        indiceProductor = 0;
    }

    bool estaVacio(){
        return cuentaElementos == 0;
    }

    bool estaLLeno(){
        return cuentaElementos == CAPACIDAD_CONTENEDOR;
    }

    int cuenta(){
        return cuentaElementos;
    }

    void produce(){
        if(!estaLLeno()){
            elementos[indiceProductor] = true;
            indiceProductor == CAPACIDAD_CONTENEDOR-1 ? indiceProductor = 0 : indiceProductor++;
            cuentaElementos++;
        }
    }

    void consume(){
        if(!estaVacio()){
            elementos[indiceConsumidor] = false;
            indiceConsumidor == CAPACIDAD_CONTENEDOR-1 ? indiceConsumidor = 0 : indiceConsumidor++;
            cuentaElementos--;
        }
    }

    std::string aCadena(){
        std::string estado("");
        for(int i = 0; i < CAPACIDAD_CONTENEDOR; i++){
            if(elementos[i] == true){
                estado += " * ";
            }
            else estado += " _ ";
        }
        return estado;
    }
};

#endif // CONTENEDOR_H_INCLUDED
