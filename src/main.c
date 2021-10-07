#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <copter.h>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef float f32;
typedef double f64;

#define WIDTH 400
#define HEIGHT 750

enum GamePhase{
  GAME_PLAY
};

struct Copter{
  s32 xPos;
  s32 yPos;
  s32 accel;
};

struct GameState{
  u8 gameBoard[WIDTH][HEIGHT];
  // Copter copter;

  // GamePhase phase;
};

int main() {
  printf("We are playing copter");
	return 0;
}