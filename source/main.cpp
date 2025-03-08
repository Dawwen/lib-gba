#include "log.h"
#include "video.h"
#include "input.h"
#include "font.h"


#include "Demo.h"

const u32 SUBARU_ID = 1;

int main(int argc, char const *argv[])
{
    Demo demo;
    demo.init();

    // //For BGM
    // video::getVideoManager()->setupBGMPalet4bpp(0, palet, resource->palet_length);

    // const auto memoryBuffer_map = video::getVideoManager()->getVideoMemoryForScreenBlock(31);
    // const char str[] = "Pinout Mode:" ;
    // for (size_t i = 0; i < 12; i++)
    // {
    //     memoryBuffer_map.ptr[i] = (str[i]- 0x20);
    // }
    
    // const char test[] = "  Pin";
    // for (size_t i = 0; i < 5; i++)
    // {
    //     memoryBuffer_map.ptr[i+32] = (test[i]- 0x20);
    // }


    // const char test1[] = "  SPI";
    // for (size_t i = 0; i < 5; i++)
    // {
    //     memoryBuffer_map.ptr[i+64] = (test1[i]- 0x20);
    // }


    // const char test2[] = "  UART";
    // for (size_t i = 0; i < 6; i++)
    // {
    //     memoryBuffer_map.ptr[i+96] = (test2[i]- 0x20);
    // }


    // const char test3[] = "  Reset";
    // for (size_t i = 0; i < 7; i++)
    // {
    //     memoryBuffer_map.ptr[i+128] = (test3[i]- 0x20);
    // }

    // // memoryBuffer_map.ptr[0] = 1;
    // const auto memoryBuffer_bg = video::getVideoManager()->getVideoMemoryForBGMTile(256);
    // unpackFont(memoryBuffer_bg.ptr, 8);

    u32 i = 0;
    while (true)
    {
        demo.process(i);
        video::waitVBlank();
        i++;
    }
    LOG_WARNING("Program finished");

    mgba_close();
    return 0;
}
