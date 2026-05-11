#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdint.h>

#include "../display/display.h"
#include "../instructions/instructions.h"

#define CURSOR_SIZE 12

extern uint16_t mouse_x;
extern uint16_t mouse_y;

extern uint8_t mouse_left;
extern uint8_t mouse_center;
extern uint8_t mouse_right;

extern uint32_t cursor_back[CURSOR_SIZE][CURSOR_SIZE];
extern const uint8_t cursor[CURSOR_SIZE][CURSOR_SIZE];

void mouse_update(int32_t, int32_t);
void mouse_init(void);

#endif