#include "ResourceManager.h"

#include "log.h"

// extern void*  __start_animation_resource[];
// extern void*  __stop_animation_resource[];

animation_resource* nextResource(const animation_resource* data) {
    void* ptr = (void*)(data->data + ((data->width * data->height * data-> atlas_length) / 4) + data->palet_length + data->ani_length);
    // 32bit alignement
    if ((u32)ptr % 4)
    {
        ptr += 4 - ((u32) ptr % 4);
    }
    return (animation_resource*)ptr;
}

const animation_resource*
ResourceManager::getAnimationResource(u32 id) {
    const animation_resource* ressource= (animation_resource*)mStartResourceData;
    while (ressource < (animation_resource*)mEndResourceData) {
        if (ressource->id == id)
        {
            LOG_WARNING("Found ressource");
            return ressource;
        }
        LOG_WARNING("Getting next ressource");
        ressource = nextResource(ressource);
    }
    
    LOG_ERROR("Could not find the animation resource with id %d,", id);
    return nullptr;
}

const u16* ResourceManager::getPaletFromResource(const animation_resource* resource)
{
    return (u16*)(resource->data + (resource->width * resource->height * resource->atlas_length / 4));
}

u32 ResourceManager::getFrameIndexFromResource(const animation_resource* resource, u32 index)
{
    u32 real_index = index % resource->ani_length;
    const u16* atlas = resource->data + (resource->width * resource->height * resource->atlas_length / 4) + resource->palet_length;
    return atlas[real_index];
}

const u16* ResourceManager::getFrameFromIndex(const animation_resource* resource, u32 atlas_index)
{
    return (u16*)(resource->data + (resource->width * resource->height * atlas_index / 4));
}

ResourceManager::ResourceManager(void* startData, void* endData)
    : mStartResourceData(startData), mEndResourceData(endData)
{
}

ResourceManager::~ResourceManager()
{
}