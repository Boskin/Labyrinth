/* This custom vector class is used to model the movement of objects.
   This class is not to be confused with a containment vector! */

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace Utils {

	class Vector {
        // Static members
        static double deltaTime; // Time it takes for a frame to complete
        
        public:
        static double getDeltaTime(); // Returns delta time
        static void calculateDeltaTime(int frameTime); // Calculates delta time; frameTime is in ticks
        
        private:
        // Other instance variables
		double magnitude;
		double angle;
        
        // Vector components
		double terminalX;
		double terminalY;
		
        // Used to update all values when certain values change
		void calcTerminalCoordinates(); // Calculates the new vector components if angle/magnitude changes
		void calcMagnitudeAngle(); // Calculates the new magnitude and/or angle if components change
		
		static void swap(Vector& a, Vector& b); // Helper function for assignment operator overloading, swaps data
		
		public:
		
		double moveCoordinates(double& x, double& y) const; /* Advances the coordinates by the vector components
                                                               returns the distance the coordinates traveled  */
		
        // Accessor for magnitude
		double getMagnitude() const;
		void setMagnitude(double magnitude);
		
        // Accessor for angle
		double getAngle() const;
		
        // Changes the vector's direction
		void changeDirection(double angle); // Directly changes the angle of the vector
		void changeDirection(bool x, bool y); // Multiplies respective components by -1 if parameter is true
		
        // Accessors for vector components
		double getTerminalX() const;
		double getTerminalY() const;
		
        // Returns vertical or horizontal vectors based on this one
		Vector getXVector() const; // Returns a vector with the x component of the caller's and y component of 0
		Vector getYVector() const; // Returns a vector with the y component of the caller's and x component of 0
		
        // Overloaded operators
		Vector& operator =(Vector opp); // Assigns the same vector components
		Vector operator +(Vector opp) const; // Adds vector components together
		Vector operator *(int opp) const; // Multiply each vector component by the opperand
		
        // Constructors
		Vector(); // Creates a vector with a magnitude and angle of 0
		Vector(double _magnitude, double _angle); // Creates a vector with the desired information
        
        // Destructor
        ~Vector();
	};

}

#endif
