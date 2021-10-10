#include <global.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <SDL2/SDL.h>

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

void addNewEnv(struct EnvPillar **environment, bool directionUp){
  struct EnvPillar *ptr = *environment;
  struct EnvPillar *lastPtr = NULL;
  // get the last env pointer
  while(ptr != NULL){
    lastPtr = ptr;
    ptr = ptr->next;
  }
  int len = (rand() % (uint32_t)(MAXL-MINL)) + MINL;
  int height = (rand() % (uint32_t)(MAXH-MINH)) + MINH;
  height = abs(height - lastPtr->h);
  float ratio = height/len;

  while(lastPtr->h <= height){
    struct EnvPillar *newSeg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    newSeg->next = NULL;

    if(directionUp){
      newSeg->h = lastPtr->h - ratio;
    } else {
      newSeg->h = lastPtr->h + ratio;
    }

    lastPtr->next = newSeg;
  }
}

void removeOldestEnv(struct EnvPillar **environment){

  struct EnvPillar *first = *environment;

  if((*environment) == NULL){
    printf("we're null");
    return;
  } else {
    printf("%f", (*environment)->h);
    struct EnvPillar *first = *environment;
    *environment = (*environment)->next;
  }

  // free(first);
  return;
}

void printPillars(struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  while(ptr != NULL){
    printf("%f\n", ptr->h);

    ptr = ptr->next;
  }
  return;
}