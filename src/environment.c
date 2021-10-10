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
    struct EnvPillar *startSeg = (struct EnvPillar*) malloc(
      sizeof(struct EnvPillar)
    );

    startSeg->h = STARTH;
    startSeg->next = *environment;

    *environment = startSeg;
  }
  incrementListLength(list, WIDTH*2);
  return;
}

void updateEnvironment(struct EnvPillar **environment, bool directionUp, 
                        struct EnvListLength *list){
  
  // remove env if we have enough
  if(list->length > WIDTH){
    removeFromFront(environment, list, SCROLLSPEED);
  }

  // add more env and be ahead of the curve
  if(list->length < WIDTH * 2){
    addToBack(environment, directionUp, list);
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
  if(!environment) return;
  else {
    // if we try to remove more than width of screen
    if(amount > WIDTH) return;
    for(int i = 0; i < amount; i++){
      struct EnvPillar *first = *environment;
      *environment = (*environment)->next;
      free(first);
      decrementListLength(list, 1);
    }
  }

  return;
}

void addToBack(struct EnvPillar **environment, bool directionUp, 
                struct EnvListLength *list){
  struct EnvPillar *ptr = *environment;
  struct EnvPillar *lastPtr = NULL;
  // get the last env pointer
  while(ptr != NULL){
    lastPtr = ptr;
    ptr = ptr->next;
  }

  // get int length between max and min
  int len = (rand() % (uint32_t)(MAXL-MINL)) + MINL;
  // get int slope between max and min
  int slope = (rand() % (uint32_t)(MAXSLOPE-MINSLOPE)) + MINSLOPE;
  
  int diff = directionUp ? abs(ptr->h - MINH) : abs(ptr->h - MAXH);


  return;
}

/*****************
  UTIL FUNCTIONS
 *****************/
void printPillars(struct EnvPillar **environment){
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