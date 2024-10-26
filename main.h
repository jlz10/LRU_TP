#ifndef MAIN_H
#define MAIN_H

#define TAM_POST 50000
#define TAM_TEXT 142
#define TAM_NAME 16
#define TAM_FEED 20
#define ARCH_POS 1


//Si quieren cambiar las estructuras con otro nombre mejor, lo puse asi

typedef struct{
    int id;
    char text[TAM_TEXT];
}
Post;

typedef struct{
    char user[TAM_NAME];
    int feed[TAM_FEED];
}
User;



#endif // MAIN_H
