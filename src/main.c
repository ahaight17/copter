#include <global.h>
#include <copter.h>
#include <environment.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef float f32;
typedef double f64;
struct GameState game;

int main(int argv, char** args) {
  // init for random 
  srand(time(NULL));
  // frame counter
  s32 FRAMES = 0;

  // init SDL libs
  if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0){
    return 1;
  }

  // create global game window
  SDL_Window *window = SDL_CreateWindow(
    "Copter",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  // create global game renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  TTF_Font *gameFontLarge = TTF_OpenFont("../assets/font.ttf", 50);
  TTF_Font *gameFontSmall = TTF_OpenFont("../assets/font.ttf", 30);

  // global to keep track of linked list length
  s32 envListLength = 0;
  struct Copter copter = {};
  struct EnvPillar *environment = NULL;

  // we're doing a push operation here and adding to the front
  initEnvPillars(renderer, &environment, &envListLength);
  // set up initial copter position, speed, and visual asset
  initCopter(renderer, &copter);

  SDL_SetWindowIcon(window, (&copter)->surface);

  bool quit = false;
  // gameplay loop
  while(!quit){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
      switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
          copterMouseDown(&copter);
          break;
        case SDL_MOUSEBUTTONUP:
          copterMouseUp(&copter);
          break;
        case SDL_QUIT:
          quit = true;
          break;
        default:
          break;
      }
    }

    // black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    // run update function
    updateGame(renderer, &game, &environment, &copter, &envListLength, FRAMES);
    // run render function
    renderGame(renderer, gameFontLarge, gameFontSmall, &game, &environment, &copter, FRAMES);

    SDL_RenderPresent(renderer);
    // increment frame counter
    if(game.phase == GAME_PLAY){
      FRAMES++;
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();

	return 0;
}