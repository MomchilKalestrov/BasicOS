#ifndef _KEYBOARD_
    #define _KEYBOARD_
	
	#define KB_RING_SIZE 4

	typedef void(*kb_callback_t)(uint8_t, char);

														/*    0     1    2    3    4    5    6    7    8     9    10    11    12    13   14    15 */
	const unsigned char keyboard_layout[128] =		{	'\0', '\0', '1', '2', '3', '4', '5', '6', '7',  '8', '9',  '0',  '-',  '=', '\b', '\t',
													/*   16    17    18   19   20   21   22   23   24    25   26    27    28    29   30    31 */
														'q',  'w',  'e', 'r', 't', 'y', 'u', 'i', 'o',  'p', '[',  ']',  '\n', ' ', 'a',  's',
													/*   32    33    34   35   36   37   38   39   40    41   42    43    44    45   46    47 */
														'd',  'f',  'g', 'h', 'j', 'k', 'l', ';', '\'', '`', ' ',  '\\', 'z',  'x', 'c',  'v',
													/*   48    49    50   51   52   53   54   55   56    57   58 */
														'b',  'n',  'm', ',', '.', '/', ' ', ' ', ' ',  ' ', ' ' };

														/*    0     1    2    3    4    5    6    7    8     9    10   11   12    13   14    15 */
	const unsigned char keyboard_layout_shift[128] =	{	'\0', '\0', '!', '@', '#', '$', '%', '^', '&',  '*', '(', ')', '_',  '+', '\b', '\t',
														/*   16    17    18   19   20   21   22   23   24    25   26   27   28    29   30    31 */
															'Q',  'W',  'E', 'R', 'T', 'Y', 'U', 'I', 'O',  'P', '[', ']', '\n', 254, 'A',  'S',
														/*   32    33    34   35   36   37   38   39   40    41   42   43   44    45   46    47 */
															'D',  'F',  'G', 'H', 'J', 'K', 'L', ':', '\"', '~', ' ', '|', 'Z',  'X', 'C',  'V',
														/*   48    49    50   51   52   53   54   55   56    57   58 */
															'B',  'N',  'M', '<', '>', '?', ' ', ' ', ' ',  ' ', ' ' };

	kb_callback_t kb_event;

	char kb_queue[KB_RING_SIZE];

	uint8_t _kb_internal_ptr;
	uint8_t kb_index;

	#define MOD_NONE  0
	#define MOD_CTRL  (1 << 0)
	#define MOD_SHIFT (1 << 1)
	#define MOD_ALT   (1 << 2)

	uint8_t mod_keys = 0;

	#include "./keyboard.c"
#endif