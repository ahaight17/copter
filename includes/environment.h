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

struct EnvPillarMeta{
  struct EnvPillar *last;
};

struct EnvListLength{
  int length;
};

void initEnvPillars(SDL_Renderer *renderer, struct EnvPillar **environment,
                    struct EnvListLength *list);
void updateEnvironment(struct EnvPillar **environment, bool directionUp,
                        struct EnvListLength *list);
void removeFromFront(struct EnvPillar **environment, struct EnvListLength *list,
                      int amount);
void addToBack(struct EnvPillar **environment, bool directionUp,
                struct EnvListLength *list);
void printPillars(struct EnvPillar **environment);

void incrementListLength(struct EnvListLength *list, int amount);
void decrementListLength(struct EnvListLength *list, int amount);

#endif
