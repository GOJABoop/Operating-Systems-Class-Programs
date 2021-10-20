#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <Windows.h>
#include <unistd.h>
#include <conio.h>
#include "proceso.h"
#include "administra_procesos.h"
#define RANURAS 4
#define SEGUNDO 1000

using namespace std;

class Principal{
private:
    int numProcesos;
    int contadorGlobal;
    int quantum;
    int contadorQuantum;
    AdministraProcesos *procesos;
    queue<Proceso*> memoria;
    queue<Proceso*> bloqueados;
    vector<Proceso*> procesosTerminados;
    vector<Proceso*> listaDeBloqueados;
    vector<Proceso*> listaDeProcesosEnMemoria;
public:
    Principal(){
        numProcesos = 0;
        contadorGlobal = 0;
        contadorQuantum = 0;
        procesos = new AdministraProcesos();
        capturaNumeroProcesos();
        FCFS();
    }

    ~Principal(){
        delete procesos;
        procesos = nullptr;
    }
private:
    void capturaNumeroProcesos(){
        cout << "BIENVENIDO" << endl;
        while(numProcesos < 1){
            cout << "Ingrese el numero de procesos: ";
            cin >> numProcesos;
        }
        cout << "Ingrese el intervalo del quantum: ";
        cin >> quantum;
        system("cls || clear");
        for(int i = 0; i < numProcesos; i++){
            procesos->agregaProceso();
        }
        cout << "Procesos creados exitosamente, presione <ENTER> para continuar . . ." << endl;
        cin.get();
        cin.get();
        system("cls || clear");
    }

    void FCFS(){
        cargaProcesos();
        Proceso *p;
        while(!memoria.empty() or !bloqueados.empty()){
            if(!memoria.empty()){
                p = memoria.front();
                memoria.pop();
                ejecutaProceso(p);
            }
            else{
                p = nullptr;
                ejecutaProcesoNulo(p);
            }
        }
        imprimirPantalla(nullptr);
        imprimirTablaDeProcesos(nullptr,true);
    }

    void cargaProcesos(){
        Proceso *p;
        for(int i = 0; i < RANURAS and !procesos->vacio(); i++){
            p = procesos->getSiguienteProceso();
            p->setTiempoLlegada(contadorGlobal);
            memoria.push(p);
        }
    }

    void cargaProceso(){
        Proceso *p;
        if(!procesos->vacio()){
            p = procesos->getSiguienteProceso();
            p->setTiempoLlegada(contadorGlobal);
            memoria.push(p);
        }
    }

    void ejecutaProceso(Proceso *p){
        bool continuar = true;
        char tecla = ' ';
        contadorQuantum = 0;
        while(continuar){
            while(!kbhit() and p->getTiempoRestante() != 0){
                actualizarColaBloqueados();
                actualizarListaMemoria();
                imprimirPantalla(p);
                if(!p->fueRespondido()){
                    p->setTiempoRespuesta(contadorGlobal - p->getTiempoLlegada());
                    p->setRespondido(true);
                }
                contadorGlobal++;
                contadorQuantum++;
                p->setTiempoTranscurrido(p->getTiempoTranscurrido()+1);
                p->setTiempoRestante(p->getTiempoRestante()-1);
                Sleep(SEGUNDO);
                if(p->getTiempoRestante() == 0){
                    continuar = false;
                    procesos->calculaOperacion(p);
                    calculaTiemposProceso(p);
                    procesosTerminados.push_back(p);
                    cargaProceso();
                }
                else if(contadorQuantum == quantum){
                    continuar = false;
                    memoria.push(p);
                    break;
                }
            }
            if(continuar){
                tecla  = getch();
                switch(tecla){
                    case 'p':
                        cout << "Programa en pausa presione 'c' para continuar ..." << endl;
                        while(getch() != 'c');
                        break;
                    case 'e':
                        bloqueados.push(p);
                        continuar = false;
                        break;
                    case 'w':
                        p->setError(true);
                        procesosTerminados.push_back(p);
                        calculaTiemposProceso(p);
                        cargaProceso();
                        continuar = false;
                        break;
                    case 'n':
                        procesos->agregaProceso();
                        if(memoria.size()+bloqueados.size() < RANURAS-1){
                            cargaProceso();
                        }
                        break;
                    case 'b':
                        imprimirTablaDeProcesos(p,false);
                        while(getch() != 'c');
                        imprimirPantalla(p);
                        break;
                    default: break;
                }
            }
        }
    }

