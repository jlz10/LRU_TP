#include "LRU.h"
void crear_lrucache(t_lru_cache* cache, size_t capacidad){
    cache->pl = NULL; //Lista inicializada en NULL
    cache->cap = capacidad; //Le ponemos la capacidad del usuario
    cache->tam_actual = 0; //El tamaño actual de la lista
}

int agregar_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;

    //Si existe el dato, remplazamos la info y lo ponemos como el primer nodo
    while(act){
        if(cmp(act->info, p) == 0){
            free(act->info);
            act->tamElem = tamDato;
            act->info = malloc(tamDato);
            if(!(act->info)){
                return 0;
            }
            memcpy(act->info, p, tamDato);
            if(ant){
                ant->sig = act->sig;
                act->sig = ant;
                cache->pl = act;
            }
            return 1;
        }
        ant = act;
        act = act->sig;
    }


    //Operacion para insertar un nuevo dato

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue){
        return 0;
    }
    nue->info = malloc(tamDato);
    if(!nue->info){
        free(nue);
        return 0;
    }
    nue->tamElem = tamDato;
    memcpy(nue->info, p, tamDato);
    nue->sig = cache->pl;
    cache->pl = nue;
    cache->tam_actual++;

    //Cuando se llena la cache se debe eliminar el ultimo!!

    if (cache->tam_actual > cache->cap) {
        act = cache->pl; //Utilice los mismos nodos inicializados de arriba
        ant = NULL; //Utilice los mismos nodos inicializados de arriba

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
    return 1;
}

int obtener_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;

    while(act){
        if(cmp(act->info, p) == 0){
            ant->sig = act->sig; //Matcheamos el siguiente
            act->sig = ant; //Ponemos al inicio el nodo encontrado ya que se uso
            cache->pl = act; // apuntamos la lista al primer nodo mas usado
            memcpy(p, act->info, MIN(tamDato, act->tamElem));
            return 1;
        }
        ant = act;
        act = act->sig;
    }

    return 0;
}

int borrar_lrucache(t_lru_cache* cache, void* p, size_t tamDato, Cmp cmp){
    tNodo* act = cache->pl;
    tNodo* ant = NULL;

    //buscamos el nodo a borrar
    while(act){
        if(cmp(act->info, p) == 0){
            if(ant){
                ant->sig = act->sig; // puede ser null tambien, por eso se apunta al siguiente
            }
            else{
                cache->pl = act->sig; // apuntando a un solo nodo.
            }
            free(act->info);
            free(act);
            cache->tam_actual--;
            return 1; //Se borro exitosamente.
        }
        ant = act;
        act = act->sig;
    }
    return 0; //No se borro el dato.
}

void vaciar_lrucache(t_lru_cache* cache){
    tNodo* elim = cache->pl;

    while (elim) {
        tNodo* aux = elim->sig;
        free(elim->info);
        free(elim);
        elim = aux;
    }

    cache->pl = NULL;
    cache->tam_actual = 0;
}

void mostrar_lrucache(t_lru_cache* cache) {
    tNodo* act = cache->pl;
    printf("Contenido de la caché (de más reciente a menos reciente):\n");

    while (act) {
        printf("%d -> ", *(int*)(act->info));  // Testing de enteros
        act = act->sig;
    }
    printf("NULL\n");
}


int cmpInt(const void* a, const void* b){
    int * e1 = (int*) a;
    int * e2 = (int*) b;
    return *e1 - *e2;
}
