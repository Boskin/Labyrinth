#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "vector.hpp"
#include "screen.hpp"

using Utils::Screen;
using Utils::Vector;

namespace Items {
    class Weapon;
}

namespace Entities {

    class Player : public Object {  
        protected:
        // Player colors
        int bodyColor;
        int faceColor;
        
        // Direction the player is facing
        // 0 = RIGHT, 1 = DOWN, 2 = LEFT, 3 = UP
        int dir;
        
        int health;
        int maxHealth;
        
        public:
        
        virtual void draw();
        virtual void move();
        virtual void damage();
        
        Player(int _bodyColor, int _faceColor, int _lengthX, int _lengthY, int _maxHealth);
        ~Player();
    };

}

#endif
