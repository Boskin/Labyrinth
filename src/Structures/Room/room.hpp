#ifndef ROOM_HPP
#define ROOM_HPP

#include "list.hpp"

namespace Entities {
    class Object;
    class Player;
}

namespace Structures {
	
	class Room {
		public:
		
		List<Entities::Object*>* objects; // Linked list of objects
		
        // Grid-coordinates of the room if in a labyrinth
		int gridX;
		int gridY;
        
        public:
        
        static const int OBJECT_MAX; // Maximum number of objects in a room, -1 for unlimited
		
		void run(); // Runs all of the objects' execution sequences and handles collisions
		void addObject(Entities::Object* o, int x, int y, int i = -1); // Adds an object to the room
        
        // Object removal, returns the object removed upon completion, returns NULL upon failure
		Entities::Object* removeObject(int i); // Removes the object at the i index in the list
        Entities::Object* removeObject(Entities::Object* o); // Checks the list for the object and removes it
		
		Room(); // Constructs an empty room with no labyrinth
		Room(int _gridX, int _gridY); // Constructs a room within a labyrinth at the grid coordinates
		~Room(); // Destroys all of the objects in the room
        
        friend class Entities::Player; // Allows Entities::Player access to private members
	};
	
}

#endif
