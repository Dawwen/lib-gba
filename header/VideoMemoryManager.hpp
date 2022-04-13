#ifndef VIDEOMEMORYMANAGER__HPP
#define VIDEOMEMORYMANAGER__HPP

#include "type.h"

#include "AnimationAtlas.hpp"
#include "MemoryTiles.hpp"
#include "LinkedList.hpp"
#include "MemoryPalet.hpp"

class VideoMemoryManager {
    // Attributes
    private :
        LinkedList<MemoryBlock> objectTileList;
        LinkedList<MemoryBlock> backgroundTileList;
        LinkedList<MemoryBlock> objectPaletList;
        LinkedList<MemoryBlock> backgroundPaletList;
    // Operations
    public :
        uint32 loadPalet (AnimationAtlas atlas);
        uint32 loadAtlas (AnimationAtlas atlas);
        MemoryTiles getAtlas (uint32 atlasId);
};

#endif
