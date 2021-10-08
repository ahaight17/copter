#include <global.h>
#include <stdio.h>

#include <SDL2/SDL.h>

const int32_t ENVCOLOR[] = { 101, 255, 101, 1 };

void drawEnv(SDL_Renderer *renderer, struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  // draw the top env lines
  for(int i = 0; i < WIDTH; i++){
    SDL_Rect rect = {0};
    rect.x = i;
    rect.y = 0;
    rect.w = GRIDSIZE;
    rect.h = ptr->h;

    ptr = ptr->next;

    SDL_SetRenderDrawColor(
      renderer, ENVCOLOR[0], ENVCOLOR[1], ENVCOLOR[2], ENVCOLOR[3]
    );
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
  }

  // draw the bottom env lines
  for(int i = 0; i < WIDTH; i++){
    SDL_Rect rect = {0};
    rect.x = i;
    rect.y = HEIGHT-ptr->h-1;
    rect.w = GRIDSIZE;
    rect.h = ptr->h;

    ptr = ptr->next;

    SDL_SetRenderDrawColor(
      renderer, ENVCOLOR[0], ENVCOLOR[1], ENVCOLOR[2], ENVCOLOR[3]
    );
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct InputState *input, 
                int32_t FRAMES){
  if(FRAMES%WIDTH){
    addNewEnv(environment, game->envDirUp);
  }
  removeOldestEnv(environment);
}

void renderGame(SDL_Renderer *renderer, struct GameState *game, 
                struct EnvPillar **environment){
  drawEnv(renderer, environment);
}