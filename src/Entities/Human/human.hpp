/* Humans are players controlled by humans; they have a specific movement speed
   and at most one equipable weapon */

#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "player.hpp"
#include "vector.hpp"
#include "screen.hpp"

namespace Items {
    class Weapon;
}

void coolDownThread(void* coolDown); // Implemented in main.cpp

namespace Entities {

    class Human : public Player {
        public:
        // Universal player dimensions
        static const int LENGTH_X;
        static const int LENGTH_Y;
        
        // Invincibility time after taking damage, in frames
        static const int INVINCIBILITY_TIME;
        
        protected:
        double spd;
        
        int invincibilityTimer; // Remaining invincibility time in milliseconds
        int spriteFlash;
        
        Items::Weapon* weapon;
        
        public:
        // Equips a new weapon to the player and returns the old one
        Items::Weapon* equip(Items::Weapon* _weapon);
        
        void draw(); // Sprite flickers if invincibility time is active
        void move(); // Moves with keyboard input
        void damage(); // Recieves invincibility time after being damaged
        
        // Constructor
        Human(int _bodyColor, int _faceColor, double _spd);
        
        // Destructor
        ~Human();
    };

}

#endif
