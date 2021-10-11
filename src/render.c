#include <global.h>
#include <copter.h>
#include <stdio.h>
#include <SDL2/SDL.h>

const int32_t ENVCOLOR[] = { 101, 255, 101, 1 };

void drawEnv(SDL_Renderer *renderer, struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  for(int i = 0; i < WIDTH; i++){
    if(!ptr){
      return;
    }
    // draw the top env lines
    SDL_Rect top = {0};
    top.x = i;
    top.y = 0;
    top.w = GRIDSIZE;
    top.h = ptr->h;

    // draw the bottom env lines
    int h = STARTH + (STARTH-ptr->h);
    SDL_Rect bottom = {0};
    bottom.x = i;
    bottom.y = HEIGHT-h+1;
    bottom.w = GRIDSIZE;
    bottom.h = h;

    SDL_SetRenderDrawColor(
      renderer, ENVCOLOR[0], ENVCOLOR[1], ENVCOLOR[2], ENVCOLOR[3]
    );
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderDrawRect(renderer, &top);
    SDL_RenderDrawRect(renderer, &bottom);

    // next pointer please
    ptr = ptr->next;
  }
  return;
}

void drawCopter(SDL_Renderer *renderer, struct Copter *copter){
  SDL_RenderCopyEx(renderer, copter->texture, NULL, &(copter->rect), 10, NULL, SDL_FLIP_NONE);
}

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct EnvListLength *list, 
                struct InputState *input,
                int32_t FRAMES){
  updateEnvironment(environment, list);
}

void renderGame(SDL_Renderer *renderer, struct GameState *game, 
                struct EnvPillar **environment, struct Copter *copter){
  drawEnv(renderer, environment);
  drawCopter(renderer, copter);
}