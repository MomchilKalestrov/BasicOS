#ifndef _EVENTS_

    typedef enum {
        KEY_PRESS     = 1,
        KEY_RELEASE   = 2,
        MOUSE_MOVE    = 3,
        MOUSE_CLICK   = 4,
        MOUSE_DRAG    = 5,
        MOUSE_RELEASE = 6
    } event_type_t;

    typedef struct {
        event_type_t type;

        union {
            struct {
                uint8_t mods;
                uint8_t key;
            } key_event;

            struct {
                uint16_t x;
                uint16_t y;
            } mouse_event;
        };
    } event_t;

    typedef struct node {
        struct node *prev;
        event_t event;
        struct node *next;
    } node_t;

    node_t *event_head = NULL;
    node_t *event_tail = NULL;

    void event_push(event_t event);
    event_t event_pop(void);

    #include "./events.c"

    #define _EVENTS_
#endif