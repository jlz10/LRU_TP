#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED

#include "Lista.h"

#include <string.h>

#define MIN(X,Y)( ((X) < (Y))? (X) : (Y) )
#define TODO_OK 1
#define ERR_MEM 0

//LISTA

typedef struct sNodo{
    void* info;
    size_t tamElem;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;


typedef struct{
    tLista pl;
    size_t cap;
    size_t tam_actual;
}
t_lru_cache;

typedef int(*Cmp)(const void*, const void*);

void crear_lrucache(t_lru_cache* cache, size_t capacidad);
int agregar_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp);
int obtener_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp);
int borrar_lrucache(t_lru_cache* cache, void*, size_t tamDato, Cmp cmp);
void vaciar_lrucache(t_lru_cache* cache);
void mostrar_lrucache(t_lru_cache* cache);


int cmpInt(const void* a, const void* b);

#endif // LRU_H_INCLUDED
