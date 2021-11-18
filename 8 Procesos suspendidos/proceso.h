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
    int tamanio;
    int tiempoTranscurrido;
    int tiempoRestante;
    int tiempoBloqueado;
    int tiempoLlegada; //Tiempo en que entra a sistema contadorGlobal
    int tiempoFinalizacion; //Tiempo en el que proceso termino contadorGlobal
    int tiempoServicio; //Tiempo que paso en procesador tiempoTranscurrido
    int tiempoRetorno;  //tiempo desde que el proceso llega hasta que termina TiempoFinal - tiempoLlegada
    int tiempoEspera;   //Tiempo que el proceso ha estado esperando para usar el procesadortiempoRetorno - tiempoServicio
    int tiempoRespuesta; //Contador global - tiempoLlega (solo la primera vez); Tiempo transcurrido desde que llega hasta que es atendido por primera vez.
    bool respondido;
    bool error;
public:
    Proceso(){
        operacion = '\0';
        tiempoMaxEstimado = 0;
        id = 0;
        operandoA = 0;
        operandoB = 0;
        resultado = 0;
        tamanio = 0;
        tiempoTranscurrido = 0;
        tiempoRestante = 0;
        tiempoBloqueado = 0;

        tiempoLlegada = 0;
        tiempoFinalizacion = 0;
        tiempoServicio = 0;
        tiempoRetorno = 0;
        tiempoEspera = 0;
        tiempoRespuesta = 0;

        respondido = false;
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
    void setTiempoBloqueado(int t){
        tiempoBloqueado = t;
    }
    void setTiempoLlegada(int t){
        tiempoLlegada = t;
    }
    void setTiempoFinalizacion(int t){
        tiempoFinalizacion = t;
    }
    void setTiempoServicio(int t){
        tiempoServicio = t;
    }
    void setTiempoRetorno(int t){
        tiempoRetorno = t;
    }
    void setTiempoEspera(int t){
        tiempoEspera = t;
    }
    void setTiempoRespuesta(int t){
        tiempoRespuesta = t;
    }
    void setRespondido(bool r){
        respondido = r;
    }
    void setError(bool e){
        error = e;
    }
    void setTamanio(int t){
        tamanio = t;
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
    int getTiempoBloqueado(){
        return tiempoBloqueado;
    }
    int getTiempoLlegada(){
        return tiempoLlegada;
    }
    int getTiempoFinalizacion(){
        return tiempoFinalizacion;
    }
    int getTiempoServicio(){
        return tiempoServicio;
    }
    int getTiempoRetorno(){
        return tiempoRetorno;
    }
    int getTiempoEspera(){
        return tiempoEspera;
    }
    int getTiempoRespuesta(){
        return tiempoRespuesta;
    }
    int getTamanio(){
        return tamanio;
    }
    bool fueRespondido(){
        return respondido;
    }
    bool getError(){
        return error;
    }
    std::string toString(){
        std::stringstream ss;
        ss << id << " \t" << tiempoMaxEstimado << " \t" << tiempoTranscurrido << " \t"
           << tiempoRestante <<"\t" << operandoA << " " << operacion << " " << operandoB
           << " \t" << tamanio;
        return ss.str();
    }
};

#endif // PROCESO_H_INCLUDED
