#include <stdio.h>
#include "blocoMemoria.h"
#include "funcAloca.h"

Bloco disco[TAM_DISCO];

int main() {
    iniciarDisco(disco);
    menu(disco);
    return 0;
}
