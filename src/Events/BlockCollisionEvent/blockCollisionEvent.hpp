/* An event that occurs if an object collides with a harmless block */

#ifndef BLOCK_COLLISION_EVENT_HPP
#define BLOCK_COLLISION_EVENT_HPP

#include "collisionEvent.hpp"

// Forward declaration
namespace Entities {
    class Object;
}

namespace Events {

    class BlockCollisionEvent : public CollisionEvent {
        public:
        
        void executeEvent(Entities::Object* target);
        
        // Constructor
        BlockCollisionEvent(Entities::Object* _caller);
        
        // Destructor
        ~BlockCollisionEvent();
    };

}

#endif