#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "object.hpp"

namespace Entities {

    class Block : public Object {
        public:
        
        // Universal block dimensions
        static int LENGTH_X;
        static int LENGTH_Y;
        
        Block(); // Constructor
        ~Block(); // Destructor
    };

}

#endif
