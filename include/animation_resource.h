#ifndef DATA_H
#define DATA_H

#include "types.h"

struct s_animation_resource {
    u32 id;
    u32 width;
    u32 height;
    u32 atlas_length;
    u32 ani_length;
    u32 palet_length;
    u16 data[];
} __attribute__((__packed__));

typedef struct s_animation_resource animation_resource;

#endif