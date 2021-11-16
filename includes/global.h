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
#define MINH 30
#define MAXSLOPE 0.33
#define MINSLOPE 0.1
#define CHEIGHT 45
#define CWIDTH 100
#define TILT 10
#define ACCELERATION 0.01
#define TIME 0.25
#define GRAVITY 0.009
#define R 101
#define G 255
#define B 101

enum GamePhase{
  GAME_START,
  GAME_PLAY,
  GAME_PAUSE,
  GAME_OVER
};

struct GameState{
  enum GamePhase phase;
};

extern struct GameState game;

void updateGame(SDL_Renderer *renderer, struct GameState *game,
                struct EnvPillar **environment, struct Copter *copter,
                int32_t *envListLength, int32_t FRAMES);

void renderGame(SDL_Renderer *renderer, TTF_Font *gameFontLarge, TTF_Font *gameFontSmall,
                struct GameState *game, struct EnvPillar **environment,
                struct Copter *copter, int32_t FRAMES);
#endif