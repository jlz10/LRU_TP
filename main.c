#include "LRU.h"
#include <time.h>

int main()
{
    t_lru_cache cache;
    int dato;
    clock_t t1,t2;
    t1 = clock();
    // Creamos la cache con capacidad 3
    crear_lrucache(&cache, 3);

    // Agregamos algunos datos
    dato = 1;
    agregar_lrucache(&cache, &dato, sizeof(int), cmpInt);
    printf("Se agrego el dato: %d\n", dato);
    //1

    dato = 2;
    agregar_lrucache(&cache, &dato, sizeof(int), cmpInt);
    printf("Se agrego el dato: %d\n", dato);

    //2 1
    dato = 3;
    agregar_lrucache(&cache, &dato, sizeof(int), cmpInt);
    printf("Se agrego el dato: %d\n", dato);

    //3 2 1
    int clave = 2;
    int resultado = obtener_lrucache(&cache, &clave, sizeof(int), cmpInt);
    if (resultado)
        printf("Se obtuvo el dato: %d\n", clave);
    else

        printf("Dato no encontrado: %d\n", clave);

    //Se deberia eliminar el ultimo (3).
    dato = 4;
    agregar_lrucache(&cache, &dato, sizeof(int), cmpInt);
    printf("Se agreg� el dato: %d\n", dato);

    //testing de enteros!
    mostrar_lrucache(&cache);

    vaciar_lrucache(&cache);

    sleep(1);

    t2 = clock();

    printf("tiempo de ejecucion: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));
}


void mostrar_lrucache(t_lru_cache* cache) {

    tNodo* act = cache->pl;

    printf("Contenido de la cach� (de m�s reciente a menos reciente):\n");

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

//generas lote de pruebas de posteos
//generas lotes de pruebas de feeds
    //compara sin y con cache
    //medir tiempos
    //probar con varias capacidades
