#include <allegro.h>
#include "block.hpp"
#include "screen.hpp"
#include "vector.hpp"
#include "blockCollisionEvent.hpp"
#include "event.hpp"

using Utils::Screen;
using Events::BlockCollisionEvent;

namespace Structures {
	
    // Intializes the standard block dimensions
	int Block::LENGTH_X = 20;
	int Block::LENGTH_Y = 20;
	
	Block::Block(): Object(LENGTH_X, LENGTH_Y, 1) /* Calls the base class constructor */ {
		// Draws the single sprite
        rectfill(sprites[0], 0, 0, lengthX, lengthY, Screen::GRAY);
		rect(sprites[0], 0, 0, lengthX - 1, lengthY - 1, Screen::BLACK);
		line(sprites[0], 0, 0, lengthX, lengthY, Screen::BLACK);
		line(sprites[0], lengthX, 0, 0, lengthY, Screen::BLACK);
		
        // Frees unnecessary vectors since blocks are immobile
		delete movement;
		delete lastMove;
		movement = NULL;
		lastMove = NULL;
        
        collisionEvent = new BlockCollisionEvent(this);
	}
	
	Block::~Block() {
        delete collisionEvent;
    }

}
