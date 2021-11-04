#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED
#include <cstdlib>
#include <unistd.h>
#include <conio.h>
#include <Windows.h>
#include "contenedor.h"
#include "sorteo.h"
#include "constantes.h"

using namespace std;

class Interfaz{
private:
    Contenedor *elementos;
    bool ejecutar;
    int turno;
    int cantidad;
public:
    Interfaz(){
        elementos = new Contenedor();
        ejecutar = true;
        productor_consumidor();
    }
    ~Interfaz(){
        delete elementos;
        elementos = nullptr;
    }
private:
    void productor_consumidor(){
        cout << ejecutar << endl;
        while(ejecutar){
            realizaProceso();
        }
        cout << "Ha terminado el proceso." << endl;
    }

    void realizaProceso(){
        char tecla;
        turno = siguienteTurno();
        cantidad = dameCantidad();
        for(int i = 0; i < cantidad; i++){
            turno == PRODUCTOR ? elementos->produce() : elementos->consume();
            imprimeEstados();
            if(kbhit()) tecla = getch();
            if(int(tecla) == ESC){
                ejecutar = false;
                break;
            }
            Sleep(SEGUNDO);
        }
    }

    void imprimeEstados(){
        system("cls || clear");
        cout << "     PRODUCTOR-CONSUMIDOR" << endl;
        if(turno == PRODUCTOR){
            cout << "Productor:  DESPIERTO" << endl;
            cout << "Consumidor: DORMIDO" << endl << endl;
        }
        else{
            cout << "Productor:  DORMIDO" << endl;
            cout << "Consumidor: DESPIERTO" << endl << endl;
        }
        cout << elementos->aCadena() << endl;
        for(int i = 1; i < CAPACIDAD_CONTENEDOR+1 ;i++){
            if(i < 10) cout <<" " << i << " ";
            else cout << " " << i;
        }
        cout << endl << endl;
        if(elementos->estaLLeno()){
            cout << "Intentando producir" << endl;
        }
        if(elementos->estaVacio() && turno == CONSUMIDOR){
            cout << "Intentando consumir" << endl;
        }
    }
};

#endif // INTERFAZ_H_INCLUDED
