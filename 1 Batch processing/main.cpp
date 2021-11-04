#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <Windows.h>
#include <unistd.h>
#include "proceso.h"

#define UNO 1
#define NULO 0
#define RANURAS 4

using namespace std;

char seleccionaOperacion();
int menuOperaciones();
bool datosSonValidos(int id, int tiempoMaxEstimado, char operacion, double operandoB);
bool listaIDsContiene(int id);
void creaLotesDeProcesos();
void procesamientoPorLotes();
void ejecutaProceso(Proceso *p);
void imprimirProcesosCompletados();
void imprimirLoteActual();
void imprimeDatos(Proceso *p, int tTranscurrido, int tRestante);
void calculaOperacion(Proceso* p);

vector<Proceso*> procesos;
vector<Proceso*> procesosTerminados;
int contadorGlobal;
int numProcesos;
int lotes;
int lotesPendientes;
unsigned int indice;

int main(){
    string nombreProgramador;
    int id, tiempoMaxEstimado;
    double operandoA, operandoB;
    char operacion;
    Proceso *p;

    cout << "BIENVENIDO" << endl;
    while(numProcesos < UNO){
        cout << "Ingrese el numero de procesos: ";
        cin >> numProcesos;
    }
    lotes = numProcesos / RANURAS;
    if(lotes % RANURAS != NULO) lotes++;

    system("cls || clear");
    for(int i = 0; i < numProcesos; i++){
        cout << "PROCESOS A  REGISTRAR: " << numProcesos << endl;
        cout << "PROCESOS PENDIENTES: " << numProcesos-i << endl << endl;
        p = new Proceso();
        cout << "PROCESO #" << i+1 << endl;
        cout << "Nombre programador: ";
        cin.get();
        getline(cin,nombreProgramador);
        cout << "ID: ";
        cin >> id;
        cout << "Tiempo maximo estimado: ";
        cin >> tiempoMaxEstimado;
        cout << "Operando A: ";
        cin >> operandoA;
        cout << "Operando B: ";
        cin >> operandoB;
        operacion = seleccionaOperacion();

        if(datosSonValidos(id,tiempoMaxEstimado,operacion,operandoB)){
            p->setNombreProgramador(nombreProgramador);
            p->setId(id);
            p->setTiempoMaxEstimado(tiempoMaxEstimado);
            p->setOperandoA(operandoA);
            p->setOperandoB(operandoB);
            p->setOperacion(operacion);
            procesos.push_back(p);
        }
        else{
            i--;
        }
        system("cls || clear");
    }
    creaLotesDeProcesos();
    return 0;
}

char seleccionaOperacion(){
    char operacion;
    switch(menuOperaciones()){
        case 1:     operacion = '+';     break;
        case 2:     operacion = '-';     break;
        case 3:     operacion = '*';     break;
        case 4:     operacion = '/';     break;
        case 5:     operacion = '%';     break;
        case 6:     operacion = '^';     break;
        default:    operacion = '+';     break;
    }
    return operacion;
}

int menuOperaciones(){
    int opcion;
    cout << "Elige la operacion a aplicar: " << endl;
    cout << "1. +" << endl;
    cout << "2. -" << endl;
    cout << "3. *" << endl;
    cout << "4. /" << endl;
    cout << "5. %" << endl;
    cout << "6. ^" << endl;
    cout << "Operacion: ";
    cin >> opcion;

    return opcion;
}

bool datosSonValidos(int id, int tiempoMaxEstimado, char operacion, double operandoB){
    if(listaIDsContiene(id)){
        cout << "El ID ya se encuntra registrado." << endl;
        cout << "Presione <ENTER> para continuar . . ." << endl;
        cin.get();
        cin.get();
        return false;
    }
    if(tiempoMaxEstimado <= NULO){
        cout << "Tiempo maximo estimado debe ser un entero mayor a 0." << endl;
        cout << "Presione <ENTER> para continuar . . ." << endl;
        cin.get();
        cin.get();
        return false;
    }
    if((operacion == '/' || operacion == '%') && operandoB <= NULO && operandoB >= NULO){
        cout << "Operendo B debe ser mayor a 0" << endl;
        cout << "Presione <ENTER> para continuar . . ." << endl;
        cin.get();
        cin.get();
        return false;
    }
    return true;
}

bool listaIDsContiene(int id){
    Proceso *p;
    for(unsigned int i = 0; i < procesos.size(); i++){
        p = procesos[i];
        if(p->getId() == id){
            return true;
        }
    }
    return false;
}

