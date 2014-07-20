#include "labyrinth.hpp"
#include "room.hpp"
#include "object.hpp"
#include "human.hpp"
#include "screen.hpp"

using Entities::Object;
using Entities::Human;
using Utils::Screen;

#define C(var) var(_##var) // Initializer list shortcut macro

namespace Structures {

    Labyrinth::Labyrinth(): rows(0), cols(0), rooms(NULL), // Initializes members
                            startRow(-1), startCol(-1),
                            curRow(-1), curCol(-1),
                            currentRoom(NULL), mainPlayer(NULL) {}
    
    Labyrinth::Labyrinth(int _rows, int _cols, int _startRow, int _startCol):
                         // Initializes members
                         C(rows), C(cols), rooms(NULL),
                         C(startRow), C(startCol),
                         curRow(startRow), curCol(startCol),
                         currentRoom(NULL), mainPlayer(NULL) {
        // Intializes room array
        rooms = new Room**[rows];
        for(int i = 0; i < rows; i++) {
            rooms[i] = new Room*[cols];
            for(int j = 0; j < cols; j++)
                rooms[i][j] = new Room(i, j);
        }
        currentRoom = rooms[startRow][startCol]; // Points to starting room
    }
    
    Labyrinth::~Labyrinth() {
        // Frees memory occupied by rooms
        if(rooms != NULL) {
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++)
                    delete rooms[i][j];
                delete[] rooms[i];
            }
            delete[] rooms;
        }
    }
    
    int Labyrinth::getRows() const {
        return rows;
    }
    
    int Labyrinth::getCols() const {
        return cols;
    }
    
    int Labyrinth::getStartRow() const {
        return startRow;
    }
    
    int Labyrinth::getStartCol() const {
        return startCol;
    }
    
    int Labyrinth::getCurRow() const {
        return curRow;
    }
    
    int Labyrinth::getCurCol() const {
        return curCol;
    }
    
    Human* Labyrinth::getMainPlayer() {
        return mainPlayer;
    }
    
    void Labyrinth::run() {
        currentRoom->run(); // Runs the current room
        
        if(mainPlayer != NULL) {
            // Checks if the player tries to move off the screen
            // Checks for room transfers
            if(mainPlayer->x + mainPlayer->lengthX > Screen::LENGTH_X) { // Checks if the player moves too far right
                if(curCol + 1 < cols) {
                    curCol++;
                    mainPlayer->x = 0;
                    updateMainPlayer();
                } else {
                    mainPlayer->x = Screen::LENGTH_X - mainPlayer->lengthX;
                }
            }
            if(mainPlayer->y + mainPlayer->lengthX > Screen::LENGTH_Y) { // Checks if the player moves too far down
                if(curRow + 1 < rows) {
                    curRow++;
                    mainPlayer->y = 0;
                    updateMainPlayer();
                } else {
                    mainPlayer->y = Screen::LENGTH_Y - mainPlayer->lengthY;
                }
            }
            if(mainPlayer->x < 0) { // Checks if the player moves too far left
                if(curCol - 1 >= 0) {
                    curCol--;
                    mainPlayer->x = Screen::LENGTH_X - mainPlayer->lengthY;
                    updateMainPlayer();
                } else {
                    mainPlayer->x = 0;
                }
            }
            if(mainPlayer->y < 0) { // Checks if the player moves far too up
                if(curRow - 1 >= 0) {
                    curRow--;
                    mainPlayer->y = Screen::LENGTH_Y - mainPlayer->lengthY;
                    updateMainPlayer();
                } else {
                    mainPlayer->y = 0;
                }
            }
        }
    }
    
    void Labyrinth::addObject(Object* o, int row, int col, int x, int y) {
        rooms[row][col]->addObject(o, x, y);
    }
    
    void Labyrinth::updateMainPlayer() {
        if(mainPlayer != NULL) {
            currentRoom->removeObject(mainPlayer);
            currentRoom = rooms[curRow][curCol];
            currentRoom->addObject(mainPlayer, mainPlayer->x, mainPlayer->y, 0);
        }
    }
    
    void Labyrinth::createMainPlayer(Human* player) {
        if(mainPlayer == NULL) {
            mainPlayer = player;
            addObject(mainPlayer, startRow, startCol, Screen::LENGTH_X / 2 - mainPlayer->lengthX / 2, 
                                                      Screen::LENGTH_Y / 2 - mainPlayer->lengthY / 2);
            currentRoom = rooms[startRow][startCol];
        }
    }

}
