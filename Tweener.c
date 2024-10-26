#include "Tweener.h"

int cargar_cache(t_lru_cache* cache, FILE * posteos,  size_t capacidad){

  int i = 0;
  tTweet tweet;

  fread(&tweet,sizeof(tweet),1,posteos);
  while(!feof(posteos)||capacidad<i){
    if(!agregar_lrucache(cache,&tweet,sizeof(tweet),cmpTweet))
      return ERR_MEM;
    fread(&tweet,sizeof(tweet),1,posteos);
    i++;
  }

  return TODO_OK;
}


int procesar_feeds(t_lru_cache* cache, FILE * posteos, FILE * feed){
  //se  procesa un posteo, un usuario, se miden los tiempos y despues el total.

} 


int buscar_tweet(tTweet * tweet, t_lru_cache* cache, FILE * posteos){
  //se busca el tweet en la cache
  //Sino se busca en el file y se carga en la cache
  
  fseek(posteos,tweet->id-1*sizeof(tTweet),SEEK_SET);
  fread(tweet,sizeof(tTweet),1,posteos);
}

int cmpTweet(const void * elem1, const void * elem2){
  return ((tTweet *)elem1)->id - ((tTweet *)elem2)->id;
}