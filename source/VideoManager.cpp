#include "VideoManager.h"

#include "object_toolbox.h"
#include "log.h"

// #define MEM_VRAM 0x06000000
// #define MEM_PAL  0x05000000

// typedef u32    tile_4bpp[8];
// typedef tile_4bpp   tile_block[512];

// #define object_palet_mem ((volatile u16 *)(MEM_PAL + 0x200))
// #define tile_mem         ((volatile tile_block *)MEM_VRAM)


#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 8
#define CHUNK_SIZE (CHUNK_WIDTH * CHUNK_HEIGHT)

VideoManager::VideoManager()
{
    // Clear the object memory map
    for (u32 i = 0; i < 4; i++) { this->objectMap[i] = 0; }
    for (u32 i = 0; i < 4; i++) { this->memoryLayout[i] = 0; }

}

VideoManager::~VideoManager()
{
}

bool
VideoManager::setupObjectPalet4bpp(u32 palet_index, const u16* palet, u32 palet_length)
{
    LOG_WARNING("Setuping palet %d with %d value", palet_index, palet_length);

    for (u32 k = 0; k < palet_length; k++)
    {
        object_palet_mem[palet_index * 16 + k] = palet[k];
    }
    return false;
}

bool
VideoManager::setupBGMPalet4bpp(u32 palet_index, const u16* palet, u32 palet_length)
{
    for (u32 k = 0; k < palet_length; k++)
    {
        bgm_palet_mem[palet_index * 16 + k] = palet[k];
    }
    return false;
}

const video_memory_proxy VideoManager::getVideoMemoryForBGMTile(u32 size)
{
    return this->getVideoMemoryTile(MemoryType::bgm_tiles, size);
}

const video_memory_proxy VideoManager::getVideoMemoryForObjectTile(const animation_resource *resource)
{
    u32 block_size = (resource->width * resource->height) /4;    
    return this->getVideoMemoryTile(MemoryType::obj_tiles, block_size);
}

const video_memory_proxy VideoManager::getVideoMemoryTile(MemoryType type, u32 size)
{
    // In case of 4bpp
    auto memoryBlock = this->findAvailableBlock(type, size);

    LOG_WARNING("Trying to find a correct block, found %d with size %d", memoryBlock.index, memoryBlock.size);
    // There is no memory in the correct type with enough space
    if (memoryBlock.size != 0)
    {
        return memoryBlock;
    }
    LOG_WARNING("Could not find a block with the right size switching a block to my type");
    memoryBlock = this->findAvailableBlock(type, size, true);
    return memoryBlock;
}

const video_memory_proxy VideoManager::getVideoMemoryForScreenBlock()
{
    return this->findAvailableBlock(MemoryType::bgm_map, 0, true);
}

const video_memory_proxy VideoManager::getVideoMemoryForScreenBlock(u32 screenblock_index)
{
    u32 charblock_index = screenblock_index / 8; 
    u32 chunk_index = (screenblock_index % 8);
    
    // Check if memory is available

    // Return it;
    return memoryManagers[screenblock_index].getAdress();
}

video_memory_proxy VideoManager::findAvailableBlock(MemoryType output_type, u32 size, bool allowEmpty) {
    
    u32 starting_index=0, last_index=0, screen_block_index=0;;
    switch (output_type)
    {
        // Only allowed in the 1st 4 charblock (0 -> 3)
        case MemoryType::bgm_map:
        case MemoryType::bgm_tiles:
            starting_index = 0;
            last_index = 4;
            break;
        
        // Only allowed in the last 2 charblock (4,5)
        case MemoryType::obj_tiles:
            starting_index = 4;
            last_index = 6;
            screen_block_index = 32; 
            break;

        default:
            LOG_ERROR("Looking for unused MemoryType in VRAM");
            break;
    }

    // For each screen block (32 screen block so each u32 contains 8 screen block)
    for (u32 k = starting_index; k < last_index; k++)
    {
        // Curent chunk
        u32 chunk = this->memoryLayout[k];
        u32 mask = 0b1111;

        for (u32 i = 0; i < 8; i++)
        {
            MemoryType current_type = static_cast<MemoryType>(chunk & mask);

            // In case it is the type we are looking for
            if (current_type == output_type || (allowEmpty && current_type == 0))
            {
                // Look if there is enough space
                MemoryManager& memoryManager = this->memoryManagers[screen_block_index];

                if (current_type == MemoryType::unused)
                {
                    // This should works because it was previously unused (value 0)
                    this->memoryLayout[k] |= output_type << (i * 4);
                }
                

                auto memoryBlock = memoryManager.availableSpace(size);
                LOG_WARNING("Looking at block %d with %d size", memoryBlock.index, memoryBlock.size );

                // Got a correct block
                if (memoryBlock.size == size)
                {
                    LOG_WARNING("Use the screenBlock, %d", screen_block_index);
                    // Was previously unused so change it to the right type
                    if (allowEmpty)
                    {
                        // This should works because it was previously unused (value 0)
                        this->memoryLayout[k] |= output_type << (i * 4);
                    }
                    return memoryBlock;
                }
            }

            // Keep looking further in
            chunk = chunk >> 4;
            screen_block_index++;
        }
    }

    // There is no VRAM available
    if (allowEmpty)
    {
        LOG_ERROR("There is not enought VRAM to store block of type %d and size %d.", output_type, size);
    }
    
    video_memory_proxy memoryBlock = {
        .index = 0,
        .size = 0,
        .ptr = nullptr
    };
    return memoryBlock;
}

u32 VideoManager::findAvailableObject() {

    // For each map (128 objects so 4 32bits integer)
    for (u32 k = 0; k < 4; k++)
    {
        // Curent chunk
        u32 objectChunk = this->objectMap[k];

        // If the chunk is not empty
        if (objectChunk != 0xffffffff) {
            // For every place
            for (u32 i = 0; i < 32; i++)
            {
                // looking if the place is open
                if ((objectChunk & (1 << i)) == 0) {
                    this->objectMap[k] = objectChunk |  (1 << i);
                    return i + k * 32;
                }
            }
        }
    }

    // There are no more object index left
    LOG_ERROR("All the object are in used cannot create a new one.");
    return 0;
}

Object* VideoManager::createObject(const animation_resource* resource, video_memory_proxy memory) {
    // Search a available adress for the object
    u32 object_index = this->findAvailableObject();

    // Create the object and return the sprite
    volatile obj_attrs* att = &oam_mem[object_index];
    return new Object(att, resource, memory);
}

void VideoManager::removeObject(Object* object) {

    u32 index = (object->obj_att - oam_mem);
    LOG_WARNING("Deleting object with id: %d", index);
    delete object;

    u32 chunk_index = index / 32;
    u32 index_in_chunk = index % 32;
    this->objectMap[chunk_index] &= ~(1<< index_in_chunk);
}