#include "Tweener.h"


int procesar_feeds(t_lru_cache* cache, FILE * posteos, FILE * users_feed) {
  tFeed feed;
  tUser user;
  tTweet tweet;
  int i, user_acum = 0;
  clock_t t1,t2;

  fseek(users_feed,0,SEEK_SET);

  //Leemos el primer usuario, comenzamos el clock
  t1 = clock();
  fread(&user,sizeof(tUser),1,users_feed);
  while (!feof(users_feed)) {
    
    for (i = 0; i < TAM_FEED; i++) {
      tweet.id = user.feed[i];
      
      if (buscar_tweet(&tweet, cache, posteos)){
        strcpy(feed.user, user.user);
        feed.feed[i] = tweet;
        
      }else{
        return ERR_MEM;
      }
      
    }

    user_acum++;
    fread(&user,sizeof(tUser),1,users_feed);
  }

  t2 = clock();
  printf("tiempo de ejecucion cache promedio procesar un feed de usuario: %f \n", ((float)(t2-t1)/(CLOCKS_PER_SEC*user_acum)));
  printf("tiempo de ejecucion cache promedio de buscar un Tweet: %.14lf \n", ((double)(t2-t1)/(CLOCKS_PER_SEC*user_acum*TAM_FEED)));
    

  return TODO_OK;
}

int procesar_feeds_sin_cache( FILE * posteos, FILE * users_feed) {
    tFeed feed;
    tUser user;
    tTweet tweet;
    int i, user_acum = 0;
    clock_t t1,t2;
    
    
    fseek(users_feed,0,SEEK_SET);
    //Leemos el primer usuario, comenzamos el clock
    t1 = clock();
    fread(&user,sizeof(tUser),1,users_feed);
    while (!feof(users_feed)) {

      for(i = 0; i < TAM_FEED; i++){
        tweet.id = user.feed[i];
        if((buscar_tweet_sin_cache(&tweet, posteos))){
          strcpy(feed.user, user.user);
          feed.feed[i] = tweet;
        }
      }

      user_acum++;
      fread(&user,sizeof(tUser),1,users_feed);
    }

    t2 = clock();
    printf("tiempo de ejecucion sin cache promedio procesar un feed de usuario: %f \n", ((float)(t2-t1)/(CLOCKS_PER_SEC*user_acum)));
    printf("tiempo de ejecucion sin cache promedio de buscar un Tweet: %.14lf \n", ((double)(t2-t1)/(CLOCKS_PER_SEC*user_acum*TAM_FEED)));


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

