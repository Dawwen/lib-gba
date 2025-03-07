#ifndef OBJECT_H
#define OBJECT_H

#include "object_toolbox.h"
#include "animation_resource.h"
// #include "VideoManager.h"

#define SQUARE_SHAPE 0;
#define RECTANGLE_UP_SHAPE 1;
#define RECTANGLE_LEFT_SHAPE 2;

struct size_shape_s
{
    u32 shape;
    u32 size;
};

typedef size_shape_s size_shape;

class Object
{
    friend class VideoManager;


    public:
        Object(volatile obj_attrs* att ,const animation_resource* resource, video_memory_proxy memory);
        ~Object();
        
        u16 getX();
        void setX(u16 x);
        u16 getY();
        void setY(u16 y);
        void move(u16 dx, u16 dy);

        void setTileIndex(u16 tile_index);
        void setPaletIndex(u16 palet_index);

    private:
        volatile obj_attrs* obj_att;

};



#endif