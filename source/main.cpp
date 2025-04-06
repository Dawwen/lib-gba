#include "log.h"
#include "video.h"
#include "input.h"
#include "font.h"
#include "comm.h"


#include "Demo.h"

const u32 SUBARU_ID = 1;

int main(int argc, char const *argv[])
{
    Demo demo;
    demo.init();
    
    u32 i = 0;
    while (true)
    {
        demo.process(i);
        waitVBlank();
        i++;
    }
    LOG_WARNING("Program finished");

    mgba_close();
    return 0;
}
