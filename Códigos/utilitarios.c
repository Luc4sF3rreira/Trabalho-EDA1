#include <stdio.h>

#include "estruturas.h"

void limparBuffer() { //Tira o \n que sobrou no buffer após um scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

