#ifndef DEMO__H
#define DEMO__H

#include "log.h"
#include "video.h"
#include "input.h"
#include "font.h"

struct sprite_resource
{
    const animation_resource* resource;
    const u16* palet;
    video_memory_proxy memory;
    u32 palet_id;
};

struct menu
{
    u32 x;
    u32 y;
    u32 index;
    u32 size;
    bool selected;
};

class Demo
{
private:
    sprite_resource subaru_resource;
    sprite_resource redhood_resource;
    sprite_resource direction_resource;
    sprite_resource a_resource;
    sprite_resource b_resource;

    Object* subaru_object;
    Object* redhood_object;
    Object* direction_object;
    Object* a_object;
    Object* b_object;

    video_memory_proxy memoryBuffer_map;
    video_memory_proxy memoryBuffer_bg;

    menu comm_menu;

public:
    Demo(/* args */);
    ~Demo();

    void init();
    void process(u32 i);
};

#endif
