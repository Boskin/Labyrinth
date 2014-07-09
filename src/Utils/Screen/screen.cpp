#include <allegro.h>
#include <cstdio>
#include "screen.hpp"

namespace Utils {

    // Intialize sscreen information
	const int Screen::LENGTH_X = 800;
	const int Screen::LENGTH_Y = 600;
	const int Screen::COLOR_DEPTH = 32;

    // Intializes as a NULL bitmap
	BITMAP* Screen::BUFFER = NULL;

    // Intializes all the colors
	int Screen::CLEAR = -1;
	int Screen::BLACK = -1;
	int Screen::WHITE = -1;
	int Screen::GRAY = -1;
	int Screen::RED = -1;
	int Screen::GREEN = -1;
	int Screen::BLUE = -1;
	int Screen::YELLOW = -1;
	int Screen::ORANGE = -1;
	int Screen::BROWN = -1;
	int Screen::PURPLE = -1;

	void Screen::init() {
		allegro_init(); // Starts allegro
		set_color_depth(COLOR_DEPTH); // Sets the pixel color depth format
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, LENGTH_X, LENGTH_Y, 0, 0); // Creates a windowed screen
		install_keyboard(); // Prepares the keyboard for input
		
		BUFFER = create_bitmap(LENGTH_X, LENGTH_Y); // Creates the buffer bitmap
		
        // Correctly assigns the colors
		BLACK = makecol(0, 0, 0);
		WHITE = makecol(255, 255, 255);
		GRAY = makecol(100, 100, 100);
		RED = makecol(255, 0, 0);
		GREEN = makecol(0, 255, 0);
		BLUE = makecol(0, 0, 255);
		YELLOW = makecol(255, 255, 0);
		ORANGE = makecol(255, 150, 0);
		BROWN = makecol(150, 75, 0);
		PURPLE = makecol(150, 0, 150);
	}

	void Screen::close() {
		destroy_bitmap(BUFFER); // Frees the memory occupied by the buffer bitmap
        BUFFER = NULL;
	}
	
	void Screen::printNum(int i, int x, int y, int col) {
		char buf[32]; // Creates a temporary buffer
		sprintf(buf, "%d", i); // Writes the number to the buffer
		textout_ex(BUFFER, font, buf, x, y, col, -1); // Draws the buffer contents onto the buffer bitmap
	}
	
	void Screen::printNum(double i, int x, int y, int col) {
		char buf[32]; // Creates a temporary buffer
		sprintf(buf, "%3.4f", i); // Writes the double to the buffer with ten-thousandth precision
		textout_ex(BUFFER, font, buf, x, y, col, -1); // Draws the buffer contents onto the buffer bitmap
	}

	void Screen::updateScreen(int background) {
		draw_sprite(screen, BUFFER, 0, 0); // Draw the buffer bitmap onto the actual screen
		rectfill(BUFFER, 0, 0, LENGTH_X, LENGTH_Y, background); // Draw a rectangle of the desired color onto the buffer bitmap
	}

}
