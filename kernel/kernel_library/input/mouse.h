#ifndef _MOUSE_
    #define _MOUSE_

    #define CURSOR_SIZE 12
    
	typedef void(*ms_callback_t)(uint16_t, uint16_t);

    ms_callback_t ms_event;

    uint16_t mouse_x = 64;
    uint16_t mouse_y = 64;
    
    uint8_t mouse_left   = 0;
    uint8_t mouse_center = 0;
    uint8_t mouse_right  = 0;
    
    uint32_t cursor_back[CURSOR_SIZE][CURSOR_SIZE];
    uint8_t cursor[CURSOR_SIZE][CURSOR_SIZE] = {
        { 1,1,0,0,0,0,0,0,0,0,0,0 },
        { 1,4,1,1,0,0,0,0,0,0,0,0 },
        { 0,1,4,2,1,1,0,0,0,0,0,0 },
        { 0,1,3,4,2,2,1,1,0,0,0,0 },
        { 0,0,1,3,4,2,2,2,1,1,0,0 },
        { 0,0,1,3,3,4,2,2,2,2,1,1 },
        { 0,0,0,1,3,3,4,2,2,2,2,1 },
        { 0,0,0,1,3,3,3,4,2,2,1,0 },
        { 0,0,0,0,1,3,3,3,4,2,1,0 },
        { 0,0,0,0,1,3,3,3,3,1,0,0 },
        { 0,0,0,0,0,1,3,1,1,0,0,0 },
        { 0,0,0,0,0,1,1,0,0,0,0,0 }
    };

    uint32_t mouse_colors[5] = {
        0x000000,
        0x000000,
        0xffffff,
        0xaaaaaa,
        0xdddddd
    };

    #include "./mouse.c"
#endif