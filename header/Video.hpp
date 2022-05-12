#ifndef VIDEO__HPP
#define VIDEO__HPP

#include "type.h"

#include "AtlasManager.hpp"
#include "ObjectManager.hpp"

class Video {
    // Attributes
    public :
        AtlasManager atlasManager;
        ObjectManager objectManager;
    // Operations
        Video ();
        void init ();
        uint32 loadAtlasInMemory (uint16 resourceId);
        Sprite* createSprite (uint16 resourceId);
        void waitVBlank ();
        void removeSprite (Sprite* sprite);
};

#endif
