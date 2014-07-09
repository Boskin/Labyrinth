#include <allegro.h>
#include <cstdio>
#include <cmath>
#include "player.hpp"
#include "room.hpp"
#include "collisionBox.hpp"
#include "screen.hpp"
#include "vector.hpp"
#include "weapon.hpp"
#include "event.hpp"

using Utils::Screen;
using Utils::Vector;
using Utils::CollisionBox;
using Structures::Room;
using Items::Weapon;
using Events::Event;

#define C(var) var(_##var)

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

namespace Entities {
    Player::Player(int _bodyColor, int _faceColor, int _lengthX, int _lengthY, int _maxHealth): 
                                                    Object(_lengthX, _lengthY, 4),
                                                    C(bodyColor), C(faceColor),
                                                    dir(rand() % 4), C(maxHealth) {
        health = maxHealth;
        
        rectfill(sprites[0], 0, 0, lengthX, lengthY, bodyColor);
        rectfill(sprites[0], 7 * lengthX / 8, lengthY / 5,
                             lengthX, 4 * lengthY / 5,
                             faceColor);
        for(int i = 1; i < 4; i++)
            rotate_sprite(sprites[i], sprites[0], 0, 0, ftofix(i * 64));
    }
    
    Player::~Player() {}
    
    void Player::draw() {
        char buf[32];
        
        sprintf(buf, "%d / %d", health, maxHealth);
        textout_ex(Screen::BUFFER, font, buf, x, y - 20, Screen::RED, -1);
        draw_sprite(Screen::BUFFER, sprites[dir], x, y);
        
        /*Screen::printNum(x, 20, 20, Screen::GREEN);
        Screen::printNum(y, 100, 20, Screen::GREEN);
        
        Screen::printNum(movement->getTerminalX(), 20, 40, Screen::BLUE);
        Screen::printNum(movement->getTerminalY(), 100, 40, Screen::BLUE);
        Screen::printNum(lastMove->getTerminalX(), 20, 60, Screen::RED);
        Screen::printNum(lastMove->getTerminalY(), 100, 60, Screen::RED);*/
        
    }
    
    void Player::move() {}
    
    void Player::damage() {
        if(--health <= 0)
            placed = false;
    }
    
}
