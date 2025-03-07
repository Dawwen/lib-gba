#include "MemoryManager.h"

#include "object_toolbox.h"
#include "log.h"


MemoryManager::MemoryManager(u32 screenblock_index)
{
    this->screenBlockIndex = screenblock_index;
    // Put the whole block as empty
    video_memory_proxy allBlock = {
        .index = 0,
        // .size = 2048,
        .size = 4096,
        .ptr = (u16 *)(tile_mem[screenBlockIndex / 8]) + (screenBlockIndex % 8) * sizeof(screen_block)
    };
    freeMemoryList.push_back(allBlock);
}

MemoryManager::~MemoryManager()
{
}

video_memory_proxy MemoryManager::availableSpace(u32 size)
{
    int index = 0;
    // Look into the list for free memory
    for (auto& freeMemory: freeMemoryList)
    {
        LOG_WARNING("Free Memory: index %d, size %d", freeMemory.index, freeMemory.size );
        // If there is  just enough space
        if (freeMemory.size == size)
        {
            video_memory_proxy memoryBlock = {
                .index = 0,
                .size = size,
                .ptr = freeMemory.ptr
            };

            freeMemoryList.erase(freeMemoryList.begin() + index);

            return memoryBlock;
        }
        // If there is enough space
        if (freeMemory.size > size)
        {
            video_memory_proxy memoryBlock = {
                .index = freeMemory.index,
                .size = size,
                .ptr = freeMemory.ptr
            };

            freeMemory.index += size/16;
            freeMemory.ptr = freeMemory.ptr + size;
            freeMemory.size = freeMemory.size - size;
            
            return memoryBlock;
        }
    }

    // The block is full return nullptr
    video_memory_proxy memoryBlock = {
        .index = 0,
        .size = 0,
        .ptr = nullptr
    };
    return memoryBlock;
}

video_memory_proxy MemoryManager::getAdress()
{
    // The block is full return nullptr
    video_memory_proxy memoryBlock = {
        .index = 0,
        .size = 0,
        .ptr = freeMemoryList[0].ptr
    };
    return memoryBlock;
}

void MemoryManager::reset()
{
    freeMemoryList.clear();

    u16 *start_memory_block   = (u16 *)(tile_mem[screenBlockIndex / 8]) + (screenBlockIndex % 8) * sizeof(screen_block);
    u16 *end_memory_block   = start_memory_block + sizeof(screen_block);
    u16 *ptr = start_memory_block;

    LOG_INFO("block %d ptr start 0x%x ", screenBlockIndex, start_memory_block);
    LOG_INFO("block %d ptr end 0x%x ", screenBlockIndex, end_memory_block);
    
    while (ptr < end_memory_block)
    {
        *ptr++ = 0x0000;
    }

}
