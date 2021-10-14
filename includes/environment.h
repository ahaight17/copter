#ifndef ENVIRONMENT_DOT_H
#define ENVIRONMENT_DOT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct EnvPillar{
  double h;
  struct EnvPillar *next;
};

struct EnvPillarMeta{
  struct EnvPillar *last;
};

void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment,
                    int32_t *envListLength);
void updateEnvironment(struct EnvPillar **environment, int32_t *envListLength);
void removeFromFront(struct EnvPillar **environment, int32_t *envListLength,
                      int amount);
void addToBack(struct EnvPillar **environment, int32_t *envListLength);
void loopPillars(struct EnvPillar **environment);

void incrementListLength(int32_t *envListLength, int amount);
void decrementListLength(int32_t *envListLength, int amount);

#endif
