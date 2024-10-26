#ifndef TWEENER_H_INCLUDED
#define TWEENER_H_INCLUDED

#include "LRU.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int cargar_posteos_cache(t_lru_cache* cache, FILE * posteos,  size_t capacidad);

int procesar_feed(t_lru_cache* cache, FILE * posteos, tUser * user, tFeed * feed);
int procesar_feed_sin_cache(FILE * posteos, FILE * users_feed, tUser * user);

int procesar_user(t_lru_cache* cache, FILE * posteos, FILE * users_feed, tUser * user);
int procesar_user_sin_cache(FILE * posteos, FILE * users_feed, tUser * user);

int buscar_tweet(tTweet * tweet, t_lru_cache* cache, FILE * posteos);
int buscar_tweet_sin_cache(tTweet * tweet, FILE * posteos);

int cmpTweet(const void * elem1, const void * elem2);

#endif // TWEENER_H_INCLUDED