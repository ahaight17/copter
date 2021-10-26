#include <global.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>

/**
 * Render the first flat section of environment 
**/
void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment, 
                    int32_t *envListLength){
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
  incrementListLength(envListLength, WIDTH*1.5);
  return;
}

void updateEnvironment(struct EnvPillar **environment, int32_t *envListLength){
  // remove env if we have enough
  if(*envListLength > WIDTH+SCROLLSPEED){
    removeFromFront(environment, envListLength, SCROLLSPEED);
  }

  // add more env and be ahead of the curve
  if(*envListLength < WIDTH * 2){
    addToBack(environment, envListLength);
  }

  return;
}

// remove environment that has exited left side of screen
void removeFromFront(struct EnvPillar **environment, int32_t *envListLength,
                      int amount){
  // if env is null
  if(!(*environment)->next || *envListLength <= 0)
    return;
  else {
    // if we try to remove more than width of screen
    if(amount > WIDTH) return;
    for(int i = 0; i < amount; i++){
      *environment = (*environment)->next;
      decrementListLength(envListLength, 1);
    }
  }

  return;
}

// add new environment section
void addToBack(struct EnvPillar **environment, int32_t *envListLength){
  struct EnvPillar *ptr = *environment;
  struct EnvPillar *lastPtr = (struct EnvPillar*) malloc(
    sizeof(struct EnvPillar)
  );
  int maxH = (STARTH*2)-MINH;
  bool directionUp = rand()>(RAND_MAX/2);

  // immediately get last pointer in list
  while(ptr->next != NULL){
    ptr = ptr->next;
    lastPtr = ptr;
  }

  // don't go beyond specified max or min
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

    incrementListLength(envListLength, 1);
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

// keep track of linked list length
void incrementListLength(int32_t *envListLength, int amount){
  *envListLength += amount;

  return;
}

void decrementListLength(int32_t *envListLength, int amount){
  *envListLength -= amount;

  return;
}