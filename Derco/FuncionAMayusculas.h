//
// Created by gerar on 6/26/2023.
//
#include "ctype.h"
#ifndef DERCO_FUNCIONAMAYUSCULAS_H
#define DERCO_FUNCIONAMAYUSCULAS_H
void AMayusculas(char* str) {
    int i = 0;
    while (str[i]) {
        str[i] = toupper(str[i]);
        i++;
    }
}

#endif //DERCO_FUNCIONAMAYUSCULAS_H
