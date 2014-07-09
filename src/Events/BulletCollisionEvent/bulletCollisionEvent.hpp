/* Bullet collision events result in the attempted damage of the target object
   as well as the removal of the caller bullet; bullets will not react with
   the player that fired them or other bullets */

#ifndef BULLET_COLLISION_EVENT_HPP
#define BULLET_COLLISION_EVENT_HPP

#include "collisionEvent.hpp"

// Forward declaration
namespace Entities {
    class Object;
}

namespace Events {
    
    class BulletCollisionEvent : public CollisionEvent {
        public:
        
        void executeEvent(Entities::Object* target);
        
        BulletCollisionEvent(Entities::Object* _caller);
        ~BulletCollisionEvent();
    };
    
}

#endif