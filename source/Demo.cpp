#include "Demo.h"

const u32 DIRECTION_ID = 0;
const u32 SUBARU_ID = 1;
const u32 A_ID = 2;
const u32 B_ID = 3;
const u32 REDHOOD_ID = 4;



void setupResource(sprite_resource& sprite,u32 resource_index, u32 palet_id)
{
    sprite.resource = video::getResourceManager()->getAnimationResource(resource_index);
    sprite.palet = video::getResourceManager()->getPaletFromResource(sprite.resource);
    sprite.memory = video::getVideoManager()->getVideoMemoryForObjectTile(sprite.resource);

    video::getVideoManager()->setupObjectPalet4bpp(palet_id, sprite.palet, sprite.resource->palet_length);
    sprite.palet_id = palet_id;
}


void update_sprite_vram(sprite_resource& sprite, u32 frame)
{
    auto frame_index = video::getResourceManager()->getFrameIndexFromResource(sprite.resource, frame);
    auto frame_content = video::getResourceManager()->getFrameFromIndex(sprite.resource, frame_index);

    for (u32 i = 0; i < sprite.memory.size; i++)
    {
        sprite.memory.ptr[i] = frame_content[i];
    }
}

void write_in_map(u16* map_adress, u32 x, u32 y, const char* string, u32 size)
{

    for (size_t i = 0; i < size; i++)
    {
        // If character is printable
        if (string[i] >= '!' || string[i] <= '~')
        {
            u32 index = y * 32 + x + i;
            map_adress[index] = (string[i]- 0x20);

        }
        
    }
}


Demo::Demo(/* args */)
{
}

Demo::~Demo()
{
    mgba_close();
}

void Demo::init()
{
    mgba_open();
    LOG_WARNING("Program starting");
    video::setupDefaultMode0();

    //For Object
    setupResource(subaru_resource, SUBARU_ID, 0);
    setupResource(redhood_resource, REDHOOD_ID, 4);
    setupResource(direction_resource, DIRECTION_ID, 1);
    setupResource(a_resource, A_ID, 2);
    setupResource(b_resource, B_ID, 3);

    subaru_object = video::getVideoManager()->createObject(subaru_resource.resource, subaru_resource.memory);
    subaru_object->move(205, 125);

    redhood_object = video::getVideoManager()->createObject(redhood_resource.resource, redhood_resource.memory);
    redhood_object->setPaletIndex(redhood_resource.palet_id);
    redhood_object->setTileIndex(redhood_resource.memory.index);
    redhood_object->move(115, 92);

    direction_object = video::getVideoManager()->createObject(direction_resource.resource, direction_resource.memory);
    direction_object->setPaletIndex(direction_resource.palet_id);
    direction_object->setTileIndex(direction_resource.memory.index);
    direction_object->move(10, 120);

    a_object = video::getVideoManager()->createObject(a_resource.resource, a_resource.memory);
    a_object->setPaletIndex(a_resource.palet_id);
    a_object->setTileIndex(a_resource.memory.index);
    a_object->move(76, 130);

    b_object = video::getVideoManager()->createObject(b_resource.resource, b_resource.memory);
    b_object->setPaletIndex(b_resource.palet_id);
    b_object->setTileIndex(b_resource.memory.index);
    b_object->move(60, 130);

    //For BGM
    video::getVideoManager()->setupBGMPalet4bpp(0, subaru_resource.palet, subaru_resource.resource->palet_length);

    const auto memoryBuffer_map = video::getVideoManager()->getVideoMemoryForScreenBlock(31);
    const auto memoryBuffer_bg = video::getVideoManager()->getVideoMemoryForBGMTile(256);
    unpackFont(memoryBuffer_bg.ptr, 1);


    write_in_map(memoryBuffer_map.ptr, 0, 0, "Comm Mode:", 10);
    write_in_map(memoryBuffer_map.ptr, 1, 1, "Pin", 3);
    write_in_map(memoryBuffer_map.ptr, 1, 2, "UART", 4);
    write_in_map(memoryBuffer_map.ptr, 1, 3, "SPI", 3);
    // write_in_map(memoryBuffer_map.ptr, 1, 4, "RESET", 5);

    write_in_map(memoryBuffer_map.ptr, 13, 0, "Pin IN/OUT State:", 17);
    
    write_in_map(memoryBuffer_map.ptr, 14, 1, "SC", 2);
    write_in_map(memoryBuffer_map.ptr, 20, 1, "IN", 2);
    write_in_map(memoryBuffer_map.ptr, 26, 1, "ON", 2);

    write_in_map(memoryBuffer_map.ptr, 14, 2, "SD", 2);
    write_in_map(memoryBuffer_map.ptr, 20, 2, "IN", 2);
    write_in_map(memoryBuffer_map.ptr, 26, 2, "OFF", 3);
    
    // Should not be an output
    write_in_map(memoryBuffer_map.ptr, 14, 3, "SI", 2);
    write_in_map(memoryBuffer_map.ptr, 20, 3, "OUT", 3);
    write_in_map(memoryBuffer_map.ptr, 26, 3, "ON", 2);
    
    write_in_map(memoryBuffer_map.ptr, 14, 4, "SO", 2);
    write_in_map(memoryBuffer_map.ptr, 20, 4, "OUT", 3);
    write_in_map(memoryBuffer_map.ptr, 26, 4, "OFF", 3);
}

void Demo::process(u32 i)
{
    u32 direction_state = 0;
    u32 a_state = 0;
    u32 b_state = 0;

    key_poll();
    
    if      (key_pushed(KEY_UP))    { direction_state = 1; }
    else if (key_pushed(KEY_RIGHT)) { direction_state = 2; }
    else if (key_pushed(KEY_DOWN))  { direction_state = 3; }
    else if (key_pushed(KEY_LEFT))  { direction_state = 4; }

    if      (key_pushed(KEY_A))    { a_state = 1; }
    if      (key_pushed(KEY_B))    { b_state = 1; }

    update_sprite_vram(subaru_resource, i / 5);
    update_sprite_vram(direction_resource, direction_state);
    update_sprite_vram(a_resource, a_state);
    update_sprite_vram(b_resource, b_state);
    update_sprite_vram(redhood_resource, i / 5);
}
