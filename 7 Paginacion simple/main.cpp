#include <iostream>
#include "principal.h"

using namespace std;

int main(){
    Principal *p = new Principal();
    delete p;
    p = nullptr;
    return 0;
}
