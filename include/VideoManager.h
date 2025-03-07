#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

#include "types.h"
#include "animation_resource.h"

#include "Object.h"
#include "MemoryManager.h"

enum MemoryType{
  unused = 0,
  bgm_map = 1,
  bgm_tiles = 2,
  obj_tiles = 3
};

class VideoManager
{
    public:
      VideoManager(/* args */);
      ~VideoManager();
      
      bool setupBGMPalet4bpp(u32 palet_index, const u16* palet, u32 palet_length);
      bool setupObjectPalet4bpp(u32 palet_index, const u16* palet, u32 palet_length);
      
      const video_memory_proxy getVideoMemoryForObjectTile(const animation_resource* resource);
      const video_memory_proxy getVideoMemoryForBGMTile(u32 size);
      const video_memory_proxy getVideoMemoryTile(MemoryType type, u32 size);
      
      const video_memory_proxy getVideoMemoryForScreenBlock();
      const video_memory_proxy getVideoMemoryForScreenBlock(u32 screenblock_index);

      // const video_memory_proxy getVideoMemoryForBackground(const animation_resource* resource);

      Object* createObject(const animation_resource* resource, video_memory_proxy memory);
      void removeObject(Object *object);

    private:
      // Specify the content of the different screen block
      u32 memoryLayout[6];
      MemoryManager memoryManagers[48] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};

      // Specify the current object in use
      u32 objectMap[4];

      u32 findAvailableObject();
      video_memory_proxy findAvailableBlock(MemoryType type, u32 size, bool allowEmpty=false);



};

#endif