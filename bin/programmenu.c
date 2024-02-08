#include "textedit.c"
#include "game.c"
#include "clock.c"
#include "calculator.c"
#include "drivereader.c"

void programmenu_init(void) {
	terminal_setcolor(VGA_COLOR_DARK_GREY, VGA_COLOR_LIGHT_CYAN);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
	// Since VGA Text Mode uses CodePage 437/IBM BIOS characters, I have to change my encoding in VS Code every f****** time I open the file
	// That wouldn't be an issue if it actually saved the file in the proper encoding that is, but f*** me I guess :))))))).
	// Another thing that sucks is it for some reason shows me the string length as if it was opened in UTF-8 (basically longer and incorrect).
	terminal_writestring("Û²±° PROGRAM MENU °±²ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ²±° SHIFT CTRL ALT °±²Û");
	terminal_row = 7;
	terminal_writestring("                                   \n");
	terminal_writestring("                              ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ\n");
	terminal_writestring("                              Û                  Û°\n");
	terminal_writestring("                              Û                  Û°\n");
	terminal_writestring("      Basic OS  v1.0.0.0      Û   Text  Editor   Û°\n");
	terminal_writestring("                              Û   Drive Reader   Û°\n");
	terminal_writestring("        Copyright 2024        Û    Calculator    Û°\n");
	terminal_writestring("      Momchil  Kalestrov      Û       Game       Û°\n");
	terminal_writestring("                              Û                  Û°\n");
	terminal_writestring("                              Û                  Û°\n");
	terminal_writestring("                              ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ°\n");
	terminal_writestring("                               °°°°°°°°°°°°°°°°°°°°\n");
}

void programmenu_main(void) {
	reset: ;
	programmenu_init();
    char input;
    uint8_t option = 0;

	for(;;) {
		terminal_putentryat('[', terminal_color, 32, 11 + option);
		terminal_putentryat(']', terminal_color, 47, 11 + option);
        
        input = keyboard_readchar();
        if (input == 0x18 && option > 0) {
			terminal_putentryat(' ', terminal_color, 32, 11 + option);
			terminal_putentryat(' ', terminal_color, 47, 11 + option);
            --option;
		}
        else if (input == 0x19 && option < 3) {
			terminal_putentryat(' ', terminal_color, 32, 11 + option);
			terminal_putentryat(' ', terminal_color, 47, 11 + option);
            ++option;
		}
		else if (input == '\n')
			switch(option) {
				case 0:
					textedit_main();
					goto reset; // If I were to do recursion, the memory would be duplicated and if the machine is used too much it will just crash.
				case 1:
					drivereader_main();
					goto reset;
				case 2:
					calculator_main();
					goto reset;
				case 3:
					game_main();
					goto reset;
				case 4:
					clock_main();
					goto reset;
				case 5: // This will return to kernel_main(), where there the PC will shut down, since this function works as the menu.
					return;
			}
	}
}