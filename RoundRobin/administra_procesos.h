#ifndef ADMINISTRA_PROCESOS_H_INCLUDED
#define ADMINISTRA_PROCESOS_H_INCLUDED
#include <queue>
#include <vector>
#include <cmath>
#include <ctime>
#include "proceso.h"

class AdministraProcesos{
private:
    std::queue<Proceso*> procesos;
    int procesosNuevos;
    int contadorId;

    char getOperacion(){
        int numero;
        numero = rand() % (6-1+1) + 1;
        switch(numero){
            case 1:     return '+';     break;
            case 2:     return '-';     break;
            case 3:     return '*';     break;
            case 4:     return '/';     break;
            case 5:     return '%';     break;
            case 6:     return '^';     break;
            default:    return '+';     break;
        }
    }
    int getTiempoMaximoEstimado(){
        return rand() % (15-6+1) + 6;
    }
    int getOperando(){
        return rand() % (1000-0+1) + 0;
    }
public:
    AdministraProcesos(){
        procesosNuevos = 0;
        contadorId = 1;
        srand(time(NULL));
    }
    void agregaProceso(){
        Proceso *p = new Proceso();
        p->setId(contadorId);
        p->setTiempoMaxEstimado(getTiempoMaximoEstimado());
        p->setOperacion(getOperacion());
        p->setOperandoA(getOperando());
        if(p->getOperacion() == '/' or p->getOperacion() == '%'){
            while(p->getOperandoB() == 0){
                p->setOperandoB(getOperando());
            }
        }
        else if(p->getOperacion() == '*'){
            p->setOperandoB(rand() % (50-0+1) + 0);
        }
        else if(p->getOperacion() == '^'){
            p->setOperandoA(rand() % (9-0+1) + 0);
            p->setOperandoB(rand() % (5-0+1) + 0);
        }
        else{
            p->setOperandoB(getOperando());
        }
        p->setTiempoRestante(p->getTiempoMaxEstimado());
        procesos.push(p);
        procesosNuevos++;
        contadorId++;
    }

    Proceso* getSiguienteProceso(){
        Proceso *p = procesos.front();
        procesos.pop();
        procesosNuevos--;
        return p;
    }

    bool vacio(){
        return procesos.empty();
    }
    int getProcesosNuevos(){
        return procesosNuevos;
    }
    void calculaOperacion(Proceso* p){
        switch(p->getOperacion()){
            case '+':   p->setResultado( p->getOperandoA() + p->getOperandoB());    break;
            case '-':   p->setResultado( p->getOperandoA() - p->getOperandoB());    break;
            case '*':   p->setResultado( p->getOperandoA() * p->getOperandoB());    break;
            case '/':   p->setResultado( p->getOperandoA() / p->getOperandoB());    break;
            case '%':   p->setResultado( p->getOperandoA() % p->getOperandoB());    break;
            case '^':   p->setResultado( pow(p->getOperandoA(),p->getOperandoB())); break;
            default:    p->setResultado( p->getOperandoA() + p->getOperandoB());    break;
        }
    }
    std::vector<Proceso*> getListaProcesosNuevos(){
        std::vector<Proceso*> lista;
        unsigned int len(procesos.size());
        for(unsigned int i = 0; i < len; i++){
            lista.push_back(procesos.front());
            procesos.pop();
            procesos.push(lista[i]);
        }
        return lista;
    }
};
#endif // ADMINISTRA_PROCESOS_H_INCLUDED
