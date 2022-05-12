#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    // Clear the memory map
    for (uint32 i = 0; i < 4; i++)
    {
        this->objectsMap[i] = 0; 
    }
}

uint32 ObjectManager::findAvalableObject() {

    // For each map (128 objects so 4 32bits integer)
    for (uint32 k = 0; k < 4; k++)
    {
        // Curent Map
        uint32 objectMap = this->objectsMap[k];

        // If the map is not empty
        if (objectMap != 0xffffffff) {
            // For every place
            for (uint32 i = 0; i < 32; i++)
            {
                // looking if the place is open
                if ((objectMap & (1 << i)) == 0) {
                    this->objectsMap[k] = objectMap |  (1 << i);
                    return i + k * 32;
                }
            }
        }
    }

    // OOM
    return 0;
}

void ObjectManager::removeSprite(Sprite *sprite) {
    volatile obj_attrs* att = sprite->getAtts();
    // Get the index of the object
    uint32 offset = att - oam_mem;
    
    // Clear the attributes
    att->attr0 = 0;
    att->attr1 = 0;
    att->attr2 = 0;

    // Get the position of the object in memory
    uint32 map_offset = offset / 32;
    uint32 index = offset % 32;

    // Remove from the map and destroy the sprite
    this->objectsMap[map_offset] = this->objectsMap[map_offset] & ~(1 << index);
    delete sprite;
}


Sprite* ObjectManager::createSprite(MemoryTiles& data) {
    // Search a available adress for the object
    uint32 id = this->findAvalableObject();

    // Create the object and return the sprite
    volatile obj_attrs* att = &oam_mem[id];
    return new Sprite(att, data);
}