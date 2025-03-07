#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H


#include <vector>

#include "types.h"

class MemoryManager
{
    public:
        MemoryManager(u32 screenblock_index);
        ~MemoryManager();
        void reset();
        video_memory_proxy availableSpace(u32 size);
        video_memory_proxy getAdress();



    private:
        std::vector<video_memory_proxy> freeMemoryList;
        u32 screenBlockIndex;
};

#endif