#ifndef MARCO_H_INCLUDED
#define MARCO_H_INCLUDED
#include "constantes.h"
#include <sstream>

class Marco{
private:
    int id;
    int idDeProceso;
    bool ocupado;
    bool espacios[CAPACIDAD_MARCO];
public:
    Marco(){
        id = 0;
        idDeProceso = PROCESO_NULO;
        ocupado = false;
        for(int i = 0; i < CAPACIDAD_MARCO; i++){
            espacios[i] = false;
        }
    }
    void setID(int id){
        idDeProceso = id;
    }
    void setIDMarco(int id){
        this->id = id;
    }
    void ocupaEspacio(int espacios){
        int espaciosAOcupar(espacios);
        if(espaciosAOcupar > CAPACIDAD_MARCO){
            espaciosAOcupar = CAPACIDAD_MARCO;
        }
        for(int i = 0; i < espaciosAOcupar; i++){
            this->espacios[i] = true;
        }
    }
    void setOcupado(bool estado){
        ocupado = estado;
    }
    void limpia(){
        idDeProceso = PROCESO_NULO;
        ocupado = false;
        for(int i = 0; i < CAPACIDAD_MARCO; i++){
            espacios[i] = false;
        }
    }
    int getIdProceso(){
        return idDeProceso;
    }
    int getIdMarco(){
        return id;
    }
    bool estaOcupado(){
        return ocupado;
    }
    std::string formatoIDMarco(){
        std::string representacion("");
        std::stringstream ss;
        representacion += "|  ";
        ss << id;
        representacion +=  ss.str();
        if(representacion.length() > 4){
           representacion += " ";
        }else{
            representacion += "  ";
        }
        return representacion;
    }

    std::string formatoIDProceso(){
        std::string representacion("");
        std::stringstream ss;
        representacion += "|  ";
        if(idDeProceso != SISTEMA_OPERATIVO){
            ss << idDeProceso;
            representacion +=  ss.str();
        }
        else{
            representacion +=  "SO";
        }
        if(representacion.length() > 4){
           representacion += " ";
        }else{
            representacion += "  ";
        }
        return representacion;
    }

    std::string aCadena(){
        std::string marco("");
        for(int i = 0; i < CAPACIDAD_MARCO; i++){
            if(espacios[i] == true){
                marco += "*";
            }
            else{
                marco += "-";
            }
        }
        return marco;
    }
};

#endif // MARCO_H_INCLUDED
