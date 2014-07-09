#ifndef SCREEN_HPP
#define SCREEN_HPP

class BITMAP;

namespace Utils {

	class Screen {
		public:
		
        // Screen dimensions
		static const int LENGTH_X;
		static const int LENGTH_Y;
        
        // Bits per pixel
		static const int COLOR_DEPTH;
		
        // Important startup and close down functions
		static void init(); // Called to intialize allegro and the buffer bitmap
		static void close(); // Called to destroy the buffer bitmap, no further drawing after this call
		
        // Quicly prints numbers to the screen for debug purposes
		static void printNum(int i, int x, int y, int col = BLACK); // Prints an integer with the default black font
		static void printNum(double i, int x, int y, int col = BLACK); // Prints a double with the default black font
        
        // Buffer bitmap everything draws on, drawn to the screen at the end of the loop and refreshed
		static BITMAP* BUFFER;
		
        // Refreshes the screen with the desired background color
		static void updateScreen(int background);
		
        // Commonly used colors
		static int CLEAR;
		static int BLACK;
		static int WHITE;
		static int GRAY;
		static int RED;
		static int GREEN;
		static int BLUE;
		static int YELLOW;
		static int ORANGE;
		static int BROWN;
		static int PURPLE;
	};

}

#endif