void creaLotesDeProcesos(){
    cout << "PROCESOS REGISTRADOS, INICIARA PROCESAMIENTO POR LOTES" << endl;
    cout << "Presione <ENTER> para continuar . . ." << endl;
    cin.get();
    cin.get();
    system("cls || clear");
    procesamientoPorLotes();
}


void procesamientoPorLotes(){
    Proceso *p;
    int cuentaProcesos = 0;
    lotesPendientes = lotes -1;
    for(indice = 0; indice < procesos.size(); indice++, cuentaProcesos++){
        if(cuentaProcesos == RANURAS){
            lotesPendientes--;
            cuentaProcesos = 0;
        }
        p = procesos[indice];
        ejecutaProceso(p);
    }
    cout << endl << "Presione <ENTER> para terminar . . ." << endl;
    cin.get();
    cin.get();
}

void ejecutaProceso(Proceso* p){
    int tiempoTranscurrido, tiempoRestante;
    tiempoRestante = p->getTiempoMaxEstimado();
    tiempoTranscurrido = NULO;
    calculaOperacion(p);
    for(int i = NULO; i < p->getTiempoMaxEstimado(); i++){
        system("cls || clear");
        imprimeDatos(p,tiempoTranscurrido,tiempoRestante);
        contadorGlobal++;
        tiempoTranscurrido++;
        tiempoRestante--;
        imprimirLoteActual();
        imprimirProcesosCompletados();
        Sleep(1000);
    }
    system("cls || clear");
    procesosTerminados.push_back(p);
    imprimeDatos(p,tiempoTranscurrido,tiempoRestante);
    imprimirLoteActual();
    imprimirProcesosCompletados();
}

void imprimirProcesosCompletados(){
    Proceso *p;
    int cuentaLotes = 1;
    int cuentaProcesos  = 0;
    cout << endl << "------------PROCESOS TERMINADOS-----------" << endl;
    cout << "ID\tOPERACION\tRESULTADO" << endl;
    cout << "LOTE #" << cuentaLotes << endl;
    for(unsigned int i = 0; i < procesosTerminados.size(); i++){
        if(cuentaProcesos == RANURAS){
            cuentaLotes++;
            cout << "LOTE #" << cuentaLotes << endl;
            cuentaProcesos = 0;
        }
        p = procesos[i];
        cout << p->getId() << "\t" << p->getOperandoA() << " " << p->getOperacion() << " "
             << p->getOperandoB() << " = \t" << p->getResultado() << endl;
        cuentaProcesos++;
    }
}

void imprimirLoteActual(){
    Proceso *p;
    cout << endl << "-------------LOTE EN EJECUCION-------------" << endl;
    cout << "PROGRAMADOR\tTME" << endl;
    unsigned int limiteLote = (lotes-lotesPendientes) * RANURAS;
    for(unsigned int i = indice;  i < limiteLote && i < procesos.size(); i++){
        p = procesos[i];
        cout << p->getNombreProgramador() << "\t\t" << p->getTiempoMaxEstimado() << endl;
    }
}

void imprimeDatos(Proceso *p,int tTranscurrido, int tRestante){
    if(lotesPendientes <= NULO){
        lotesPendientes = NULO;
    }
    cout << "LOTES PENDIENTES: " << lotesPendientes << endl;
    cout << "CONTADOR GLOBAL: " << contadorGlobal << endl << endl;
    cout << "-------------------PROCESO EN EJECUCION--------------------" << endl;
    cout << "ID\tPROGRAMADOR\tTME\tOPERACION\t TT\tTR" << endl;
    cout << p->toString() << "\t\t " << tTranscurrido << "\t" << tRestante << endl;
}

void calculaOperacion(Proceso* p){
    switch(p->getOperacion()){
        case '+':   p->setResultado( p->getOperandoA() + p->getOperandoB());    break;
        case '-':   p->setResultado( p->getOperandoA() - p->getOperandoB());    break;
        case '*':   p->setResultado( p->getOperandoA() * p->getOperandoB());    break;
        case '/':   p->setResultado( p->getOperandoA() / p->getOperandoB());    break;
        case '%':   p->setResultado((int)p->getOperandoA() % (int)p->getOperandoB());    break;
        case '^':   p->setResultado( pow(p->getOperandoA(),p->getOperandoB())); break;
        default:    p->setResultado( p->getOperandoA() + p->getOperandoB());    break;
    }
}
