#ifndef PROCESO_H_INCLUDED
#define PROCESO_H_INCLUDED
#include <sstream>

class Proceso{
private:
    std::string nombreProgramador;
    char operacion;
    double operandoA;
    double operandoB;
    double resultado;
    int tiempoMaxEstimado;
    int id;
public:
    Proceso(){
        nombreProgramador = "NONE";
        operacion = '\0';
        tiempoMaxEstimado = 0;
        id = 0;
        operandoA = 0;
        operandoB = 0;
        resultado = 0;
    }

    void setNombreProgramador(std::string nombre){
        nombreProgramador = nombre;
    }
    void setOperacion(char operacion){
        this->operacion = operacion;
    }
    void setTiempoMaxEstimado(int tiempo){
        tiempoMaxEstimado = tiempo;
    }
    void setId(int id){
        this->id = id;
    }
    void setOperandoA(double a){
        operandoA = a;
    }
    void setOperandoB(double b){
        operandoB = b;
    }
    void setResultado(double r){
        resultado = r;
    }

    std::string getNombreProgramador(){
        return nombreProgramador;
    }
    char getOperacion(){
        return operacion;
    }
    int getTiempoMaxEstimado(){
        return tiempoMaxEstimado;
    }
    int getId(){
        return id;
    }
    double getOperandoA(){
        return operandoA;
    }
    double getOperandoB(){
        return operandoB;
    }
    double getResultado(){
        return resultado;
    }
    std::string toString(){
        std::stringstream ss;
        ss << id << "\t" << nombreProgramador << "\t\t" << tiempoMaxEstimado << "\t" << operandoA
           << " " << operacion << " " << operandoB;
        return ss.str();
    }
};

#endif // PROCESO_H_INCLUDED
