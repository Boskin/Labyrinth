#include "bulletCollisionEvent.hpp"
#include "collisionEvent.hpp"
#include "object.hpp"
#include "room.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "weapon.hpp"

using Entities::Object;
using Structures::Room;
using Entities::Bullet;
using Items::Weapon;
using Entities::Player;

namespace Events {

    BulletCollisionEvent::BulletCollisionEvent(Object* _caller): CollisionEvent(_caller) {
        // Makes sure that the caller actually is a bullet
        if(!dynamic_cast<Bullet*>(caller))
            caller = NULL;
    }
    
    BulletCollisionEvent::~BulletCollisionEvent() {}
    
    void BulletCollisionEvent::executeEvent(Object* target) {
        if(caller != NULL) {
            Bullet* realCaller = dynamic_cast<Bullet*>(caller);
            // Bullets will not affect or be affected by their master players(firers) or by other bullets
            if(target != realCaller->player && !dynamic_cast<Bullet*>(target)) {
                target->damage(); // Attempts to damage the target
                caller->placed = false; // Flags the object for removal at the end of the room loop
            }
        }
    }

}
