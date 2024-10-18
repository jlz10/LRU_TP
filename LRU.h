#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED

#include "Lista.h"

typedef struct{
    tLista pl;
    size_t cap;
    size_t tam_actual;
}
t_lru_cache;

typedef int (Cmp*)(const void*, const void*);

void crear_lrucache(t_lru_cache* cache, size_t capacidad);
int agregar_lrucache(t_lru_cache* cache, void* p, size_t tamDato);
int obtener_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp);
void borrar_lrucache(t_lru_cache* cache, void*, size_t tamDato);


#endif // LRU_H_INCLUDED
