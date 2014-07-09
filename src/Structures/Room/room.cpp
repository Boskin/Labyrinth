#include "room.hpp"
#include "object.hpp"
#include "list.hpp"
#include "event.hpp"
#include "screen.hpp"
#include "collisionBox.hpp"

#define C(var) var(_##var)
#define UNLIMITED -1

using Entities::Object;

using Events::Event;

using Utils::Screen;

namespace Structures {
    
    const int Room::OBJECT_MAX = UNLIMITED; // Sets the maximum number of objects
    
    // Constructs an empty room
    Room::Room(): objects(new List<Object*>),
                  gridX(-1), gridY(-1) {}
    
    // Constructs an empty room with the specified grid coordinates of a labyrinth
    Room::Room(int _gridX, int _gridY): objects(new List<Object*>),
                                        C(gridX), C(gridY) {}
    
    Room::~Room() {
        // Deletes all of the room's objects and the list
        while(objects->size() > 0)
            delete objects->remove(0);
        delete objects;
    }
    
    void Room::run() {
        // Runs all of the object's execution sequences
        for(Iterator<Object*> i(objects); i.valid(); i++)
            i.get()->run();
        
        // Runs object collision events
        for(Iterator<Object*> i(objects); i.valid(); i++) {
            for(Iterator<Object*> j = i + 1; j.valid(); j++) {
                if(i.get()->collisionEvent != NULL) {
                    i.get()->collisionEvent->run(j.get());
                }
                
                if(j.get()->collisionEvent != NULL) {
                    j.get()->collisionEvent->run(i.get());
                }
            }
        }
        
        // Removes objects from the list if instructed to do so
        Iterator<Object*> i(objects);
        int index = 0;
        while(i.valid())
            if(!i.get()->placed) {
                i++;
                delete objects->remove(index);
            } else {
                i++;
                index++;
            }
    }
    
    void Room::addObject(Object* o, int x, int y, int i) {
        if(OBJECT_MAX == -1 || objects->size() < OBJECT_MAX) {
            if(i == -1 || objects->size() == 0) {
                objects->add(o);
                o->place(this, x, y);
            } else {
                objects->insert(i, o);
                o->place(this, x, y);
            }
        }
    }
    
    Object* Room::removeObject(int i) {
        if(objects->size() > 0 && i >= 0 && i < objects->size()) {
            (*objects)[i]->remove();
            return objects->remove(i);
        }
        
        return NULL;
    }
    
    Object* Room::removeObject(Object* o) {
        int index = 0;
        for(Iterator<Object*> i(objects); i.valid(); i++, index++)
            if(i.get() == o)
                return objects->remove(index);
        
        return NULL;
    }
}
