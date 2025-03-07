#ifndef VIDEO_H
#define VIDEO_H

#include "ResourceManager.h"
#include "VideoManager.h"


namespace video {

void setupDefaultMode0();
void waitVBlank();

VideoManager*       getVideoManager();
ResourceManager*    getResourceManager();

}

#endif
