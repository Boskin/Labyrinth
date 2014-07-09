/* A labyrinth is a collection of rooms in a 2D rectangular grid
   formation. Other rooms in the labyrinth are accessed when the main player 
   reaches the screen's border in one of the rooms. */

#ifndef LABYRINTH_HPP
#define LABYRINTH_HPP

// Forward declarations
namespace Entities {
    class Object;
    class Human;
}

namespace Structures {

    class Room;

    class Labyrinth {
        private:
        // Dimensions of the labyrinth in rooms
        int rows;
        int cols;
        
        // 2D array of rooms that make up the labyrinth
        Room*** rooms;
        
        // Coordinates of the initial room to start
        int startRow;
        int startCol;
        
        // Coordinates of the current room
        int curRow;
        int curCol;
        
        Room* currentRoom; // Pointer to the current room being processed
        Entities::Human* mainPlayer; // Pointer to the player that determines the current room
        
        public:
        int getRows() const;
        int getCols() const;
        
        int getStartRow() const;
        int getStartCol() const;
        
        int getCurRow() const;
        int getCurCol() const;
        
        Entities::Human* getMainPlayer();
        
        void run(); // Processes the current room
        void addObject(Entities::Object* o, int col, int row, int x, int y); // Adds an object to a room
        Entities::Object* removeObject(int i, int col, int row);
        Entities::Object* removeObject(Entities::Object* o, int col, int row);
        
        void updateMainPlayer(); /* Updates the value of currentRoom based 
                                    on new curCol and curRow values and 
                                    moves mainPlayer to the new room */
        void createMainPlayer(Entities::Human* player);
        
        // Constructors
        Labyrinth(); // Default constructor that makes a labyrinth with no rooms -> cannot run this labyrinth
        Labyrinth(int _rows, int _cols,int _startRow, int _startCol); // Creates a labyrinth with the specified information
        
        ~Labyrinth(); // Destructor
    };

}

#endif
