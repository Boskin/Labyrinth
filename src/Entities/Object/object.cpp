#include <allegro.h>
#include <cmath>
#include "list.hpp"
#include "room.hpp"
#include "object.hpp"
#include "screen.hpp"
#include "collisionBox.hpp"
#include "vector.hpp"

#define C(var) var(_##var)

using Utils::Screen;
using Structures::Room;
using Utils::CollisionBox;
using Utils::Vector;

namespace Entities {
    void Object::initialize() {
        // Initialize primary collision box
        collisionBox = new CollisionBox(x, y, lengthX, lengthY, 0, 0);
    }

    Object::Object(int _lengthX, int _lengthY, int _spriteCount):
                   // Initialize data members
                   x(-1), y(-1),
                   C(lengthX), C(lengthY),
                   placed(false), room(NULL),
                   C(spriteCount), externalSprite(false),
                   movement(new Vector), lastMove(new Vector),
                   collisionEvent(NULL) {
        
        // Initialize sprite array
        sprites = new BITMAP*[spriteCount];
        for(int i = 0; i < spriteCount; i++)
            sprites[i] = create_bitmap(lengthX, lengthY);
        
        initialize();
    }

    Object::Object(int _lengthX, int _lengthY, int _spriteCount, BITMAP** _sprites):
                   // Initialize data members
                   x(-1), y(-1),
                   C(lengthX), C(lengthY),
                   placed(false), room(NULL),
                   C(spriteCount), externalSprite(true), C(sprites),
                   movement(new Vector), lastMove(new Vector),
                   collisionEvent(NULL) {
        initialize();
    }

    Object::~Object() {
        // Frees memory occupied by bitmaps if not external
        if(!externalSprite) {
            for(int i = 0; i < spriteCount; i++)
                destroy_bitmap(sprites[i]);
            delete[] sprites;
        }
        
        // Frees memory occupied by collision boxe
        if(collisionBox != NULL)
            delete collisionBox;
        
        // Frees memory occupied by movement vectors
        if(movement != NULL)
            delete movement;
        if(lastMove != NULL)
            delete lastMove;
    }
    
    CollisionBox* Object::getCollisionBox() {
        return collisionBox;
    }
    
    Room* Object::getRoom() {
        return room;
    }

    void Object::run() {
        // Draw and move objects, if placed in a room
        if(placed) {
            draw();
            move();
        }
    }

    void Object::draw() {
        // By default, just draw the first sprite in the sprite array at all times
        draw_sprite(Screen::BUFFER, *sprites, x, y);
    }

    void Object::move() {
        // No movement by default
    }
    
    void Object::damage() {
        // Objects are invincible by default
    }

    bool Object::collision(Object* o) {
        return (collisionBox->collision(*o->collisionBox) && // Check to see if the collision boxes intersect
                this != o); // Make sure that caller and the parameter are not the same objects
    }

    void Object::place(Room* room, int x, int y) {
        this->room = room; // Make the room pointer point to the room the object will be placed in
        
        // Move the object to the desired location
        this->x = (double)x; 
        this->y = (double)y;
        
        placed = true; // Indicate that the object is placed
    }

    void Object::remove() {
        room = NULL; // Current room pointer shouldn't point to a room
        placed = false; // Indicate that the object is not placed
    }
}
