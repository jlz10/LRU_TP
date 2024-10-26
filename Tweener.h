#ifndef TWEENER_H_INCLUDED
#define TWEENER_H_INCLUDED

#include "LRU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int id;
    char texto[140];
}tTweet;

typedef struct{
    char user[15];
    int feed[20];
}tUser;

typedef struct{
    char user[15];
    tTweet feed[20];
}tFeed;

typedef int(*Cmp)(const void*, const void*);

//agrega los posteos al cache
int cargar_posteos_cache(t_lru_cache* cache, FILE * posteos); //ESTA

int procesar_feed(tFeed * feed,tUser * user, t_lru_cache* cache, FILE * posteos);
int procesar_feed_sin_cache(tFeed * feed,tUser * user,FILE * posteos);

int procesar_feeds(t_lru_cache* cache, FILE * posteos, FILE * users_feed);
int procesar_feeds_sin_cache( FILE * posteos, FILE * users_feed); 

int buscar_tweet(tTweet * tweet, t_lru_cache* cache, FILE * posteos); //ESTA
int buscar_tweet_sin_cache(tTweet * tweet, FILE * posteos); //ESTA

int cmpTweet(const void * elem1, const void * elem2);

#endif // TWEENER_H_INCLUDED