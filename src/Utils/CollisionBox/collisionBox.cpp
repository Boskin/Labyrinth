#include <allegro.h>
#include "collisionBox.hpp"
#include "object.hpp"
#include "screen.hpp"

#define C(var) var(_##var)

using Entities::Object;

namespace Utils {
    
    CollisionBox::CollisionBox(double& _x, double& _y,
                   int _lengthX, int _lengthY,
                   double _xOffset, double _yOffset):
                   // Initialize members
                   C(x), C(y),
                   C(lengthX), C(lengthY),
                   C(xOffset), C(yOffset) {}
                   
    CollisionBox::~CollisionBox() {}
    
    double CollisionBox::getX() {
		return x + xOffset; // Return sum of the x reference and the offset to give the x-coordinate
	}
	
	double CollisionBox::getY() {
		return y + yOffset; // Return sum of the y reference and the offset to give the y-coordinate
	}
    
    int CollisionBox::getLengthX() {
        return lengthX;
    }
    
    int CollisionBox::getLengthY() {
        return lengthY;
    }
    
    bool CollisionBox::collision(double x1, double y1, double x2, double y2) {
        return x1 < x + lengthX + xOffset && x2 > x + xOffset &&
               y1 < y + lengthY + yOffset && y2 > y + yOffset; // Check to see if the rectanges are intersecting
    }
    
    bool CollisionBox::collision(CollisionBox& other) {
        return this->collision(other.getX(), other.getY(),
                               other.getX() + other.lengthX,
                               other.getY() + other.lengthY); // Call the other method with the other collision box's coordinates
    }
    
    void CollisionBox::draw(int color) {
        rectfill(Utils::Screen::BUFFER,
                 getX(), getY(),
                 getX() + lengthX, getY() + lengthY,
                 color);
    }
    
}
