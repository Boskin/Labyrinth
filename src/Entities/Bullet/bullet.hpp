/* Bullets are harmful objects that try to damage other objects
   they come in contact with. Bullets are added to a room when
   weapons are activated by players and possibly other future smart
   objects. */

#ifndef BULLET_HPP
#define BULLET_HPP

#include "object.hpp"

// Forward declarations
namespace Entities {
    class Player;
}

namespace Items {
    class Weapon;
}

namespace Entities {
	
    class Bullet : public Object {
        public:
        
        Items::Weapon* weapon; // Pointer to the weapon responsible for firing the bullet
        
        Entities::Player* player;
        
        double distanceTraveled; // Distance the bullet has traveled
        
        void move(); // Overriden move function
        
        Bullet(Items::Weapon* _weapon, Entities::Player* _player,
               double _angle); // Constructs a bullet from the desired weapon firing at the desired angle
        ~Bullet(); // Destructor
    };

}

#endif
