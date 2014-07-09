/* Event objects consist of checking for a condition with respect to an object
   and executing a routine in response to the fulfilled condition */

#ifndef EVENT_HPP
#define EVENT_HPP

// Forward declaration
namespace Entities {
    class Object;
}

namespace Events {
    
    class Event {
        protected:
        Entities::Object* caller; // Object the event checks with respect to
        
        public:
        void run(Entities::Object* target); // Generic method that executes the event if the condition is fulfilled
        virtual void executeEvent(Entities::Object* target) = 0; // Event routine, to be defined in subclasses
        virtual bool checkForEvent(Entities::Object* target) = 0; // Event condition, to be defined in subclasses
        
        // Constructor
        Event(Entities::Object* _caller);
        
        // Destructor
        virtual ~Event();
    };
    
}

#endif