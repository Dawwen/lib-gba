#include "MemoryBlock.hpp"

MemoryBlock::MemoryBlock(uint32 start, uint32 end, AnimationAtlas* data) {
    this->startAdress = start;
    this->endAdress = end;
    this->resource = data;
}