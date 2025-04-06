#ifndef COMM_PORT_H
#define COMM_PORT_H

#include "types.h"

namespace CommPort {

enum Pin {
    SC = 0,
    SD = 1,
    SI = 2,
    SO = 3
};

enum InOut {
    Input = 0,
    Output = 1
};


void resetPort();
void setPinMode();

u32 readPins();
bool readPin(Pin pin);
void setOutputPin(Pin pin, bool value);

}

#endif
