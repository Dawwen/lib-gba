#include "Object.h"
#include "log.h"

size_shape get_shape_size(u32 width, u32 height)
{
    size_shape output;
    // Manage the square
    if (width == height)
    {
        output.shape = SQUARE_SHAPE;
        switch (width)
        {
        case 8:
            output.size = 0;
            break;
        case 16:
            output.size = 1;
            break;
        case 32:
            output.size = 2;
            break;
        case 64:
            output.size = 3;
            break;
        default:
            LOG_ERROR("Unknow Square shape: %dx%d", width, height);
            break;
        }
        return output;
    }

    if (width < height)
    {
        output.shape = RECTANGLE_UP_SHAPE;
        height = width;
    }
    else
    {
        output.shape = RECTANGLE_LEFT_SHAPE;
    }
    
    switch (width + height)
    {
    case 8 + 16:
        output.size = 0;
        break;
    case 8 + 32:
        output.size = 1;
        break;
    case 16 + 32:
        output.size = 2;
        break;
    case 32 + 64:
        output.size = 3;
        break;
    default:
        LOG_ERROR("Unknow shape (May Be reversed): %dx%d", width, height);
        break;
    }

    return output;
    
}


Object::Object(volatile obj_attrs* att ,const animation_resource* resource, video_memory_proxy) {

    this->obj_att = att;

    set_object_position(this->obj_att, 0,0);

    // Set object Attribute
    set_object_bpp(att, 0);
	set_object_palet(att, 0);

    // set_object_palet(att, 1);

    size_shape format = get_shape_size(resource->width, resource->height);
	set_object_shape(att, format.shape);
	set_object_size(att, format.size);

    set_object_tile(att, 0);
}

Object::~Object()
{
    this->obj_att->attr0 = 0;
    this->obj_att->attr1 = 0;
    this->obj_att->attr2 = 0;
}


u16 Object::getX() {
    return get_object_position_x(this->obj_att);
}

void Object::setX(u16 x) {
    return set_object_position_x(this->obj_att, x);
}

u16 Object::getY() {
    return get_object_position_y(this->obj_att);
}

void Object::setY(u16 y) {
    set_object_position_y(this->obj_att, y);
}

void Object::move(u16 dx, u16 dy) {
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Object::setTileIndex(u16 tile_index)
{
    set_object_tile(this->obj_att, tile_index);
}

void Object::setPaletIndex(u16 palet_index)
{
    set_object_palet(this->obj_att, palet_index);
}
