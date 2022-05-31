#include "VideoMemoryManager.hpp"

#include "object.h"

uint32 VideoMemoryManager::loadAtlas(AnimationAtlas* atlas) {
    // TODO: fix this part to be dynamic
    MemoryTiles* m = new MemoryTiles(2,6, atlas);
    this->objectTileList.push_back(m);
    return 1;
}

uint32 VideoMemoryManager::loadPalet(AnimationAtlas* atlas) {
    uint16 palet_id = 0;
    array<uint16> palet = atlas->getPalet();
    for (uint32 k = 0; k < palet.length; k++) //palet.length
    {
        object_palet_mem[palet_id * 16 + k] = palet.data[k];
    }
    return 1;
}

MemoryTiles& VideoMemoryManager::getAtlas(uint32 atlasId) {
    return *(this->objectTileList.front());
}