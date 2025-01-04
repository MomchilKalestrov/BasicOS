#ifndef _EVENTS_

    #define EVENT_KEY_PRESS     1
    #define EVENT_KEY_RELEASE   2
    #define EVENT_MOUSE_CLICK   3
    #define EVENT_MOUSE_DRAG    4
    #define EVENT_MOUSE_RELEASE 5

    typedef struct {
        uint8_t type;

        union {
            struct {
                uint8_t mods;
                uint8_t key;
            } key_event;

            struct {
                uint16_t x;
                uint16_t y;
            } mouse_event;

            uint8_t _union_size[7];
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