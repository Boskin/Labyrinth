#include "collisionEvent.hpp"
#include "event.hpp"
#include "object.hpp"

using Entities::Object;

namespace Events {
    CollisionEvent::CollisionEvent(Object* _caller): Event(_caller) {}
    
    CollisionEvent::~CollisionEvent() {}
    
    bool CollisionEvent::checkForEvent(Entities::Object* target) {
        return caller->collision(target); // Checks for collision
    }
}
