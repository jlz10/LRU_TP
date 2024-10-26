#include "Tweener.h"

int cargar_posteos_cache(t_lru_cache* cache, FILE * posteos){

  int i = 0;
  tTweet tweet;

  fread(&tweet,sizeof(tweet),1,posteos);
  while(!feof(posteos)||cache->cap<i){
    if(!agregar_lrucache(cache,&tweet,sizeof(tweet),cmpTweet))
      return ERR_MEM;
    fread(&tweet,sizeof(tweet),1,posteos);
    i++;
  }

  return TODO_OK;
}

int procesar_feed(tFeed * feed, tUser * user, t_lru_cache* cache, FILE * posteos){
    tTweet tweet;

    for (int i = 0; i < 20; i++) {
        tweet.id = user->feed[i];
        if (buscar_tweet(&tweet, cache, posteos)){
            strcpy(feed->user, user->user);
            feed->feed[i] = tweet;
        }
    }
    return TODO_OK;
}

int procesar_feed_sin_cache(tFeed * feed, tUser * user, FILE * posteos){
    int i;
    tTweet tweet;

    for(i = 0; i < 20; i++){
      tweet.id = user->feed[i];
      if((buscar_tweet_sin_cache(&tweet, posteos))){
        strcpy(feed->user, user->user);
        feed->feed[i] = tweet;
      }
    }

    return TODO_OK;
}

int procesar_feeds(t_lru_cache* cache, FILE * posteos, FILE * users_feed) {
    tFeed feed;
    tUser user;

    while (fread(&user, sizeof(user), 1, users_feed) == 1) {
        if (procesar_feed(&feed, &user, cache, posteos) != TODO_OK) {
            return ERR_MEM;
        }
    }

    if (ferror(users_feed)) {
        perror("Error al leer el archivo de usuarios");
        return ERR_MEM;
    }

    return TODO_OK;
}

int procesar_feeds_sin_cache( FILE * posteos, FILE * users_feed) {
    tFeed feed;
    tUser user;

    while (fread(&user, sizeof(user), 1, users_feed) == 1) {
        if (procesar_feed_sin_cache(&feed, &user, posteos) != TODO_OK) {
            return ERR_MEM;
        }
    }

    if (ferror(users_feed)) {
        perror("Error al leer el archivo de usuarios");
        return ERR_MEM;
    }

    return TODO_OK;
}

int buscar_tweet(tTweet * tweet, t_lru_cache* cache, FILE * posteos){
  if(obtener_lrucache(cache,tweet,sizeof(tTweet),cmpTweet))
    return TODO_OK;

  fseek(posteos,tweet->id-1*sizeof(tTweet),SEEK_SET);
  fread(tweet,sizeof(tTweet),1,posteos);

  if(agregar_lrucache(cache,tweet,sizeof(tTweet),cmpTweet))
    return TODO_OK;
  else
    return ERR_MEM;
}

int buscar_tweet_sin_cache(tTweet * tweet, FILE * posteos){

  fseek(posteos,tweet->id-1*sizeof(tTweet),SEEK_SET);
  fread(tweet,sizeof(tTweet),1,posteos);

  return TODO_OK;
}

int cmpTweet(const void * elem1, const void * elem2){
  return ((tTweet *)elem1)->id - ((tTweet *)elem2)->id;
}

