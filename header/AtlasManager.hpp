#ifndef ATLASMANAGER__HPP
#define ATLASMANAGER__HPP

#include "type.h"
#include "animation_resource.h"

#include "VideoMemoryManager.hpp"
#include "AnimationAtlas.hpp"
#include "array.h"

class AtlasManager {
    // Attributes
    private :
        animation_resource* resource_data;
        /// Number of sprite to load should not be necessary
        uint32 spritesNumber;
        array<AnimationAtlas> arrayOfAtlas;
        VideoMemoryManager videoMemoryManager;
    // Operations
    public :
        AtlasManager ();
    private :
        AnimationAtlas getAnimationAtlas (uint32 id);
    public :
        uint32 loadAtlasInMemory (uint32 resourceId);
        MemoryTiles& getAtlasInMemory (uint32 resourceId);
};

#endif
