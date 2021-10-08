#include <global.h>
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
  srand(time(NULL));
  s32 FRAMES = 0;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
    "Copter",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  SDL_Renderer *renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  struct EnvPillar *environment = NULL;
  enum GamePhase phase = GAME_START;

  initEnvPillars(renderer, &environment);

  struct GameState game = { 
    .phase = phase,
    .envDirUp = false
  };
  
  struct InputState input = {};

  bool quit = false;
  while(!quit){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
      if(e.type == SDL_QUIT){
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    updateGame(renderer, &game, &environment, &input, FRAMES);
    renderGame(renderer, &game, &environment);

    SDL_RenderPresent(renderer);
    FRAMES++;
  }

  SDL_DestroyRenderer(renderer);
  SDL_Quit();

	return 0;
}