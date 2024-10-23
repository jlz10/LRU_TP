#include "LRU.h"

void crear_lrucache(t_lru_cache* cache, size_t capacidad){
    cache->pl = NULL; //Lista inicializada en NULL
    cache->cap = capacidad; //Le ponemos la capacidad del usuario
    cache->tam_actual = 0; //El tamano actual de la lista
}

int agregar_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;
    tNodo* nue = NULL;

    //Tengo entendido que el profe justamente no quiere llamado a funcion inecesarios, esto es por eso?
    //Siento que queda ya demasiado compleja la operacion

    //Si existe el dato, remplazamos la info y lo ponemos como el primer nodo
    while(act){

        if(cmp(act->info, p) == 0){

            free(act->info);
            act->tamElem = tamDato;

            if((act->info = malloc(tamDato)) == NULL)
                return ERR_MEM;

            memcpy(act->info, p, tamDato);
            
            if(ant){ //Si no existe el anterior no se mueve
                ant->sig = act->sig;
                act->sig = cache->pl;
                cache->pl = act;
            }

            return TODO_OK;

        }

        ant = act;
        act = act->sig;
    }


    //Cuando se llena la cache se debe eliminar el ultimo!!

    if (cache->tam_actual == cache->cap) {
        act = cache->pl; //Utilice los mismos nodos inicializados de arriba
        ant = NULL;

        while (act->sig) {
            ant = act;
            act = act->sig;
        }
        if (ant)
            ant->sig = NULL;

        free(act->info);
        free(act);
        cache->tam_actual--;
    }

    //Operacion para insertar un nuevo dato

    //probar puede fallar
    if((nue = (tNodo*) malloc(sizeof(tNodo))) == NULL||(nue->info = malloc(tamDato))  == NULL){
        free(nue);
        return ERR_MEM;
    }

    nue->tamElem = tamDato;
    memcpy(nue->info, p, tamDato);
    nue->sig = cache->pl;
    cache->pl = nue;
    cache->tam_actual++;

    return TODO_OK;
}

int obtener_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;

    while(act){
        if(cmp(act->info, p) == 0){

            ant->sig = act->sig; //Matcheamos el siguiente
            act->sig = cache->pl; //Ponemos segundo al nodo que anteriormente era primero
            cache->pl = act; // apuntamos la lista al primer nodo
            memcpy(p, act->info, MIN(tamDato, act->tamElem));
            return TODO_OK;

        }
        ant = act;
        act = act->sig;
    }

    return NOT_FOUND;
}

int borrar_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;

    //buscamos el nodo a borrar
    while(act){
        if(cmp(act->info, p) == 0){

            if(ant)
                ant->sig = act->sig; // puede ser null tambien, por eso se apunta al siguiente
            else
                cache->pl = act->sig; // apuntando a un solo nodo.

            free(act->info);
            free(act);
            cache->tam_actual--;

            return TODO_OK; //Se borro exitosamente.
        }

        ant = act;
        act = act->sig;

    }
    return NOT_FOUND;
}

void vaciar_lrucache(t_lru_cache* cache){
    tNodo* elim = cache->pl;
    tNodo* aux = NULL;

    while (elim) {
        aux = elim->sig;
        free(elim->info);
        free(elim);
        elim = aux;
    }

    cache->pl = NULL;
    cache->tam_actual = 0;
}


