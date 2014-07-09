#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "object.hpp"

using Entities::Object;

namespace Structures {

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
