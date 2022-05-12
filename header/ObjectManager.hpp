#ifndef OBJECTMANAGER__HPP
#define OBJECTMANAGER__HPP

#include "type.h"
#include "object.h"

#include "MemoryTiles.hpp"
#include "Sprite.hpp"

class ObjectManager {
    // Attributes
    public :
        uint32 objectsMap [4];
    // Operations
        ObjectManager ();
        Sprite* createSprite (MemoryTiles& data);
    private :
        uint32 findAvalableObject ();
    public :
        void removeSprite (Sprite* sprite);
};

#endif
