#include "MemoryManager.h"

#include "object_toolbox.h"
#include "log.h"


MemoryManager::MemoryManager(u8 screenblock_index)
{
    this->screenBlockIndex = screenblock_index;
    // Put the whole block as empty
    video_memory_proxy allBlock = {
        .sb_index = screenblock_index,
        .index = 0,
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
        LOG_INFO("Free Memory: index %d, size %d", freeMemory.index, freeMemory.size );
        
        // If there is enough space
        if (freeMemory.size >= size)
        {
            video_memory_proxy memoryBlock = {
                .sb_index = screenBlockIndex,
                .index = freeMemory.index,
                .size = size,
                .ptr = freeMemory.ptr
            };

            // If there is  just enough space
            if (freeMemory.size == size)
            {
                freeMemoryList.erase(freeMemoryList.begin() + index);
            }
            // If there is more space left
            else
            {
                freeMemory.index += size/16;
                freeMemory.ptr = freeMemory.ptr + size;
                freeMemory.size = freeMemory.size - size;
            }
            return memoryBlock;
        }
        index++;
    }

    // The block is full return nullptr
    video_memory_proxy memoryBlock = {
        .index = 0,
        .size = 0,
        .ptr = nullptr
    };
    return memoryBlock;
}

bool MemoryManager::free(video_memory_proxy& memoryBlock)
{
    // Clean the memory
    u16 *ptr = memoryBlock.ptr;
    u32 size = memoryBlock.size;
    while (size > 0)
    {
        *ptr++ = 0x0000;
        size -= 2;
    }

    int index = 0;
    video_memory_proxy* blockToLeft;
    u32 rightIndex = 0;
    video_memory_proxy* blockToRight;
    // Look into the list for free memory
    
    for (auto& freeMemory: freeMemoryList)
    {
        if (freeMemory.index < memoryBlock.index)
        {
            blockToLeft = &freeMemory;
        }
        else if (freeMemory.index > memoryBlock.index)
        {
            blockToRight = &freeMemory;
            rightIndex = index;
            break;
        }
    }

    // Merge with left block
    if (blockToLeft != nullptr && (blockToLeft->index + blockToLeft->size/16) == memoryBlock.index)
    {
        blockToLeft->size += memoryBlock.size;
    }
    // Merge with right block
    if (blockToRight != nullptr && (memoryBlock.index + memoryBlock.size/16) == blockToRight->index)
    {
        blockToRight->index = memoryBlock.index;
        blockToRight->size += memoryBlock.size;
        freeMemoryList.erase(freeMemoryList.begin() + rightIndex);
    }
    else
    {
        freeMemoryList.push_back(memoryBlock);
    }

    return false;
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
    
    while (ptr < end_memory_block)
    {
        *ptr++ = 0x0000;
    }

    // Put the whole block as empty
    video_memory_proxy allBlock = {
        .sb_index = screenBlockIndex,
        .index = 0,
        .size = 4096,
        .ptr = (u16 *)(tile_mem[screenBlockIndex / 8]) + (screenBlockIndex % 8) * sizeof(screen_block)
    };
    freeMemoryList.push_back(allBlock);
}
