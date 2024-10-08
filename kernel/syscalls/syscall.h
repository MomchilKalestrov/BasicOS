#define COMMAND_READ    0b00000000 << 24
#define COMMAND_WRITE   0b00000001 << 24
#define COMMAND_SET     0b00000010 << 24
#define COMMAND_GET     0b00000011 << 24
#define COMMAND_MEMORY  0b00000100 << 24

#define PARAM_FILE_READ 0b00000000 << 16
#define PARAM_FILE_OPEN 0b00000001 << 16
#define PARAM_FILE_ALL  0b00000010 << 16

#define PARAM_FILE_WRITE 0b0000000 << 16
#define PARAM_FIGURE     0b00000001 << 16
#define PARAM_ELEMENT    0b00000010 << 16

#define PARAM_MEM_ALLOC 0b00000000 << 16
#define PARAM_MEM_FREE  0b00000001 << 16

#define FIG_TYPE_LINE      0b00000000 << 0
#define FIG_TYPE_RECTANGLE 0b00000001 << 0
#define FIG_TYPE_CIRCLE    0b00000010 << 0
#define FIG_TYPE_TEXT      0b00000011 << 0
#define FIG_TYPE_SYMBOL    0b00000100 << 0
#define FIG_TYPE_PIXEL     0b00000101 << 0

uint32_t return_value = 0;
bool has_return = false;

void *setters[] = {
    (void *)&foreground,
    (void *)&background,
    (void *)&kb_event,
    (void *)&ms_event
};

void *getters[] = {
    (void *)&foreground,
    (void *)&background,
    (void *)&kb_event,
    (void *)&ms_event,
    (void *)&framebuffer_width,
    (void *)&framebuffer_height
};

typedef void (*_calls)(uint32_t, uint32_t, uint32_t);

#include "./memory_calls.c"
#include "./read_calls.c"
#include "./write_calls.c"
#include "./syscall.c"