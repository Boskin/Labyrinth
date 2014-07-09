/* Collision boxes are rectangular zones that have the capability
   to check if they are intersecting or colliding with other collision
   boxes. Collision boxes are usually assigned to objects. */

#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include "screen.hpp"

// Forward declarations
namespace Entities {
	class Object;
}

namespace Utils {

    class CollisionBox {
        private:
        
        // References to the coordinates of the object
        double& x;
        double& y;
        
        // References to the dimensions of the object 
        int lengthX;
        int lengthY;
        
        // Offset values to have collision boxes that 
        double xOffset;
        double yOffset;
        
        public:
        
        // Accessor methods for the exact coordinates of a collision box
        double getX();
        double getY();
        
        // Accessor methods to get the dimensions of the collision box
        int getLengthX();
        int getLengthY();
        
        // Methods to check if a collision box has collided with another box or object
        bool collision(CollisionBox& other); // Check if the specified collision box is intersecting with the caller
        bool collision(double x1, double y1,
                       double x2, double y2); // Check if the specified rectange intersects with this collision box
        
        void draw(int color = Utils::Screen::BLACK); // Draws a rectangle where the collision box is for debug purposes
        
        // Constructs a collision box with the specified data
        CollisionBox(double& _x, double& _y, 
                     int _lengthX, int _lengthY,
                     double _xOffset, double _yOffset);
        
        // Destructor
        ~CollisionBox();
    };
    
}

#endif
