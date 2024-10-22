#include "Lista.h"
#include "LRU.h"

int main()
{
    t_lru_cache cache;
    int dato;

    // Creamos la caché con capacidad 3
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
    printf("Se agregó el dato: %d\n", dato);

    //testing de enteros!
    mostrar_lrucache(&cache);
}
