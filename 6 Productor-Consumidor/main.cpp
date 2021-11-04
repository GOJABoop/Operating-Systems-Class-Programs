#include <iostream>
#include "interfaz.h"

int main(){
    Interfaz *i = new Interfaz();
    delete i;
    i = nullptr;
    return 0;
}
