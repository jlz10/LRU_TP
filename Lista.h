#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


//LISTA

typedef struct sNodo{
    void* info;
    size_t tamElem;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;


#endif // LISTA_H_INCLUDED
