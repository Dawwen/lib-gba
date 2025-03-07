#include "Demo.h"

const u32 DIRECTION_ID = 0;
const u32 SUBARU_ID = 1;
const u32 A_ID = 2;
const u32 B_ID = 3;



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

    setupResource(subaru_resource, SUBARU_ID, 0);
    setupResource(direction_resource, DIRECTION_ID, 1);
    setupResource(a_resource, A_ID, 2);
    setupResource(b_resource, B_ID, 3);

    //For BGM
    video::getVideoManager()->setupBGMPalet4bpp(0, subaru_resource.palet, subaru_resource.resource->palet_length);

    subaru_object = video::getVideoManager()->createObject(subaru_resource.resource, subaru_resource.memory);
    subaru_object->move(205, 125);

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
}
