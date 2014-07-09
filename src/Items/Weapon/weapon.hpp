/* A weapon is an intermediate between a player and a bullet. It
   provides the means of adding bullets to the current room as well
   as stats such as bullet speed, dimensions, and appearance.   */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "list.hpp"

class BITMAP;

namespace Structures {
    class Room;
}

namespace Entities {
	class Bullet;
    class Object;
    class Player;
}

void coolDownThread(void* coolDown);

namespace Items {
	class Weapon {
        public:
		
        // Data Structure containing individual bullet information
        struct BulletInfo {
            // Bullet dimensions
            int lengthX;
            int lengthY;
            
            // Bullet colors
            int colorInner;
            int colorOuter;
            
            // Bullet speed and range
            double speed;
            double range;
            
            // Pointer to bullet sprites
            BITMAP** sprite;
        };
        
        private:
        
        BulletInfo bulletInfo; // Contains bullet information
        
        int coolTimer; // Milliseconds remaining in cool down
        int coolDownTime; // Milliseconds to wait before another shot can be fired
        
        int bulletsToFire; // Number of bullets to fire in one instance of the fire function
        double angleBetween; // Angle between multiple bullets fired
		
        void initializeSprite(); // Procedure to create bullet sprite used only in constructor
        
        public:
        
        BulletInfo getBulletInfo(); // Bullet info accessor
        
		void fire(Entities::Player* player, double angle, double xPos, double yPos); // Function to fire bullets with the specified info
        
        // Constructors
		Weapon();
        Weapon(BulletInfo _bulletInfo,
               int _coolDownTime,
               int _bulletsToFire, 
               double _angleBetween);
        Weapon(const Weapon& rhs);
		
        // Destructor
        ~Weapon();
        
        friend class Entities::Bullet; // Gives the bullet class full access to the weapon class
	};
	
}

#endif
