#ifndef OBJECTMANAGER__HPP
#define OBJECTMANAGER__HPP

#include "type.h"
#include "object.h"

#include "MemoryTiles.hpp"
#include "Sprite.hpp"

class ObjectManager {
    // Operations
    public :
        Sprite* createSprite (MemoryTiles& data);
};

#endif
