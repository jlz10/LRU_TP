#include "cabeceras.h"

int main(int argc, char* argv[])
{
    t_lru_cache cache;
    clock_t t1,t2;
    FILE * fpruebas, * fusers_feed3000, *fusers_feed500;

    fpruebas =  fopen("LotePruebas\\posteos.bin", "rb");
    if(fpruebas == NULL){
        printf("Error al abrir el archivo de posteos\n");
        return ERR_ARCHIVO;
    }

    fusers_feed3000 =  fopen("LotePruebas\\feed_3000.bin", "rb");
    if(fusers_feed3000 == NULL){
        fclose(fpruebas);  
        printf("Error al abrir el archivo de feeds\n");
        return ERR_ARCHIVO;
    }

    fusers_feed500 =  fopen("LotePruebas\\feed_500.bin", "rb");
    if(fusers_feed500 == NULL){
        fclose(fusers_feed3000);
        fclose(fpruebas);  
        printf("Error al abrir el archivo de feeds\n");
        return ERR_ARCHIVO;
    }

    printf("Procesando feeds...\n");
    printf("------CON CACHE -----\n");
    printf("3000 usuarios y cache con 12 capacidad:\n");
    t1 = clock();

    // Creamos la cache con capacidad 12
    crear_lrucache(&cache, 12);
    
    // Procesamos los feeds
    procesar_feeds(&cache, fpruebas, fusers_feed3000);

    vaciar_lrucache(&cache);

    t2 = clock();

    printf("tiempo de ejecucion cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));

    printf("------SIN CACHE-----\n");
    printf("3000 usuarios:\n");
    t1 = clock();

    procesar_feeds_sin_cache(fpruebas, fusers_feed3000);

    t2 = clock();

    printf("tiempo de ejecucion sin cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));
    printf("500 usuarios:\n");
    
    t1 = clock();

    procesar_feeds_sin_cache(fpruebas, fusers_feed500);

    t2 = clock();

    printf("tiempo de ejecucion sin cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));
    
    printf("------CON CACHE -----\n");
    printf("500 usuarios y cache con 7 capacidad:\n");
    
    t1 = clock();

     // Creamos la cache con capacidad 12
    crear_lrucache(&cache, 7);
    
    // Procesamos los feeds
    procesar_feeds(&cache, fpruebas, fusers_feed500);

    vaciar_lrucache(&cache);

    t2 = clock();

    printf("tiempo de ejecucion sin cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));

    printf("500 usuarios y cache con 12 capacidad:\n");
    
    t1 = clock();

     // Creamos la cache con capacidad 12
    crear_lrucache(&cache, 12);
    
    // Procesamos los feeds
    procesar_feeds(&cache, fpruebas, fusers_feed500);

    vaciar_lrucache(&cache);

    t2 = clock();

    printf("tiempo de ejecucion sin cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));

    fclose(fusers_feed500);
    fclose(fusers_feed3000);
    fclose(fpruebas);
    
    

    return 0;

}