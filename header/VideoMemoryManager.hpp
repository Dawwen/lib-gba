#ifndef VIDEOMEMORYMANAGER__HPP
#define VIDEOMEMORYMANAGER__HPP

#include "type.h"
#include <list>

#include "AnimationAtlas.hpp"
#include "MemoryTiles.hpp"
#include "MemoryPalet.hpp"

class VideoMemoryManager {
    // Attributes
    private :
        std::list<MemoryTiles*> objectTileList;
        std::list<MemoryTiles*> backgroundTileList;
        std::list<MemoryPalet*> objectPaletList;
        std::list<MemoryPalet*> backgroundPaletList;
    // Operations
    public :
        uint32 loadPalet (AnimationAtlas atlas);
        uint32 loadAtlas (AnimationAtlas atlas);
        MemoryTiles& getAtlas (uint32 atlasId);
};

#endif
