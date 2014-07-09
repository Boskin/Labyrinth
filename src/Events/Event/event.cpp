#include "event.hpp"
#include "object.hpp"
#include "screen.hpp"

#define C(var) var(_##var)

using Entities::Object;

namespace Events {

    Event::Event(Object* _caller): C(caller) {}

    Event::~Event() {}
    
    void Event::run(Object* target) {
        if(checkForEvent(target)) // If the condition is true, execute the routine
            executeEvent(target);
    }
    
}