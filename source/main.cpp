#include "log.h"
#include "video.h"
#include "input.h"
#include "font.h"

const u32 SUBARU_ID = 1;

int main(int argc, char const *argv[])
{
    mgba_open();

    LOG_WARNING("Program starting");
    
    video::setupDefaultMode0();


    const animation_resource* resource = video::getResourceManager()->getAnimationResource(SUBARU_ID);
    auto palet = video::getResourceManager()->getPaletFromResource(resource);
    video::getVideoManager()->setupObjectPalet4bpp(0, palet, resource->palet_length);
    const auto memoryBuffer = video::getVideoManager()->getVideoMemoryForObjectTile(resource);
    auto object = video::getVideoManager()->createObject(resource, memoryBuffer);
    object->move(205, 125);

    const animation_resource* resource_joy = video::getResourceManager()->getAnimationResource(0);
    auto palet_joy = video::getResourceManager()->getPaletFromResource(resource_joy);
    video::getVideoManager()->setupObjectPalet4bpp(1, palet_joy, resource_joy->palet_length);
    const auto memoryBuffer_joy = video::getVideoManager()->getVideoMemoryForObjectTile(resource_joy);
    auto object_joy = video::getVideoManager()->createObject(resource_joy, memoryBuffer_joy);
    object_joy->setPaletIndex(1);
    object_joy->setTileIndex(16);
    object_joy->move(10, 120);

    const animation_resource* resource_a = video::getResourceManager()->getAnimationResource(2);
    auto palet_a = video::getResourceManager()->getPaletFromResource(resource_a);
    video::getVideoManager()->setupObjectPalet4bpp(2, palet_a, resource_a->palet_length);
    const auto memoryBuffer_a = video::getVideoManager()->getVideoMemoryForObjectTile(resource_a);
    auto object_a = video::getVideoManager()->createObject(resource_a, memoryBuffer_a);
    object_a->setPaletIndex(2);
    object_a->setTileIndex(32);
    object_a->move(76, 130);

    const animation_resource* resource_b = video::getResourceManager()->getAnimationResource(3);
    auto palet_b = video::getResourceManager()->getPaletFromResource(resource_b);
    video::getVideoManager()->setupObjectPalet4bpp(3, palet_b, resource_b->palet_length);
    const auto memoryBuffer_b = video::getVideoManager()->getVideoMemoryForObjectTile(resource_b);
    auto object_b = video::getVideoManager()->createObject(resource_b, memoryBuffer_b);
    object_b->setPaletIndex(3);
    object_b->setTileIndex(36);
    object_b->move(60, 130);
    
    //For BGM
    video::getVideoManager()->setupBGMPalet4bpp(0, palet, resource->palet_length);

    const auto memoryBuffer_map = video::getVideoManager()->getVideoMemoryForScreenBlock(31);
    const char str[] = "Pinout Mode:" ;
    for (size_t i = 0; i < 12; i++)
    {
        memoryBuffer_map.ptr[i] = (str[i]- 0x20);
    }
    
    const char test[] = "  Pin";
    for (size_t i = 0; i < 5; i++)
    {
        memoryBuffer_map.ptr[i+32] = (test[i]- 0x20);
    }


    const char test1[] = "  SPI";
    for (size_t i = 0; i < 5; i++)
    {
        memoryBuffer_map.ptr[i+64] = (test1[i]- 0x20);
    }


    const char test2[] = "  UART";
    for (size_t i = 0; i < 6; i++)
    {
        memoryBuffer_map.ptr[i+96] = (test2[i]- 0x20);
    }


    const char test3[] = "  Reset";
    for (size_t i = 0; i < 7; i++)
    {
        memoryBuffer_map.ptr[i+128] = (test3[i]- 0x20);
    }

    // memoryBuffer_map.ptr[0] = 1;
    const auto memoryBuffer_bg = video::getVideoManager()->getVideoMemoryForBGMTile(256);
    unpackFont(memoryBuffer_bg.ptr, 8);

    u32 i = 0;
    LOG_WARNING("Object ptr 0x%x", object);
    LOG_WARNING("stack ptr 0x%x", &i);
    LOG_WARNING("rom ptr 0x%x", resource);
    while (true)
    {
        key_poll();


        u32 direction_state = 0;
        u32 a_state = 0;
        u32 b_state = 0;
        if      (key_pushed(KEY_UP))    { direction_state = 1; }
        else if (key_pushed(KEY_RIGHT)) { direction_state = 2; }
        else if (key_pushed(KEY_DOWN))  { direction_state = 3; }
        else if (key_pushed(KEY_LEFT))  { direction_state = 4; }

        if      (key_pushed(KEY_A))    { a_state = 1; }
        if      (key_pushed(KEY_B))    { b_state = 1; }


        auto frame_index = video::getResourceManager()->getFrameIndexFromResource(resource, i/5);
        auto frame_content = video::getResourceManager()->getFrameFromIndex(resource, frame_index);

        for (u32 i = 0; i < memoryBuffer.size; i++)
        {
            memoryBuffer.ptr[i] = frame_content[i];
        }

        auto frame_index_joy = video::getResourceManager()->getFrameIndexFromResource(resource_joy, direction_state);
        auto frame_content_joy = video::getResourceManager()->getFrameFromIndex(resource_joy, frame_index_joy);

        for (u32 i = 0; i < memoryBuffer_joy.size; i++)
        {
            memoryBuffer_joy.ptr[i] = frame_content_joy[i];
        }

        auto frame_index_a = video::getResourceManager()->getFrameIndexFromResource(resource_a, a_state);
        auto frame_content_a = video::getResourceManager()->getFrameFromIndex(resource_a, frame_index_a);

        for (u32 i = 0; i < memoryBuffer_a.size; i++)
        {
            memoryBuffer_a.ptr[i] = frame_content_a[i];
        }

        auto frame_index_b = video::getResourceManager()->getFrameIndexFromResource(resource_b, b_state);
        auto frame_content_b = video::getResourceManager()->getFrameFromIndex(resource_b, frame_index_b);

        for (u32 i = 0; i < memoryBuffer_b.size; i++)
        {
            memoryBuffer_b.ptr[i] = frame_content_b[i];
        }


        video::waitVBlank();
        i++;
    }
    LOG_WARNING("Program finished");

    video::getVideoManager()->removeObject(object);


    mgba_close();
    return 0;
}
