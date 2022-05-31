#ifndef DATA_H
#define DATA_H

#include "type.h"

struct s_animation_resource {
    uint32 id;
    int32 X;
    int32 Y;
    int32 atlas_length;
    int32 ani_length;
    int32 palet_length;
    uint16 data[];
} __attribute__((__packed__));

typedef struct s_animation_resource animation_resource;

#endif