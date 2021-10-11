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
#include <SDL2/SDL.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef float f32;
typedef double f64;

int main(int argv, char** args) {
  // init for random 
  srand(time(NULL));
  // frame counter
  s32 FRAMES = 0;

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
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

  struct EnvListLength list = {
    .length = 0
  };
  struct GameState game = { 
    .phase = GAME_START
  };
  struct Copter copter = {};
  struct EnvPillar *environment = NULL;

  // we're doing a push operation here and adding to the front
  initEnvPillars(renderer, &environment, &list);
  initCopter(renderer, &copter);
  
  struct InputState input = {};

  bool quit = false;
  // gameplay loop
  while(!quit){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
      switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
          printf("Mouse down");
          break;
        case SDL_MOUSEBUTTONUP:
          printf("Mouse up");
          break;
        case SDL_QUIT:
          printf("Quitting");
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
    updateGame(renderer, &game, &environment, &list, &input, FRAMES);
    // run render function
    renderGame(renderer, &game, &environment, &copter);

    SDL_RenderPresent(renderer);
    // increment frame counter
    FRAMES++;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

	return 0;
}