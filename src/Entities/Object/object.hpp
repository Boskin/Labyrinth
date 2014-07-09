//Object header

/* Objects are visible entities that have collision boxes.
   Examples include blocks, players, and bullets. */

#ifndef OBJECT_HPP
#define OBJECT_HPP

// Forward declarations
class BITMAP;

namespace Structures {
	class Room;
    class Labyrinth;
}

namespace Utils {
    class CollisionBox; 
	class Vector;
}

namespace Events {
    class Event;
    class BlockCollisionEvent;
}

namespace Entities {

    class Object {
        public:
        
        // Object's coordinates
        double x;
        double y;
        
        // Object's dimensions
        int lengthX;
        int lengthY;
        
        bool placed; // See if the object is active/placed in its room
        Structures::Room* room; /* Pointer to the room the object is loacted in, 
                                  NULL if the object is inactive */
        
        /* Array of different sprites the object uses to display itself
           draw function overridend to handle different sprites */
        int spriteCount;
        bool externalSprite;
        BITMAP** sprites;
        
        /* The object's movement vector for the current frame as well as a 
           last movement vector used to rollback the frame's movement in instances
           such as a collision */
        Utils::Vector* movement;
        Utils::Vector* lastMove;
        
        Events::Event* collisionEvent; // Event that detects collisions and handles them accordingly
        
       /* Primary collision box of the object as well as surrounding collision boxes,
       which can be used to indicate direction of the collision */
        Utils::CollisionBox* collisionBox;
        
        void initialize();
        
        public:
        
        Utils::CollisionBox* getCollisionBox();
        Structures::Room* getRoom();
        
        // Overridable methods for different object variations
        void run(); // Method calls both draw and move functions
        virtual void draw(); // Method that draws the sprite to the buffer bitmap
        virtual void move(); // Method that handles the movement of the object
        virtual void damage(); // Method that handles damaging the object, if possible
        
        // Standard methods for object handling
        void place(Structures::Room* room, int x, int y); /* Places the object in the 
                                                            specified room at the specified coordinates */
        void remove(); // Called whenever an object is removed from the room
        bool collision(Object* o); // Detects whether a collision has occured with the other object
        
        // Constructors
        Object(int _lengthX, int _lengthY, int _spriteCount); 
        Object(int _lengthX, int _lengthY, int _spriteCount, BITMAP** _sprites); /* Constructor used if all of one variation of 
                                                                                objects will have te same sprite */
        // Overridable destructor
        virtual ~Object();
        
        friend class Structures::Labyrinth; // Gives labyrinths access to private fields
        friend class Structures::Room;
        friend class Events::BlockCollisionEvent;
    };

}

#endif
