#include "cabeceras.h"

int main(int argc, char* argv[])
{
    t_lru_cache cache;
    clock_t t1,t2;
    FILE * fpruebas, * fusers_feed;

    fpruebas =  fopen("LotePruebas\\posteos.bin", "rb");
    if(fpruebas == NULL){
        printf("Error al abrir el archivo de posteos\n");
        return 1;
    }

    fusers_feed =  fopen("LotePruebas\\feed_5000.bin", "rb");
    if(fusers_feed == NULL){
        fclose(fpruebas);  
        printf("Error al abrir el archivo de feeds\n");
        return 1;
    }


    t1 = clock();

    // Creamos la cache con capacidad 7
    crear_lrucache(&cache, 15);
    
    // Procesamos los feeds
    procesar_feeds(&cache, fpruebas, fusers_feed);

    vaciar_lrucache(&cache);

    t2 = clock();

    printf("tiempo de ejecucion cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));


    t1 = clock();

    procesar_feeds_sin_cache(fpruebas, fusers_feed);

    t2 = clock();

    printf("tiempo de ejecucion sin cache: %f \n", ((float)(t2-t1)/CLOCKS_PER_SEC));

    fclose(fusers_feed);
    fclose(fpruebas);
    
    

    return 0;

}