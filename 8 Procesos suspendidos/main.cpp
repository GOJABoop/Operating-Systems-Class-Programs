#include <iostream>
#include "interfaz.h"

using namespace std;

int main(){
    Interfaz *i = new Interfaz();
    delete i;
    i = nullptr;
    return 0;
}
