#include <global.h>
#include <copter.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>

void initCopter(SDL_Renderer *renderer, struct Copter *copter){
  copter->down = true;
  copter->tilt = 0;
  copter->v = 0;
  copter->t = TIME;
  copter->yPos = (HEIGHT/2)-(CHEIGHT/2);
  copter->surface = SDL_LoadBMP("../assets/copter.bmp");
  copter->texture = SDL_CreateTextureFromSurface(renderer, copter->surface);
  SDL_Rect rect = { WIDTH*0.15, copter->yPos, CWIDTH, CHEIGHT };
  copter->rect = rect;

  return;
}

void updateCopter(struct Copter *copter){
  // decide if acceleration is positive or negative
  double a = copter->down ? ACCELERATION : -ACCELERATION;
  // decide if copter is tilting downward or not
  double tilt = copter->down ? TILT : 0;
  
  // update copter velocity from time, acceleration, and gravity
  copter->v += (copter->t * a) + GRAVITY;
  // update copter position on Y axis
  copter->yPos += ((0.5*a)*pow(copter->t, 2.0)) + (copter->v);
  // increment time
  copter->t += TIME;
  // update copter tilt
  copter->tilt = tilt;
  
  // update rect used to draw copter on screen with new values
  SDL_Rect rect = { WIDTH*0.15, copter->yPos, CWIDTH, CHEIGHT };
  copter->rect = rect;

  return;
}

void checkCopterCollision(struct EnvPillar **environment, struct Copter *copter){
  // printf("%lf\n", copter->yPos);
  if(copter->yPos >= HEIGHT - CHEIGHT || copter->yPos <= 0){
    game.phase = GAME_OVER;
  }
  return;
}

// when the mouse is pressed
void copterMouseDown(struct Copter *copter){
  if(game.phase == GAME_START){
    game.phase = GAME_PLAY;
  }
  copter->t = 0;
  copter->down = false;

  return;
}

// when the mouse is released
void copterMouseUp(struct Copter *copter){
  copter->t = 0;
  copter->down = true;

  return;
}