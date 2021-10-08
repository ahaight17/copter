#ifndef COPTER_DOT_H
#define COPTER_DOT_H

#include <global.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Copter{
  int32_t xPos;
  int32_t yPos;
  int32_t accel;
};

#endif