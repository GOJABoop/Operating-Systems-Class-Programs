#ifndef PROCESO_H_INCLUDED
#define PROCESO_H_INCLUDED
#include <sstream>

class Proceso{
private:
    char operacion;
    int operandoA;
    int operandoB;
    int resultado;
    int tiempoMaxEstimado;
    int id;
    int tiempoTranscurrido;
    int tiempoRestante;
    bool error;
public:
    Proceso(){
        operacion = '\0';
        tiempoMaxEstimado = 0;
        id = 0;
        operandoA = 0;
        operandoB = 0;
        resultado = 0;
        tiempoTranscurrido = 0;
        tiempoRestante = 0;
        error = false;
    }
    //Setters
    void setOperacion(char operacion){
        this->operacion = operacion;
    }
    void setTiempoMaxEstimado(int tiempo){
        tiempoMaxEstimado = tiempo;
    }
    void setId(int id){
        this->id = id;
    }
    void setOperandoA(int a){
        operandoA = a;
    }
    void setOperandoB(int b){
        operandoB = b;
    }
    void setResultado(int r){
        resultado = r;
    }
    void setTiempoTranscurrido(int t){
        tiempoTranscurrido = t;
    }
    void setTiempoRestante(int t){
        tiempoRestante = t;
    }
    void setError(bool e){
        error = e;
    }
    //Getters
    char getOperacion(){
        return operacion;
    }
    int getTiempoMaxEstimado(){
        return tiempoMaxEstimado;
    }
    int getId(){
        return id;
    }
    int getOperandoA(){
        return operandoA;
    }
    int getOperandoB(){
        return operandoB;
    }
    int getResultado(){
        return resultado;
    }
    int getTiempoTranscurrido(){
        return tiempoTranscurrido;
    }
    int getTiempoRestante(){
        return tiempoRestante;
    }
    bool getError(){
        return error;
    }
    std::string toString(){
        std::stringstream ss;
        ss << id << " \t" << tiempoMaxEstimado << " \t" << tiempoTranscurrido << " \t"
           << tiempoRestante <<"\t" << operandoA << " " << operacion << " " << operandoB;
        return ss.str();
    }
};

#endif // PROCESO_H_INCLUDED
