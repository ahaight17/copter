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
  for(int i = 0; i < WIDTH*2; i++){

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
  
  // int height = (rand() % (uint32_t)(MAXH-MINH)) + MINH;
  // height = abs(height - lastPtr->h);
  // float ratio = height/len;

  // while(lastPtr->h <= height){
  //   struct EnvPillar *newSeg = (struct EnvPillar*) malloc(
  //     sizeof(struct EnvPillar)
  //   );

  //   newSeg->next = NULL;

  //   if(directionUp){
  //     newSeg->h = lastPtr->h - ratio;
  //   } else {
  //     newSeg->h = lastPtr->h + ratio;
  //   }

  //   lastPtr->next = newSeg;
  // }
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

  bool directionUp = rand()>(RAND_MAX/2);

  // immediately get last pointer
  while(ptr->next != NULL){
    ptr = ptr->next;
    lastPtr = ptr;
  }

  if(lastPtr->h < MINH)
    directionUp = false;

  if(lastPtr->h > MAXH)
    directionUp = true;
  
  // get int length between max and min
  int len = (rand() % (uint32_t)(MAXL-MINL)) + MINL;
  // get int slope between max and min
  double slope = MINSLOPE + (rand() / ((RAND_MAX)/(MAXSLOPE-MINSLOPE)));
  // amount of room between current height and the max or min
  int diff = directionUp ? abs(lastPtr->h - MINH) : abs(lastPtr->h - MAXH);

  int lastHeight = lastPtr->h;
  for(int i = 0; i < len; i++){
    if(diff <= 0) return;
    diff -= slope;
    // create new env segment
    struct EnvPillar *seg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    seg->h = directionUp ? lastHeight-slope : lastHeight+slope;
    seg->next = NULL;

    lastPtr->next = seg;

    lastPtr = seg;

    if(directionUp)
      lastHeight -= slope;
    else
      lastHeight += slope;

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