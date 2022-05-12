#include "Sprite.hpp"

Sprite::Sprite(volatile obj_attrs* att ,MemoryTiles& data) {

    this->obj_att = att;
    this->asset = &data;

    set_object_position(this->obj_att, 0,0);

    // Set object Attribute
    set_object_bpp(att, 0);
	set_object_palet(att, 0);

    // set_object_palet(att, 1);

	set_object_shape(att, 0);
    set_object_tile(att, 0);
	set_object_size(att, 2);
}

uint16 Sprite::getX() {
    return get_object_position_x(this->obj_att);
}

void Sprite::setX(uint16 x) {
    return set_object_position_x(this->obj_att, x);
}

uint16 Sprite::getY() {
    return get_object_position_y(this->obj_att);
}

void Sprite::setY(uint16 y) {
    set_object_position_y(this->obj_att, y);
}

void Sprite::move(uint16 x, uint16 y) {
    this->setX(this->getX() + x);
    this->setY(this->getY() + y);
}

void Sprite::nextFrame() {
    this->asset->nextFrame();
}

// Get the object Attribute Should only be used by Object Manager
volatile obj_attrs* Sprite::getAtts() {
    return this->obj_att;
}