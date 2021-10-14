#ifndef RENDER_DOT_H
#define RENDER_DOT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <copter.h>
#include <environment.h>
#include <SDL2/SDL.h>

#define WIDTH 1080
#define HEIGHT 720
#define SCROLLSPEED 2
#define PILLARSIZE 1
#define STARTH HEIGHT*0.15
#define MINL WIDTH*0.33
#define MINH 25
#define MAXSLOPE 0.33
#define MINSLOPE 0.1
#define CHEIGHT 45
#define CWIDTH 100
#define TILT 10
#define ACCELERATION 0.01
#define TIME 0.1
#define GRAVITY 0.009

enum GamePhase{
  GAME_START,
  GAME_PLAY,
  GAME_PAUSE,
  GAME_OVER
};

struct GameState{
  enum GamePhase phase;

  struct Copter copter;
};

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct Copter *copter,
                struct EnvListLength *list, int32_t FRAMES);
void renderGame(SDL_Renderer *renderer, struct GameState *game, 
                struct EnvPillar **environment, struct Copter *copter);
#endif