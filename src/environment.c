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
void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment){
  for(int i = 0; i < WIDTH*2; i++){
    struct EnvPillar *startSeg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    startSeg->h = STARTH;

    startSeg->next = *environment;

    *environment = startSeg;
  }
  return;
}

/**
 * Render the first flat section of environment 
**/
void addNewEnv(struct EnvPillar **environment, bool directionUp){
  struct EnvPillar *ptr = *environment;
  struct EnvPillar *lastPtr = NULL;
  // get the last env pointer
  while(ptr != NULL){
    lastPtr = ptr;
    ptr = ptr->next;
  }
  // generate a random length between min and max 
  int len = (rand() % (uint32_t)(MAXL-MINL)) + MINL;
  // generate a random height change
  int height = (rand() % (uint32_t)(MAXH-MINH)) + MINH;
  height = abs(height - lastPtr->h);
  float slope = height/len;

  while(lastPtr->h <= height){
    struct EnvPillar *newSeg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    newSeg->next = NULL;

    if(directionUp){
      newSeg->h = lastPtr->h - slope;
    } else {
      newSeg->h = lastPtr->h + slope;
    }

    lastPtr->next = newSeg;
  }
}

// remove environment that has exited screen on left side
void removeOldestEnv(struct EnvPillar **environment){

  if((*environment) == NULL){
    return;
  } else {
    // used to free memory
    struct EnvPillar *first = *environment;
    *environment = (*environment)->next;
  }

  free(first);
  return;
}

// util function for iterating linked list
void printPillars(struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  while(ptr != NULL){
    printf("%f\n", ptr->h);

    ptr = ptr->next;
  }
  return;
}