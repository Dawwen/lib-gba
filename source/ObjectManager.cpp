#include "ObjectManager.hpp"

Sprite* ObjectManager::createSprite(MemoryTiles& data) {
    volatile obj_attrs* att = &oam_mem[0];
    return new Sprite(att, data);
}