    void ejecutaProcesoNulo(Proceso *p){
        bool continuar = true;
        char tecla = ' ';
        while(continuar){
            while(!kbhit() and memoria.empty()){
                actualizarColaBloqueados();
                actualizarListaMemoria();
                imprimirPantalla(p);
                contadorGlobal++;
                Sleep(SEGUNDO);
            }
            if(memoria.empty()){
                tecla  = getch();
                switch(tecla){
                    case 'p':
                        cout << "Programa en pausa presione 'c' para continuar ..." << endl;
                        while(getch() != 'c');
                        break;
                    case 'n':
                        procesos->agregaProceso();
                        if(bloqueados.size() < RANURAS){
                            cargaProceso();
                        }
                        break;
                    case 'b':
                        imprimirTablaDeProcesos(p,false);
                        while(getch() != 'c');
                        imprimirPantalla(p);
                        break;
                    default: break;
                }
            }else{
                continuar = false;
            }
        }
    }

    void actualizarColaBloqueados(){
        listaDeBloqueados.clear();
        Proceso *p;
        unsigned int len(bloqueados.size());
        for(unsigned int i = 0; i < len; i++){
            p = bloqueados.front();
            bloqueados.pop();
            p->setTiempoBloqueado(p->getTiempoBloqueado() + 1);
            if(p->getTiempoBloqueado() == 7){
                p->setTiempoBloqueado(0);
                memoria.push(p);
            }
            else{
                bloqueados.push(p);
                listaDeBloqueados.push_back(p);
            }
        }
    }

    void actualizarListaMemoria(){
        listaDeProcesosEnMemoria.clear();
        unsigned int len(memoria.size());
        for(unsigned int i = 0; i < len; i++){
            listaDeProcesosEnMemoria.push_back(memoria.front());
            memoria.pop();
            memoria.push(listaDeProcesosEnMemoria[i]);
        }
    }

    void calculaTiemposProceso(Proceso *p){
        p->setTiempoFinalizacion(contadorGlobal);
        p->setTiempoServicio(p->getTiempoTranscurrido());
        p->setTiempoRetorno(p->getTiempoFinalizacion() - p->getTiempoLlegada());
        p->setTiempoEspera(p->getTiempoRetorno() - p->getTiempoServicio());
    }

    void imprimirPantalla(Proceso *proceso){
        Proceso *p;
        system("cls || clear");
        //PROCESO EN EJECUCION
        cout << "PROCESOS NUEVOS: " << procesos->getProcesosNuevos() << endl;
        cout << "CONTADOR GLOBAL: " << contadorGlobal << endl;
        cout << "VALOR DEL QUANTUM: " << quantum << endl << endl;
        cout << "-------------------PROCESO EN EJECUCION--------------------" << endl;
        cout << "TTQ \tID \tTME \tTT \tTR \tOPERACION" << endl;
        if(proceso != nullptr){
            cout << contadorQuantum << "\t" << proceso->toString() << endl;
        }
        //PROCESOS LISTOS
        cout << endl << "--------------PROCESOS LISTOS-------------" << endl;
        cout << "\tID \tTME \tTT" << endl;
        for(unsigned int i = 0;  i < listaDeProcesosEnMemoria.size(); i++){
            p = listaDeProcesosEnMemoria[i];
            cout << "\t" << p->getId() << " \t" << p->getTiempoMaxEstimado() << " \t"<< p->getTiempoTranscurrido() << endl;
        }
        //PROCESOS BLOQUEADOS
        cout << endl << "------------PROCESOS BLOQUEADOS------------" << endl;
        cout << "ID \tTTB" << endl;
        for(unsigned int i = 0;  i < listaDeBloqueados.size(); i++){
            p = listaDeBloqueados[i];
            cout << p->getId() << " \t" << p->getTiempoBloqueado() << endl;
        }
        //PROCESOS TERMINADOS
        cout << endl << "------------PROCESOS TERMINADOS-----------" << endl;
        cout << "ID\tOPERACION\tRESULTADO\tTME\tTRTNT\tTT\tTLL\tTF\tTRET\tTRES\tTE\tTS" << endl;
        for(unsigned int i = 0; i < procesosTerminados.size(); i++){
            p = procesosTerminados[i];
            cout << p->getId();
            if(p->getError()==false){
                cout << "\t" << p->getOperandoA() << " " << p->getOperacion() << " " << p->getOperandoB() << " = \t" << p->getResultado();
            }
            else{
                cout << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "<< p->getOperandoB() << " = \tERROR";
            }
            cout << "\t\t" << p->getTiempoMaxEstimado()
            << "\t" << p->getTiempoRestante()
            << "\t" << p->getTiempoTranscurrido()
            << "\t" << p->getTiempoLlegada()
            << "\t" << p->getTiempoFinalizacion()
            << "\t" << p->getTiempoRetorno()
            << "\t" << p->getTiempoRespuesta()
            << "\t" << p->getTiempoEspera()
            << "\t" << p->getTiempoServicio() << endl;
        }
    }

