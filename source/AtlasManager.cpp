#include "AtlasManager.hpp"
#include <stdlib.h>

extern void*  __start_info[];
extern void*  __stop_info[];

AtlasManager::AtlasManager() {
    animation_resource* offset= (animation_resource*)__start_info;
    AnimationAtlas *a =  new AnimationAtlas(offset);
    

    this->arrayOfAtlas.length = 1;
    // this->arrayOfAtlas.data = (AnimationAtlas*) malloc(sizeof(AnimationAtlas&) * 1);
    this->arrayOfAtlas.data = a;
}

uint32 AtlasManager::loadAtlasInMemory(uint32 resourceId) {
    this->videoMemoryManager.loadAtlas(this->getAnimationAtlas(resourceId));
    this->videoMemoryManager.loadPalet(this->getAnimationAtlas(resourceId));

    return 1;
}

AnimationAtlas AtlasManager::getAnimationAtlas(uint32 id) {
    // TODO this function properly
    return *(this->arrayOfAtlas.data);
}

MemoryTiles& AtlasManager::getAtlasInMemory(uint32 resourceId) {
    // TODO this function properly
    return this->videoMemoryManager.getAtlas(resourceId);
}