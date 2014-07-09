#include <allegro.h>
#include <cmath>
#include <cstdlib>
#include <process.h>
#include "human.hpp"
#include "player.hpp"
#include "vector.hpp"
#include "weapon.hpp"

using Items::Weapon;

#define C(var) var(_##var)

// Directionaly shortcuts, can determine angles by multipling by M_PI / 2
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

namespace Entities {
    const int Human::LENGTH_X = 20;
    const int Human::LENGTH_Y = 20;
    
    const int Human::INVINCIBILITY_TIME = 1000;
    
    Human::Human(int _bodyColor, int _faceColor, double _spd): Player(_bodyColor, _faceColor, LENGTH_X, LENGTH_Y, 3),
                                                               C(spd), invincibilityTimer(0), spriteFlash(0), weapon(NULL) {}
    
    Human::~Human() {
        if(weapon) {
            delete weapon;
            weapon = NULL;
        }
    }
    
    void Human::draw() {
        if(invincibilityTimer == 0)
            Player::draw();
        else {
            if(spriteFlash == 0) {
                Player::draw();
                spriteFlash = 5;
                _beginthread(coolDownThread, 0, (void*)&spriteFlash);
            }
        }
    }
    
    void Human::move() {
        movement->setMagnitude(0);
        movement->changeDirection(0);
        
        if(key[KEY_RIGHT])
            *movement = *movement + Vector(spd, 0);
        if(key[KEY_DOWN])
            *movement = *movement + Vector(spd, M_PI / 2);
        if(key[KEY_LEFT])
            *movement = *movement + Vector(spd, M_PI);
        if(key[KEY_UP])
            *movement = *movement + Vector(spd, 3 * M_PI / 2);
        
        if(movement->getMagnitude() > spd)
            movement->setMagnitude(spd);
        
        movement->moveCoordinates(x, y);
        *lastMove = *movement;
        if(movement->getMagnitude() != 0)
            lastMove->setMagnitude(-0.5);
        else
            lastMove->setMagnitude(0);
        
        if(key[KEY_D])
            dir = RIGHT;
        if(key[KEY_S])
            dir = DOWN;
        if(key[KEY_A])
            dir = LEFT;
        if(key[KEY_W])
            dir = UP;
        if(weapon != NULL)
            if(key[KEY_SPACE])
                weapon->fire(this, dir * M_PI / 2,
                             x + (lengthX - weapon->getBulletInfo().lengthX) / 2,
                             y + (lengthY - weapon->getBulletInfo().lengthY) / 2);
    
        
    }
    
    void Human::damage() {
        if(invincibilityTimer == 0) {
            Player::damage(); // Calls the generic damage code
            
            if(placed) {
                // Resets the invincibility timer to prevent instant deaths for human players
                invincibilityTimer = INVINCIBILITY_TIME;
                _beginthread(coolDownThread, 0, (void*)&invincibilityTimer);
            }
        }
    }
    
    Weapon* Human::equip(Weapon* _weapon) {
        Weapon* retVal = weapon;
        weapon = _weapon;
        return retVal;
    }
}
