#ifndef MEMORYBLOCK__HPP
#define MEMORYBLOCK__HPP

#include "type.h"

#include "AnimationAtlas.hpp"

class MemoryBlock {
    // Attributes
    protected :
        AnimationAtlas* resource;
        uint32 startAdress;
        uint32 endAdress;
    // Operations
    public :
        MemoryBlock (uint32 start, uint32 end, AnimationAtlas* data);
};

#endif
