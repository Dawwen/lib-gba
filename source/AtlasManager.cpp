#include "AtlasManager.hpp"
// #include <stdlib.h>

extern void*  __start_sprite[];
extern void*  __stop_sprite[];

animation_resource* nextResource(animation_resource* data) {
    return (animation_resource*)(data->data + ((data->X * data->Y * data-> atlas_length) / 4) + data->palet_length + data->ani_length);
}


AtlasManager::AtlasManager() {
    animation_resource* offset= (animation_resource*)__start_sprite;
    while (offset < (animation_resource*)__stop_sprite) {
        AnimationAtlas* a =  new AnimationAtlas(offset);
        this->atlasList.push_back(a);
        offset = nextResource(offset);
    }
}

uint32 AtlasManager::loadAtlasInMemory(uint32 resourceId) {
    this->videoMemoryManager.loadAtlas(this->getAnimationAtlas(resourceId));
    this->videoMemoryManager.loadPalet(this->getAnimationAtlas(resourceId));

    return 1;
}

AnimationAtlas* AtlasManager::getAnimationAtlas(uint32 id) {
    for(AnimationAtlas* atlas : this->atlasList)
    {
        if (atlas->getId() == id) {
            return atlas;
        }
    }
    return 0x00;
}

MemoryTiles& AtlasManager::getAtlasInMemory(uint32 resourceId) {
    // TODO this function properly
    return this->videoMemoryManager.getAtlas(resourceId);
}