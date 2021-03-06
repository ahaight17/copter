#include <global.h>
#include <environment.h>
#include <copter.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void checkCopterCollision(struct EnvPillar **environment, struct Copter *copter);
void updateCopter(struct Copter *copter);

void drawEnv(SDL_Renderer *renderer, struct EnvPillar **environment){
  struct EnvPillar *ptr = *environment;

  for(int i = 0; i < WIDTH; i++){
    if(!ptr){
      return;
    }
    // draw the top env lines
    SDL_Rect top = { 0 };
    top.x = i;
    top.y = 0;
    top.w = PILLARSIZE;
    top.h = ptr->h;

    // draw the bottom env lines
    double h = (double)(STARTH*2)-ptr->h;
    SDL_Rect bottom = { 0 };
    bottom.x = i;
    bottom.y = HEIGHT-h+1;
    bottom.w = PILLARSIZE;
    bottom.h = h;

    // draw barriers
    if(ptr->gap > 0){
      SDL_Rect barrier = { 0 };
      barrier.x = i;
      barrier.y = ptr->h+ptr->gap;
      barrier.w = PILLARSIZE;
      barrier.h = HEIGHT-(2*ptr->gap)-ptr->h-h;

      SDL_RenderFillRect(renderer, &barrier);
      SDL_RenderDrawRect(renderer, &barrier);
    }

    SDL_SetRenderDrawColor(renderer, R, G, B, 1);
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

void printSDLText(SDL_Renderer *renderer, TTF_Font *gameFont, char *text,
                  int r, int g, int b, int y, int align){
  int padding = 25;
  int w, h;
  SDL_Color messageColor = {r, g, b, 0};

  SDL_Surface *messageSurf = TTF_RenderText_Solid(gameFont, text, messageColor);
  TTF_SizeText(gameFont, text, &w, &h);
  SDL_Texture *messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurf);
  int x = padding;
  if(align == 1){
    x = WIDTH-w-padding;
  } else if(align == 2){
    x = (WIDTH/2)-(w/2);
  }
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderCopy(renderer, messageTexture, NULL, &rect);

  SDL_FreeSurface(messageSurf);
  SDL_DestroyTexture(messageTexture);
  return;
}

void startMenuText(SDL_Renderer *renderer, TTF_Font *gameFontLarge, TTF_Font *gameFontSmall){
  int fhl = TTF_FontHeight(gameFontLarge);
  int fhs = TTF_FontHeight(gameFontSmall);

  printSDLText(renderer, gameFontLarge, "CLICK TO START", R, G, B, (HEIGHT/2)-(fhl/2), 1);
  printSDLText(renderer, gameFontSmall, "CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP", R, G, B, (HEIGHT/3)*2, 1);
  printSDLText(renderer, gameFontSmall, "RELEASE TO GO DOWN", R, G, B, (HEIGHT/3)*2+(fhs), 1);
  return;
}

void gameOverText(SDL_Renderer *renderer, TTF_Font *gameFontLarge, TTF_Font *gameFontSmall, int32_t frames){
  int fhl = TTF_FontHeight(gameFontLarge);

  printSDLText(renderer, gameFontLarge, "GAME OVER!", R, G, B, (HEIGHT/2)-(fhl/2), 2);
  char bestScore[100];
  sprintf(bestScore, "YOUR SCORE: %d", frames/10);
  printSDLText(renderer, gameFontSmall, bestScore, R, G, B, (HEIGHT/2)+(fhl), 2);
  printSDLText(renderer, gameFontSmall, "CLICK TO RESTART", R, G, B, (HEIGHT/2)+(fhl*2), 2);
}

void printScore(SDL_Renderer *renderer, TTF_Font *gameFontSmall, int32_t frames){
  char score[100];
  sprintf(score, "SCORE: %d", frames/10);
  printSDLText(renderer, gameFontSmall, score, 255, 255, 255, HEIGHT-(int)TTF_FontHeight(gameFontSmall), 0);
  return;
}

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct Copter *copter,
                int32_t *envListLength, int32_t FRAMES){
  if(game->phase == GAME_PLAY){
    updateEnvironment(environment, envListLength);
    updateCopter(copter);
    checkCopterCollision(environment, copter);
  }

  return;
}

void renderGame(SDL_Renderer *renderer, TTF_Font *gameFontLarge, TTF_Font *gameFontSmall,
                struct GameState *game, struct EnvPillar **environment,
                struct Copter *copter, int32_t FRAMES){
  drawEnv(renderer, environment);
  drawCopter(renderer, copter);
  if(game->phase == GAME_START){
    startMenuText(renderer, gameFontLarge, gameFontSmall);
  }
  if(game->phase == GAME_OVER){
    gameOverText(renderer, gameFontLarge, gameFontSmall, FRAMES);
  }
  printScore(renderer, gameFontSmall, FRAMES);
  return;
}