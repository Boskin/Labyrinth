/* Collision events are events that happen upon collision with certain objects */

#ifndef COLLISION_EVENT_HPP
#define COLLISION_EVENT_HPP

#include "event.hpp"

namespace Entities {
    class Object;
}

namespace Events {

    class CollisionEvent : public Event {
        public:
        
        virtual void executeEvent(Entities::Object* target) = 0; // To be defined in subclasses
        virtual bool checkForEvent(Entities::Object* target); // Checks for collision with target
        
        // Constructor
        CollisionEvent(Entities::Object* _caller);
        
        // Destructor
        virtual ~CollisionEvent();
    };

}

#endif