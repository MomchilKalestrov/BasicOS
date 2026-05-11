#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define KB_RING_SIZE 4

#include <stdint.h>

#include "../display/display.h"

#define MOD_NONE  0
#define MOD_CTRL  (1 << 0)
#define MOD_SHIFT (1 << 1)
#define MOD_ALT   (1 << 2)

extern const unsigned char keyboard_layout[128];
extern const unsigned char keyboard_layout_shift[128];

extern char kb_queue[KB_RING_SIZE];

extern uint8_t _kb_internal_ptr;
extern uint8_t kb_index;

extern uint8_t mod_keys;

void keyboard_read(char *, uint16_t);

#endif