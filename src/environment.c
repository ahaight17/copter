#include <global.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>

void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment, 
                    struct EnvListLength *list){
  for(int i = 0; i < WIDTH*1.5; i++){

    // create new env segment
    struct EnvPillar *startSeg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    // push it to the front
    startSeg->h = STARTH;
    startSeg->next = *environment;

    *environment = startSeg;
  }
  // make sure to update list length
  incrementListLength(list, WIDTH*2);
  return;
}

void updateEnvironment(struct EnvPillar **environment, struct EnvListLength *list){
  
  // remove env if we have enough
  if(list->length > WIDTH+SCROLLSPEED){
    removeFromFront(environment, list, SCROLLSPEED);
  }

  // add more env and be ahead of the curve
  if(list->length < WIDTH * 2){
    addToBack(environment, list);
  }
}

void removeFromFront(struct EnvPillar **environment, struct EnvListLength *list,
                      int amount){
  
  // if env is null
  if(!(*environment)->next || list->length <= 0)
    return;
  else {
    // if we try to remove more than width of screen
    if(amount > WIDTH) return;
    for(int i = 0; i < amount; i++){
      struct EnvPillar *first = *environment;
      *environment = (*environment)->next;
      // free(first);
      decrementListLength(list, 1);
    }
  }

  return;
}

void addToBack(struct EnvPillar **environment, struct EnvListLength *list){
  struct EnvPillar *ptr = *environment;
  struct EnvPillar *lastPtr = (struct EnvPillar*) malloc(
    sizeof(struct EnvPillar)
  );
  int maxH = (STARTH*2)-MINH;
  bool directionUp = rand()>(RAND_MAX/2);

  // immediately get last pointer
  while(ptr->next != NULL){
    ptr = ptr->next;
    lastPtr = ptr;
  }

  if(lastPtr->h <= MINH)
    directionUp = false;

  if(lastPtr->h >= maxH)
    directionUp = true;
  
  // get int length between max and min
  int len = MINL + (rand() / ((RAND_MAX)/(WIDTH-MINL)));
  // get int slope between max and min
  double slope = MINSLOPE + (rand() / ((RAND_MAX)/(MAXSLOPE-MINSLOPE)));
  // amount of room between current height and the max or min
  double diff = directionUp ? fabs(lastPtr->h - MINH) : fabs(lastPtr->h - maxH);

  double lh = lastPtr->h;
  for(int i = 0; i < len; i++){
    if(diff <= 0)
      return;
    diff -= slope;
    // create new env segment
    struct EnvPillar *seg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    seg->h = directionUp ? lh-slope : lh+slope;
    seg->next = NULL;

    lastPtr->next = seg;

    lastPtr = seg;

    if(directionUp)
      lh -= slope;
    else 
      lh += slope;

    incrementListLength(list, 1);
  }

  return;
}

/*****************
  UTIL FUNCTIONS
 *****************/
void loopPillars(struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  int count = 0;
  while(ptr != NULL){
    count ++;
  }
  printf("%d\n", count);
  return;
}

void incrementListLength(struct EnvListLength *list, int amount){
  list->length += amount;
}

void decrementListLength(struct EnvListLength *list, int amount){
  list->length -= amount;
}