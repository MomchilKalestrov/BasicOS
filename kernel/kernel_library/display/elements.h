#ifndef _ELEMENTS_
    #define _ELEMENTS_

    #define MAX_ELEMENTS 64

    #define BUTTON  0
    #define FIELD   1
    #define LABEL   2
    #define IMAGE   3

    typedef struct {
        uint16_t x;
        uint16_t y;

        uint16_t width;
        uint16_t height;

        uint32_t foreground;
        uint32_t background;

        bool visible;

        char *text;

        uint8_t type;
        uint8_t extras[8];
    } element_t;
    
    typedef void (*callback_t)(element_t *);

    typedef struct {
        callback_t on_click;
    } button_t;

    typedef struct {
        uint8_t selected_index;
        uint8_t max_length;
    } field_t;

    typedef struct {
        file_t *image_location;
    } image_t;

    element_t _elements_arr[MAX_ELEMENTS];
    element_t *elements = _elements_arr;
    uint8_t element_counter = 0;
    int8_t element_selected = -1;

    void element_render(void);

    #include "./elements.c"
#endif