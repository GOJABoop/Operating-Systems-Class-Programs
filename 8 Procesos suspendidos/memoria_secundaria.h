#ifndef MEMORIA_SECUNDARIA_H_INCLUDED
#define MEMORIA_SECUNDARIA_H_INCLUDED
#include <queue>
#include <fstream>
#include <sstream>
#include "proceso.h"
#include "constantes.h"

class MemoriaSecundaria{
private:
    int cuentaProcesos;
    int indiceArchivo;
    std::queue<int> espaciosDeProcesos;

    void iniciarArchivo(){
        std::ofstream archivo;
        archivo.open(NOMBRE_ARCHIVO_SUSPENDIDOS, std::ios::out | std::ios::trunc);
        archivo.close();
    }

    int aEntero(std::string cadena){
        std::stringstream ss;
        int valor;

        ss << cadena;
        ss >> valor;

        return valor;
    }
public:
    MemoriaSecundaria(){
        cuentaProcesos = 0;
        indiceArchivo = 0;
        iniciarArchivo();
    }
    bool estaVacio(){
        return cuentaProcesos == 0;
    }
    int numeroProcesosSuspendidos(){
        return cuentaProcesos;
    }
    int tamanioSiguienteProceso(){
        return espaciosDeProcesos.front();
    }

    void agregaProcesoSuspendido(Proceso *p){
        std::ofstream archivo;
        archivo.open(NOMBRE_ARCHIVO_SUSPENDIDOS, std::ios::app);
        if (archivo.is_open()){
            archivo << p->getId() << SEPARADOR_CAMPOS
                    << p->getOperandoA() << SEPARADOR_CAMPOS
                    << p->getOperacion() << SEPARADOR_CAMPOS
                    << p->getOperandoB() << SEPARADOR_CAMPOS
                    << p->getResultado() << SEPARADOR_CAMPOS
                    << p->getTiempoMaxEstimado() << SEPARADOR_CAMPOS
                    << p->getTamanio() << SEPARADOR_CAMPOS
                    << p->getTiempoTranscurrido() << SEPARADOR_CAMPOS
                    << p->getTiempoRestante() << SEPARADOR_CAMPOS
                    << p->getTiempoBloqueado() << SEPARADOR_CAMPOS
                    << p->getTiempoLlegada() << SEPARADOR_CAMPOS
                    << p->getTiempoFinalizacion() << SEPARADOR_CAMPOS
                    << p->getTiempoServicio() << SEPARADOR_CAMPOS
                    << p->getTiempoRetorno() << SEPARADOR_CAMPOS
                    << p->getTiempoEspera() << SEPARADOR_CAMPOS
                    << p->getTiempoRespuesta() << SEPARADOR_CAMPOS
                    << p->fueRespondido() << SEPARADOR_CAMPOS
                    << p->getError() << SEPARADOR_REGISTROS;
            archivo.close();
        }
        cuentaProcesos++;
        espaciosDeProcesos.push(p->getTamanio());
    }

    Proceso* extraeProcesoDelFrente(){
        std::ifstream archivo;
        std::string cadena;
        Proceso *p = new Proceso();

        archivo.open(NOMBRE_ARCHIVO_SUSPENDIDOS, std::ios::in);
        if (archivo.is_open()){
            for(int i = 0; i < indiceArchivo; i++){
                getline(archivo,cadena,SEPARADOR_REGISTROS);
            }
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setId(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setOperandoA(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setOperacion(cadena[0]);
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setOperandoB(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setResultado(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoMaxEstimado(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTamanio(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoTranscurrido(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoRestante(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoBloqueado(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoLlegada(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoFinalizacion(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoServicio(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoRetorno(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoEspera(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setTiempoRespuesta(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_CAMPOS);
            p->setRespondido(aEntero(cadena));
            getline(archivo,cadena,SEPARADOR_REGISTROS);
            p->setError(aEntero(cadena));

            archivo.close();
            indiceArchivo++;
            cuentaProcesos--;
            espaciosDeProcesos.pop();
            return p;
        }
        else {
            return nullptr;
        }
    }
};

#endif // MEMORIA_SECUNDARIA_H_INCLUDED
