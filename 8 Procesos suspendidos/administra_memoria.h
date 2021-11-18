#ifndef ADMINISTRA_MEMORIA_H_INCLUDED
#define ADMINISTRA_MEMORIA_H_INCLUDED

#include "marco.h"
#include "constantes.h"

class AdministraMemoria{
private:
    Marco memoria[NUMERO_MARCOS];
    int marcosLibres;

    void reservaEspacioSistemaOperativo(){
        for(int i = 0; i < MARCOS_RESERVADOS_SO; i++){
            memoria[i].setID(SISTEMA_OPERATIVO);
            memoria[i].ocupaEspacio(CAPACIDAD_MARCO);
            memoria[i].setOcupado(true);
            marcosLibres--;
        }
    }
    int marcosAOcupar(int tamanioProceso){
        int marcos;
        marcos = tamanioProceso/CAPACIDAD_MARCO;
        if(tamanioProceso % CAPACIDAD_MARCO != 0){
            marcos++;
        }
        return marcos;
    }
public:
    AdministraMemoria(){
        marcosLibres = NUMERO_MARCOS;
        for(int i = 0; i < NUMERO_MARCOS; i++){
            memoria[i].setIDMarco(i);
        }
        reservaEspacioSistemaOperativo();
    }

    bool hayEspacioParaProceso(int tamanioProceso){
        int paginas;
        paginas = marcosAOcupar(tamanioProceso);
        if(paginas <= marcosLibres){
            return true;
        }else{
            return false;
        }
    }

    void reservaEspacios(Proceso *p){
        int marcos, indice(0), espaciosPorLlenar;
        espaciosPorLlenar = p->getTamanio();
        marcos = marcosAOcupar(p->getTamanio());
        for(int i = 0; i < marcos; i++){
            for(indice= 0; indice < NUMERO_MARCOS; indice++){
                if(!memoria[indice].estaOcupado()){
                    break;
                }
            }
            if(espaciosPorLlenar > CAPACIDAD_MARCO){
                memoria[indice].ocupaEspacio(CAPACIDAD_MARCO);
                espaciosPorLlenar -= CAPACIDAD_MARCO;
            }else{
                memoria[indice].ocupaEspacio(espaciosPorLlenar);
            }
            memoria[indice].setID(p->getId());
            memoria[indice].setOcupado(true);
            marcosLibres--;
        }
    }

    void liberaEspacios(Proceso *p){
        for(int i = 0; i < NUMERO_MARCOS; i++){
            if(memoria[i].getIdProceso() == p->getId()){
                memoria[i].limpia();
                marcosLibres++;
            }
        }
    }

    std::string aCadena(){
        std::string representacion("");

        for(int i= 0; i < 120; i++){
            representacion += "_";
        }
        representacion += "\n";
        for(int i= 0; i < NUMERO_MARCOS/2; i++){
            representacion += memoria[i].formatoIDMarco();
        }
        representacion += "| ID MARCO\n";
        for(int i= 0; i < NUMERO_MARCOS/2; i++){
            representacion += memoria[i].formatoIDProceso();
        }
        representacion += "| ID PROCESO\n";
        for(int i= 0; i < NUMERO_MARCOS/2; i++){
            representacion += "|";
            representacion += memoria[i].aCadena();
        }
        representacion += "| MEMORIA\n"; //segundo bloque


        for(int i= 0; i < 120; i++){
            representacion += "_";
        }
        representacion += "\n";
        for(int i= NUMERO_MARCOS/2; i < NUMERO_MARCOS; i++){
            representacion += memoria[i].formatoIDMarco();
        }
        representacion += "| ID MARCO\n";
        for(int i= NUMERO_MARCOS/2; i < NUMERO_MARCOS; i++){
            representacion += memoria[i].formatoIDProceso();
        }
        representacion += "| ID PROCESO\n";
        for(int i= NUMERO_MARCOS/2; i < NUMERO_MARCOS; i++){
            representacion += "|";
            representacion += memoria[i].aCadena();
        }
        representacion += "| MEMORIA\n";
        return representacion;
    }
};

#endif // ADMINISTRA_MEMORIA_H_INCLUDED
