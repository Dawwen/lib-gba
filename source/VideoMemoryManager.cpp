#include "VideoMemoryManager.hpp"

#include "object.h"


// AnimationAtlas tmp;

uint32 VideoMemoryManager::loadAtlas(AnimationAtlas atlas) {
    uint16 *start_tile_mem   = (uint16 *)tile_mem[4][2];

    array<uint16> frame = atlas.getSpriteFrame(0); 
    int width = atlas.getWidth(), height = atlas.getHeight();
    for (int i = 0; i < width*height / 4; i++)
    {
        *start_tile_mem = frame.data[i]; 
        start_tile_mem++;
    }
    // tmp = atlas;
    return 1;
}

uint32 VideoMemoryManager::loadPalet(AnimationAtlas atlas) {
    uint16 palet_id = 0;
    array<uint16> palet = atlas.getPalet();
    for (uint32 k = 0; k < palet.length; k++) //palet.length
    {
        object_palet_mem[palet_id * 16 + k] = palet.data[k];
    }
    return 1;
}

MemoryTiles VideoMemoryManager::getAtlas(uint32 atlasId) {
    MemoryTiles m;
    return m;
}