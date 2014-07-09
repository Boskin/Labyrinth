#include <cmath>
#include <ctime>
#include <algorithm>
#include "vector.hpp"

#define C(var) var(_##var)
#define SWAP(mem) std::swap(a.mem, b.mem); // Shortcut macro for calling std::swap

namespace Utils {
    
    // Initailizes delta time to 1 by default
    double Vector::deltaTime = 1;

    double Vector::getDeltaTime() {
        return deltaTime;
    }
    
    void Vector::calculateDeltaTime(int frameTime) {
        deltaTime = (double)frameTime / CLOCKS_PER_SEC; // Convert the time in ticks to time in seconds
    }
    
	void Vector::swap(Vector& a, Vector& b) {
		// Swap data members
        SWAP(terminalX)
		SWAP(terminalY)
		SWAP(magnitude)
		SWAP(angle)
	}

	Vector::Vector(): 
    // Intializes members
    magnitude(0), angle(0),
    terminalX(0), terminalY(0) {}

	Vector::Vector(double _magnitude, double _angle):
				   // Intializes members
                   C(magnitude), C(angle) {
        
        // Calculates components based on given data
		calcTerminalCoordinates();
	}
    
    Vector::~Vector() {}

	void Vector::calcTerminalCoordinates() {
        // Calculates components based on magnitude and angle
		terminalX = magnitude * cos(angle);
		terminalY = magnitude * sin(angle);
	}

	void Vector::calcMagnitudeAngle() {
        // Calculates magnitude and angle based on components
		magnitude = sqrt(pow(terminalX, 2) + pow(terminalY, 2));
		angle = atan2(terminalY, terminalX);
	}

	double Vector::moveCoordinates(double& x, double& y) const {
        x += terminalX * deltaTime; // Moves x coordinate
		y += terminalY * deltaTime; // Moves y coordinate
        return magnitude * deltaTime;
	}

	double Vector::getMagnitude() const {
		return magnitude;
	}

	void Vector::setMagnitude(double magnitude) {
		this->magnitude = magnitude;
		calcTerminalCoordinates(); // Updates the components
	}

	double Vector::getAngle() const {
		return angle;
	}

	void Vector::changeDirection(double angle) {
		this->angle = angle;
		calcTerminalCoordinates(); // Updates the components
	}

	void Vector::changeDirection(bool x, bool y) {
		terminalX *= x ? -1 : 1;
		terminalY *= y ? -1 : 1;
		calcMagnitudeAngle(); // Updates the magnitude and angle
	}
	
	double Vector::getTerminalX() const {
		return terminalX;
	}
	
	double Vector::getTerminalY() const {
		return terminalY;
	}
	
	Vector Vector::getXVector() const {
		return Vector(terminalX, 0); // Returns a vector with the magnitude of the x component
	}
	
	Vector Vector::getYVector() const {
		return Vector(terminalY, M_PI / 2); // Returns a vector with the magnitue of the y component
	}

	Vector& Vector::operator =(Vector opp) {
		swap(*this, opp); // Swaps data members
		return (*this); // Returns lvalue reference
	}

	Vector Vector::operator +(Vector opp) const {
		Vector retVal;
        
        // Adds components together
		retVal.terminalX = this->terminalX + opp.terminalX;
		retVal.terminalY = this->terminalY + opp.terminalY;
		
        // Calculates magnitude and angle based on components
        retVal.calcMagnitudeAngle();
		
        return retVal;
	}

	Vector Vector::operator *(int opp) const {
		Vector retVal;
        
		// Multiplies components by the opperand
        retVal.terminalX = opp * terminalX;
		retVal.terminalY = opp * terminalY;
		
        // Calculates the new magnitude
        retVal.calcMagnitudeAngle();
        
		return retVal;
	}

}
