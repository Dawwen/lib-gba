#ifndef SPRITE__HPP
#define SPRITE__HPP

#include "type.h"
#include "object.h"

#include "MemoryTiles.hpp"

class Sprite {
    // Attributes
    private :
        volatile obj_attrs * obj_att;
    public :
        MemoryTiles* asset;
    // Operations
        Sprite (volatile obj_attrs * att, MemoryTiles& data);
        uint16 getX ();
        void setX (uint16 y);
        uint16 getY ();
        void setY (uint16 x);
        void move (uint16 x, uint16 y);
        void nextFrame ();
};

#endif
