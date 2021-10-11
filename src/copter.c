#include <global.h>
#include <copter.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>

void initCopter(SDL_Renderer *renderer, struct Copter *copter){
  SDL_Rect crect= { WIDTH*0.15, (HEIGHT/2)-(CHEIGHT/2), CWIDTH, CHEIGHT };
  copter->surface = SDL_LoadBMP("../assets/copter.bmp");
  copter->rect = crect;
  copter->texture = SDL_CreateTextureFromSurface(renderer, copter->surface);
  return;
}