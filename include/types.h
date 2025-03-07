#ifndef TYPES_H
#define TYPES_H


#define i32 int
#define u32 unsigned int
#define i16 short
#define u16 unsigned short
#define i8 char
#define u8 unsigned char


struct s_video_memory_proxy
{
    u32 index;
    u32 size;
    u16* ptr;
};

typedef struct s_video_memory_proxy video_memory_proxy;

#endif
