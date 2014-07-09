#include <allegro.h>
#include "bullet.hpp"
#include "object.hpp"
#include "weapon.hpp"
#include "vector.hpp"
#include "room.hpp"
#include "bulletCollisionEvent.hpp"

#define C(var) var(_##var)

using Utils::Vector;
using Items::Weapon;
using Entities::Object;
using Entities::Player;
using Structures::Room;
using Events::BulletCollisionEvent;

namespace Entities {
	
	Bullet::Bullet(Weapon* _weapon, Player* _player, double _angle):
                   Object(_weapon->bulletInfo.lengthX, _weapon->bulletInfo.lengthY, 1, _weapon->bulletInfo.sprite),
                   C(weapon), C(player), distanceTraveled(0) {
        *movement = Vector(weapon->bulletInfo.speed, _angle);
        delete lastMove;
        lastMove = NULL;
        
        collisionEvent = new BulletCollisionEvent(this);
    }
    
    Bullet::~Bullet() {
        delete collisionEvent;
    }
    
    void Bullet::move() {
        distanceTraveled += movement->moveCoordinates(x, y); // Moves the bullet
        //distanceTraveled += weapon->bulletInfo.speed; // Updates the distance elapsed
        if(distanceTraveled > weapon->bulletInfo.range) { // Checks if the distance traveled is greater than the range of the weapon
            placed = false; // Marks this object for removal at the end of the execution loop
        }
    }
	
}
