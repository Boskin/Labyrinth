#include <allegro.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <process.h>
#include "block.hpp"
#include "screen.hpp"
#include "human.hpp"
#include "labyrinth.hpp"
#include "vector.hpp"
#include "weapon.hpp"

using Entities::Human;

using Items::Weapon;

using Structures::Block;
using Structures::Labyrinth;

using Utils::Screen;
using Utils::Vector;

bool exitProgram = false;
int MIN_TIME = 10;

// Thread used to run a timer in milliseconds, coolDown is an integer that counts down to 0
void coolDownThread(void* coolDown);

// Close button callback function
void closeProgram();

int main() {
    Screen::init(); // Starts the allegro graphics library
    set_close_button_callback(closeProgram); // Assigns the closeProgram function as the callback

    srand(time(NULL)); // Seeds the random number generator
    
    Labyrinth* test = new Labyrinth(1, 1, 0, 0); // Creates a labyrinth of one room that starts at row 0, column 0
    
    // Creates a player in the labyrinth whose perspective is used to handle room changes
    test->createMainPlayer(new Human(Screen::PURPLE, Screen::ORANGE, 130));
    
    // Adds random blocks in the starting room
    for(int i = 0; i < 20; i++) {
        if(i % 5 != 0) {
            test->addObject(new Block, 0, 0, rand() % 400, rand() % 250);
        }
    }
    
    // Equips the player with a weapon
    test->getMainPlayer()->equip(new Weapon((Weapon::BulletInfo) {
                                                        15, 15,
                                                        Screen::BLUE, Screen::GREEN,
                                                        400, 350
                                                    },
                                                    250, 5, M_PI / 8));
    
    // Game loop
    while(!exitProgram && !key[KEY_ESC]) {
        int loopStart = clock(); // The time the loop starts
        
        test->run(); // Runs the labyrinth's room and object routines
        
        Screen::updateScreen(Screen::WHITE); // Updates the screen
        
        Vector::calculateDeltaTime(clock() - loopStart); // Calculates the delta time value
    }
    
    delete test; // Frees memory of the labyrinth
    
    Screen::close(); // Destroys the buffer bitimap
    
    return 0;
}
END_OF_MAIN()

void coolDownThread(void* coolDown) {
    int* coolDownTimer = (int*)coolDown;
    rest(*coolDownTimer);
    *coolDownTimer = 0;
    _endthread();
}

void closeProgram() {
    exitProgram = true; // Sets the exit program boolean to true to exit the loop
}