    void imprimirTablaDeProcesos(Proceso *proceso, bool terminado){
        Proceso *p;
        vector<Proceso*> procesosNuevos;
        procesosNuevos = procesos->getListaProcesosNuevos();
        cout << endl << "------------TABLA DE PROCESOS (BCP)-----------" << endl;
        cout << "ID\tESTADO\tOPERACION\tRESULTADO\tTME\tTLL\tTF\tTRET\tTE\tTS\tTRTNT\tTRES" << endl;
        for(unsigned int i = 0; i < procesosTerminados.size(); i++){
            p = procesosTerminados[i];
            cout << p->getId() << "\tT\t" << p->getOperandoA() << " " << p->getOperacion() << " " << p->getOperandoB() << " = \t";
            if(p->getError()==false){
                cout << p->getResultado();
            }else cout  << "ERROR";
            cout << "\t\t" << p->getTiempoMaxEstimado()
            << "\t" << p->getTiempoLlegada()
            << "\t" << p->getTiempoFinalizacion()
            << "\t" << p->getTiempoRetorno()
            << "\t" << p->getTiempoEspera()
            << "\t" << p->getTiempoServicio()
            << "\t" << p->getTiempoRestante()
            << "\t" << p->getTiempoRespuesta() << endl;
        }
        if(proceso != nullptr){
            imprimeDetallesProceso(proceso,'E');
        }
        for(unsigned int i = 0;  i < listaDeProcesosEnMemoria.size(); i++){
            p = listaDeProcesosEnMemoria[i];
            imprimeDetallesProceso(p,'L');
        }

        for(unsigned int i = 0;  i < listaDeBloqueados.size(); i++){
            p = listaDeBloqueados[i];
            imprimeDetallesProceso(p,'B');
        }
        for(unsigned int i = 0; i < procesosNuevos.size(); i++){
            p = procesosNuevos[i];
            cout << p->getId()
             << "\tN\t"
             << p->getOperandoA() << " "
             << p->getOperacion() << " "
             << p->getOperandoB() << " = \tnull\t\t"
             << p->getTiempoMaxEstimado()
             << "\tnull" // tiempo de llegada
             << "\tnull" //tiempo de finalizacion
             << "\tnull" //tiempo tiempo retorno
             << "\tnull"//tiempo de espera al momento
             << "\tnull" //tiempo Servicio
             << "\tnull" //tiempo restante
             << "\tnull" << endl; //tiempo respuesta
        }
        if(!terminado){
            cout << "Presione la tecla <C> para continuar ...";
        }else{
            cout << "Presione <ENTER> para terminar...";
            cin.get();
        }
    }

    void imprimeDetallesProceso(Proceso *proceso, char estado){
        cout << proceso->getId()
             << "\t"<< estado <<"\t"
             << proceso->getOperandoA() << " "
             << proceso->getOperacion() << " "
             << proceso->getOperandoB() << " = \tnull\t\t"
             << proceso->getTiempoMaxEstimado()
             << "\t" << proceso->getTiempoLlegada()
             << "\tnull" //tiempo de finalizacion
             << "\tnull\t" //tiempo tiempo retorno
             << contadorGlobal-proceso->getTiempoLlegada()-proceso->getTiempoTranscurrido() //tiempo de espera al momento
             << "\t" << proceso->getTiempoTranscurrido() //tiempo Servicio
             << "\t" <<proceso->getTiempoRestante();
         if(proceso->fueRespondido()){//tiempo respuesta
            cout << "\t" << proceso->getTiempoRespuesta() << endl;
         }else{
            cout << "\tnull" << endl;
         }
    }
};

#endif // PRINCIPAL_H_INCLUDED
