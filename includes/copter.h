#ifndef COPTER_DOT_H
#define COPTER_DOT_H

#include <global.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct Copter{
  int xPos;
  int yPos;
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect rect;
};

void initCopter(SDL_Renderer *renderer, struct Copter *copter);

#endif