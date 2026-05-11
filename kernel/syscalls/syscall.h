#ifndef __SYSCALL_H
#define __SYSCALL_H

#include <stdint.h>
#include <stdbool.h>

#include "../kernel_library/display/display.h"
#include "../kernel_library/drives/drives.h"

#define COMMAND_READ    0b00000000 << 24
#define COMMAND_WRITE   0b00000001 << 24
#define COMMAND_SET     0b00000010 << 24
#define COMMAND_GET     0b00000011 << 24
#define COMMAND_MEMORY  0b00000100 << 24
#define COMMAND_EVENT   0b00000101 << 24

#define PARAM_FILE_READ 0b00000000 << 16
#define PARAM_FILE_OPEN 0b00000001 << 16
#define PARAM_FILE_ALL  0b00000010 << 16

#define PARAM_FILE_WRITE 0b00000000 << 16
#define PARAM_FIGURE     0b00000001 << 16

#define PARAM_MEM_ALLOC   0b00000000 << 16
#define PARAM_MEM_FREE    0b00000001 << 16


typedef void (*_call)(uint32_t, uint32_t, uint32_t);

extern uint32_t return_value;
extern bool has_return;
extern uint32_t *variables[];
extern _call read_calls[];
extern _call write_calls[];

#endif
