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

void updateEnvironment(struct EnvPillar **environment, int32_t *envListLength);

#endif
