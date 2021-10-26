#include <global.h>
#include <copter.h>
#include <stdio.h>
#include <SDL2/SDL.h>

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
    top.w = PILLARSIZE;
    top.h = ptr->h;

    // draw the bottom env lines
    int h = STARTH + (STARTH-ptr->h);
    SDL_Rect bottom = {0};
    bottom.x = i;
    bottom.y = HEIGHT-h+1;
    bottom.w = PILLARSIZE;
    bottom.h = h;

    SDL_SetRenderDrawColor(
      renderer, R, G, B, 1
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
  SDL_RenderCopyEx(renderer, copter->texture, NULL, &(copter->rect), copter->tilt, NULL, SDL_FLIP_NONE);

  return;
}

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct Copter *copter,
                int32_t *envListLength, int32_t FRAMES){
  if(game->phase == GAME_PLAY){
    updateEnvironment(environment, envListLength);
    updateCopter(copter);
  }

  return;
}

void renderGame(SDL_Renderer *renderer, struct GameState *game, 
                struct EnvPillar **environment, struct Copter *copter){
  drawEnv(renderer, environment);
  drawCopter(renderer, copter);

  return;
}