#include "MemoryTiles.hpp"

#include "object.h"

MemoryTiles::MemoryTiles(uint32 start, uint32 end, AnimationAtlas* data) : MemoryBlock(start, end, data) {
    this->updateMemory();
}

void MemoryTiles::nextFrame() {
    this->animationFrame++;
    this->updateMemory();
}

void MemoryTiles::setFrame(uint32 frame) {
    this->animationFrame = frame;
    this->updateMemory();
}

void MemoryTiles::updateMemory() {
    uint16 *start_tile_mem   = (uint16 *)tile_mem[4][0];

    array<uint16> frame = this->resource->getSpriteFrame(this->animationFrame); 
    int width = this->resource->getWidth(), height = this->resource->getHeight();
    for (int i = 0; i < width*height / 4; i++)
    {
        *start_tile_mem = frame.data[i]; 
        start_tile_mem++;
    }
}