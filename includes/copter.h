#ifndef COPTER_DOT_H
#define COPTER_DOT_H

#include <global.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Copter{
  double yPos;
  double angle;
  double t;
  double v;
  bool down;
  double tilt;
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect rect;
};

void initCopter(SDL_Renderer *renderer, struct Copter *copter);
void copterMouseDown(struct Copter *copter);
void copterMouseUp(struct Copter *copter);
void checkCopterCollision(struct EnvPillar **environment, struct Copter *copter);
void updateCopter(struct Copter *copter);

#endif