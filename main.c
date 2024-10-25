#include "Lista.h"
#include "LRU.h"
#include "main.h"

int generarArchivo(char* userArch);

int main(int argc, char* argv[])
{
    generarArchivo(argv[ARCH_POS]);
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
