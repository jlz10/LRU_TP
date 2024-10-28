#ifndef TWEENER_H_INCLUDED
#define TWEENER_H_INCLUDED

#include "LRU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FEED 20
#define TAM_TEXT 141
#define TAM_NAME 15

typedef struct{
    int id;
    char texto[TAM_TEXT];
}tTweet;

typedef struct{
    char user[TAM_NAME];
    int feed[TAM_FEED];
}tUser;

typedef struct{
    char user[TAM_NAME];
    tTweet feed[TAM_FEED];
}tFeed;

typedef int(*Cmp)(const void*, const void*);

int procesar_feeds(t_lru_cache* cache, FILE * posteos, FILE * users_feed);
int procesar_feeds_sin_cache( FILE * posteos, FILE * users_feed); 

int buscar_tweet(tTweet * tweet, t_lru_cache* cache, FILE * posteos); //ESTA
int buscar_tweet_sin_cache(tTweet * tweet, FILE * posteos); //ESTA

int cmpTweet(const void * elem1, const void * elem2);

#endif // TWEENER_H_INCLUDED