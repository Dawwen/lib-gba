#include "AtlasManager.hpp"
// #include <stdlib.h>

extern void*  __start_sprite[];
extern void*  __stop_sprite[];

AtlasManager::AtlasManager() {
    animation_resource* offset= (animation_resource*)__start_sprite;
    AnimationAtlas* a =  new AnimationAtlas(offset);

    this->atlasList.push_back(a);
}

uint32 AtlasManager::loadAtlasInMemory(uint32 resourceId) {
    this->videoMemoryManager.loadAtlas(this->getAnimationAtlas(resourceId));
    this->videoMemoryManager.loadPalet(this->getAnimationAtlas(resourceId));

    return 1;
}

AnimationAtlas* AtlasManager::getAnimationAtlas(uint32 id) {
    // TODO this function properly
    for(AnimationAtlas* atlas : this->atlasList)
    {
        if (atlas->getId() == id) {
            return atlas;
        }
    }
    // this->atlasList.front()
    return 0x00;
}

MemoryTiles& AtlasManager::getAtlasInMemory(uint32 resourceId) {
    // TODO this function properly
    return this->videoMemoryManager.getAtlas(resourceId);
}