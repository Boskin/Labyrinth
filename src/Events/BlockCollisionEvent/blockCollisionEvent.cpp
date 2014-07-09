#include <cstdlib>
#include "block.hpp"
#include "blockCollisionEvent.hpp"
#include "collisionEvent.hpp"
#include "object.hpp"
#include "collisionBox.hpp"
#include "vector.hpp"

using Structures::Block;
using Entities::Object;

using Utils::CollisionBox;
using Utils::Vector;

namespace Events {
    BlockCollisionEvent::BlockCollisionEvent(Object* _caller): CollisionEvent(_caller) {
        // Checks if the caller specified is a block
        if(!dynamic_cast<Block*>(caller))
            caller = NULL;
    }
    
    BlockCollisionEvent::~BlockCollisionEvent() {}
    
    void BlockCollisionEvent::executeEvent(Object* target) {
        if(caller && target->movement && target->lastMove) {
            // Records the coordinates of the object while in collision
            double oldX = target->x;
            double oldY = target->y;
            
            // Rolls back the target's coordinates until no collision is deteced with the caller
            while(target->collision(caller))
                target->lastMove->moveCoordinates(target->x, target->y);
            
            /* Checks which direction (RIGHT, LEFT, UP, DOWN) the collision came from and
               alligns the target with that face of the caller */
            if(target->x >= caller->x + caller->lengthX) {
                target->x = caller->x + caller->lengthX;
                target->y = oldY;
            } else if(target->x <= caller->x - target->lengthX) {
                target->x = caller->x - target->lengthX;
                target->y = oldY;
            } else if(target->y <= caller->y - target->lengthY) {
                target->x = oldX;
                target->y = caller->y - target->lengthY;
            } else if(target->y >= caller->y + caller->lengthY) {
                target->x = oldX;
                target->y = caller->y + caller->lengthY;
            }
        }
    }
}