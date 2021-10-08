#ifndef ENVIRONMENT_DOT_H
#define ENVIRONMENT_DOT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct EnvPillar{
  float h;

  struct EnvPillar *next;
};

void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment);
void addNewEnv(struct EnvPillar **environment, bool directionUp);
void removeOldestEnv(struct EnvPillar **environment);
void printPillars(struct EnvPillar **environment);

#endif
