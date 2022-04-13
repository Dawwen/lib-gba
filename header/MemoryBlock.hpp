#ifndef MEMORYBLOCK__HPP
#define MEMORYBLOCK__HPP

#include "type.h"

#include "AnimationAtlas.hpp"

class MemoryBlock {
    // Attributes
    private :
        AnimationAtlas* resource;
        uint32 startAdress;
        uint32 endAdress;
};

#endif
