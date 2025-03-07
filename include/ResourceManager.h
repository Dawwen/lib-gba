#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "types.h"
#include "animation_resource.h"

class ResourceManager
{
private:
    /* data */
public:
    ResourceManager(/* args */);
    ~ResourceManager();

    const animation_resource* getAnimationResource(u32 id);
    static const u16* getPaletFromResource(const animation_resource*);
    static u32 getFrameIndexFromResource(const animation_resource* resource, u32 index);
    static const u16* getFrameFromIndex(const animation_resource* resource, u32 atlas_index);

};

#endif