#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H


#include <vector>

#include "types.h"

class MemoryManager
{
    public:
        MemoryManager(u8 screenblock_index);
        ~MemoryManager();
        void reset();
        video_memory_proxy availableSpace(u32 size);
        bool free(video_memory_proxy& memoryBlock);
        video_memory_proxy getAdress();



    private:
        std::vector<video_memory_proxy> freeMemoryList;
        u8 screenBlockIndex;
};

#endif