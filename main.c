#include "LRU.h"
#include "main.h"

int generarArchivo(char* userArch);

int main(int argc, char* argv[])
{
    generarArchivo(argv[ARCH_POS]);
    return 1;
}

int generarArchivo(char* userArch){
    Post tPost[] = {
        {1, "lol"},
        {2, "Waaao"}
    };

    FILE* pf = fopen(userArch, "wb");
    fwrite(&tPost, sizeof(Post), 2, pf);
    fclose(pf);
    return 1;
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