#include "CommPort.h"


#include "log.h"

#define MEM_IO      0x04000000
#define REG_CNT     (*((volatile u32 *)(MEM_IO + 0x0134)))

namespace CommPort {

void resetPort()
{
    REG_CNT = 0;
}

// Pin Mode

void setPinMode()
{
    REG_CNT = 0xc000;
}

bool readPin(Pin pin)
{
    // This check if the pin is in input mode
    if ((REG_CNT & (1 << (pin + 4))) != 0)
    {
        LOG_WARNING("Reading an Output pin");
        return false;
    }
    LOG_WARNING("%x", REG_CNT);
    return REG_CNT & (1 << pin);
}

u32 readPins()
{
    return REG_CNT & 0b1111;
}

void setPin(Pin pin, InOut input)
{
    REG_CNT = (REG_CNT & ~(1 << pin + 4)) | (input << (pin + 4));
}

void setOutputPin(Pin pin, bool value)
{
    // This check if the pin is in input mode
    if ((REG_CNT & (1 << (pin + 4))) == 0)
    {
        // return false;
    }
    
    REG_CNT = (REG_CNT & ~(1 << pin)) | value << pin;
}

}