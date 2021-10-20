#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <Windows.h>
#include <unistd.h>
#include <conio.h>
#include "proceso.h"
#include "administra_procesos.h"
#define UNO 1
#define RANURAS 4

using namespace std;

vector<Proceso*> procesosTerminados;

void capturaNumeroProcesos(int &numProcesos);
void creaLotesDeProcesos(int &numProcesos, AdministraProcesos &procesos);
void procesamientoPorLotes(AdministraProcesos &procesos);
void ejecutarLote(vector<Proceso*> &lote, int &contadorGlobal,AdministraProcesos &procesos);

void ejecutaProceso(Proceso* p, queue<Proceso*> &q,vector<Proceso*> &loteActual,
                    int &contadorGlobal, AdministraProcesos &procesos);

void imprimirPantalla(Proceso *proceso, vector<Proceso*> loteActual,int &contadorGlobal,
                      AdministraProcesos &procesos);
void pantallaFinal(int &contadorGlobal, AdministraProcesos &procesos);

int main(){
    AdministraProcesos procesos;
    int numProcesos = 0;
    capturaNumeroProcesos(numProcesos);
    creaLotesDeProcesos(numProcesos, procesos);
    procesamientoPorLotes(procesos);
    return 0;
}

void capturaNumeroProcesos(int &numProcesos){
    cout << "BIENVENIDO" << endl;
    while(numProcesos < UNO){
        cout << "Ingrese el numero de procesos: ";
        cin >> numProcesos;
    }
    system("cls || clear");
}

void creaLotesDeProcesos(int &numProcesos, AdministraProcesos &procesos){
    cout << "Creando lotes de procesos" << endl;
    if(numProcesos % RANURAS == 0){
        procesos.setLotesTotales(numProcesos/RANURAS);
    }else{
        procesos.setLotesTotales((numProcesos/RANURAS)+UNO);
    }
    for(int i = 0; i < numProcesos; i++){
        procesos.agregaProceso();
    }
    cout << "Lotes creados exitosamente, presione <ENTER> para continuar . . ." << endl;
    cin.get();
    cin.get();
    system("cls || clear");
}


void procesamientoPorLotes(AdministraProcesos &procesos){
    vector<Proceso*> lote;
    int contadorGlobal = 0;

    for(int i = 0; i < procesos.getLotesTotales(); i++){
        lote = procesos.getSiguienteLote();
        ejecutarLote(lote,contadorGlobal,procesos);
    }
    pantallaFinal(contadorGlobal,procesos);
}

void ejecutarLote(vector<Proceso*> &lote, int &contadorGlobal,AdministraProcesos &procesos){
    vector<Proceso*> v;
    queue<Proceso*> q;
    Proceso *p;

    for(unsigned int i = 0; i < lote.size(); i++){
        q.push(lote[i]);
    }
    while(!q.empty()){
        p = q.front();
        q.pop();
        v.clear();
        while(!q.empty()){
            v.push_back(q.front());
            q.pop();
        }
        for(unsigned int i = 0; i < v.size(); i++){
            q.push(v[i]);
        }
        ejecutaProceso(p,q,v,contadorGlobal,procesos);
    }
}

void ejecutaProceso(Proceso* p, queue<Proceso*> &q, vector<Proceso*> &loteActual,
                    int &contadorGlobal, AdministraProcesos &procesos){
    bool continuar = true;
    char tecla = ' ';
    while(continuar){
        while(!kbhit() and p->getTiempoRestante() != 0){
            imprimirPantalla(p,loteActual,contadorGlobal,procesos);
            contadorGlobal++;
            p->setTiempoTranscurrido(p->getTiempoTranscurrido()+1);
            p->setTiempoRestante(p->getTiempoRestante()-1);
            Sleep(1000);
            if(p->getTiempoRestante() == 0){
                continuar = false;
                procesos.calculaOperacion(p);
                procesosTerminados.push_back(p);
            }
        }
        if(p->getTiempoRestante() != 0){
            tecla  = getch();
            switch(tecla){
                case 'p':
                    cout << "Programa en pausa presione 'c' para continuar ..." << endl;
                    while(getch() != 'c');
                    break;
                case 'e':
                    q.push(p);
                    continuar = false;
                    break;
                case 'w':
                    p->setError(true);
                    procesosTerminados.push_back(p);
                    continuar = false;
                    break;
                default: break;
            }
        }
    }
    imprimirPantalla(p,loteActual,contadorGlobal,procesos);
}

