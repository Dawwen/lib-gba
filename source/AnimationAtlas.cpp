#include "AnimationAtlas.hpp"

AnimationAtlas::AnimationAtlas(animation_resource* data) {
    this->id = data->id;
    this->width = data->X;
    this->height = data->Y;

    this->atlas.length = data->atlas_length;
    this->palet.length = data->palet_length;
    this->animation.length = data->ani_length;
    
    this->atlas.data = data->data;
    this->palet.data = data->data + (data->X * data->Y * data-> atlas_length / 4);
    this->animation.data = data->data + ((data->X * data->Y * data-> atlas_length) / 4) + data->palet_length;
}

uint32 AnimationAtlas::getId() {
    return this->id;
}

uint32 AnimationAtlas::getHeight() {
    return this->height;
}

uint32 AnimationAtlas::getWidth() {
    return this->width;
}

array<uint16> AnimationAtlas::getPalet() {
    return this->palet;
}

array<uint16> AnimationAtlas::getSpriteFrame(uint32 index) {
    int animation_index = index % this->animation.length;
    int frame = this->animation.data[animation_index];

    // int frame = this->animation.data[index % this->animation.length];
    // int frame = index % this->atlas.length;
    array<uint16> output;
    output.length = this->width * this->height;
    output.data = &(this->atlas.data[frame * this->width * this->height / 4]);
    return output;
}