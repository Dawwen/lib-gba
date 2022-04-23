#ifndef MEMORYTILES__HPP
#define MEMORYTILES__HPP

#include "type.h"

#include "MemoryBlock.hpp"

class MemoryTiles : public MemoryBlock {
    // Attributes
    public :
        uint32 animationFrame = 0;
    // Operations
        MemoryTiles (uint32 start, uint32 end, AnimationAtlas* data);
        void nextFrame ();
    private :
        void updateMemory ();
};

#endif