void imprimirPantalla(Proceso *proceso, vector<Proceso*> loteActual,int &contadorGlobal, AdministraProcesos &procesos){
    Proceso *p;
    int cuentaLotes = 1;
    int cuentaProcesos  = 0;
    system("cls || clear");
    //PROCESO EN EJECUCION
    cout << "LOTES PENDIENTES: " << procesos.getLotesRestantes()<< endl;
    cout << "CONTADOR GLOBAL: " << contadorGlobal << endl << endl;
    cout << "-------------------PROCESO EN EJECUCION--------------------" << endl;
    cout << "ID \tTME \tTT \tTR \tOPERACION" << endl;
    cout << proceso->toString() << endl;
    //LOTE EN EJECUCION
    cout << endl << "-------------LOTE EN EJECUCION-------------" << endl;
    cout << "ID \tTME \tTT" << endl;
    for(unsigned int i = 0;  i < loteActual.size(); i++){
        p = loteActual[i];
        cout << p->getId() << " \t" << p->getTiempoMaxEstimado() << " \t"<< p->getTiempoTranscurrido() << endl;
    }
    //PROCESOS TERMINADOS
    cout << endl << "------------PROCESOS TERMINADOS-----------" << endl;
    cout << "ID\tOPERACION\tRESULTADO" << endl;
    cout << "LOTE #" << cuentaLotes << endl;
    for(unsigned int i = 0; i < procesosTerminados.size(); i++){
        if(cuentaProcesos == RANURAS){
            cuentaLotes++;
            cout << "LOTE #" << cuentaLotes << endl;
            cuentaProcesos = 0;
        }
        p = procesosTerminados[i];
        if(p->getError()==false){
            cout << p->getId() << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "
             << p->getOperandoB() << " = \t" << p->getResultado() << endl;
        }
        else{
            cout << p->getId() << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "
             << p->getOperandoB() << " = \tERROR" << endl;
        }
        cuentaProcesos++;
    }
}

void pantallaFinal(int &contadorGlobal, AdministraProcesos &procesos){
    Proceso *p;
    int cuentaLotes = 1;
    int cuentaProcesos  = 0;
    system("cls || clear");
    //PROCESO EN EJECUCION
    cout << "LOTES PENDIENTES: " << procesos.getLotesRestantes()<< endl;
    cout << "CONTADOR GLOBAL: " << contadorGlobal << endl << endl;
    cout << "-------------------PROCESO EN EJECUCION--------------------" << endl;
    cout << "ID \tTME \tTT \tTR \t OPERACION" << endl << endl;
    //LOTE EN EJECUCION
    cout << endl << "-------------LOTE EN EJECUCION-------------" << endl;
    cout << "ID \tTME \tTT" << endl << endl;
    //PROCESOS TERMINADOS
    cout << endl << "------------PROCESOS TERMINADOS-----------" << endl;
    cout << "ID\tOPERACION\tRESULTADO" << endl;
    cout << "LOTE #" << cuentaLotes << endl;
    for(unsigned int i = 0; i < procesosTerminados.size(); i++){
        if(cuentaProcesos == RANURAS){
            cuentaLotes++;
            cout << "LOTE #" << cuentaLotes << endl;
            cuentaProcesos = 0;
        }
        p = procesosTerminados[i];
        if(p->getError()==false){
            cout << p->getId() << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "
             << p->getOperandoB() << " = \t" << p->getResultado() << endl;
        }
        else{
            cout << p->getId() << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "
             << p->getOperandoB() << " = \tERROR" << endl;
        }
        cuentaProcesos++;
    }
    cout << endl << "Presione <ENTER> para terminar . . ." << endl;
    cin.get();
}
